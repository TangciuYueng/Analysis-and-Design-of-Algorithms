#include <iostream>
#include <vector>
using namespace std;

// 求解C(x, x + y)
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

// 爬楼梯函数
long long stairs(int m, int n) {
	// 设爬上m个台阶需要x次一步，y次两部
	// x + 2y = m
	// 卡路里限制
	// x + 3y <= n
	// 于是有0 <= y <= n - m
	if (n - m < 0)
		return 0;
	int x, y;
	long long ans = 0;
	// 解出方程组y最大整数解
	for (y = n - m; y >= 0; --y) {
		x = m - 2 * y;
		// 不满足卡路里条件
		if (x + 3 * y > n || x < 0)
			continue;
		ans = count(x, y);
		// 找到一组就退出
		break;
	}
	return ans;
}

int main() {
	int m, n;
	// 输入合法性判断
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