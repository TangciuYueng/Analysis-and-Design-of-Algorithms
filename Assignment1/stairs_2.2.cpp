#include <iostream>
#include <vector>
using namespace std;

// ���C(x, x + y)
long long count(int x, int y) {
	int Min = min(x, y);
	int N = x + y;
	vector<vector<long> > dp(N - Min + 1, vector<long>(Min + 1, 1));
	for (int i = 1; i < N - Min + 1; ++i) {
		for (int j = 1; j < Min + 1; ++j) {
			dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
		}
	}
	return dp[N - Min][Min];
}

// ��¥�ݺ���
long long stairs(int m, int n) {
	// ������m��̨����Ҫx��һ����y������
	// x + 2y = m
	// ��·������
	// x + 3y <= n
	// ������0 <= y <= n - m
	if (n - m < 0)
		return 0;
	int x, y;
	long long ans = 0;
	// ���������y���������
	for (y = n - m; y >= 0; --y) {
		x = m - 2 * y;
		// �����㿨·������
		if (x + 3 * y > n || x < 0)
			continue;
		ans = count(x, y);
		// �ҵ�һ����˳�
		break;
	}
	return ans;
}

int main() {
	int m, n;
	// ����Ϸ����ж�
	while (1) {
		cout << "input: ";
		cin >> m >> n;
		if (cin.fail()) {
			cout << "INPUT ERROR" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	cout << "output: " << stairs(m, n) << endl;
	cout << "press any key to exit" << endl;
	cin.ignore(1024, '\n');
	cin.get();
}