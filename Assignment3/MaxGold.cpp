#include <iostream>
#include <vector>
using namespace std;
  
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int m, n;
int ans = 0;
int temp = 0;
// �ж��Ƿ�Ϊ���ʵ���㣬��Χ������·���ϵĴ����м䣬���ʺ�Ϊ��� 
bool isStart(vector<vector<int>>& grid, int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (new_x < 0 || new_y < 0 || new_x >= m || new_y >= n || grid[new_x][new_y] == 0)
            continue;
        ++cnt;
	}
    return cnt <= 2;
}
// �ݹ麯�� 
void help(vector<vector<int>>& grid, int x, int y) {
    ans = max(ans, temp);
    // ����
    if (x < 0 || y < 0 || x >= m || y >= n) {
        return;
    }
    // û��������ʹ� 
    if (grid[x][y] == 0) {
        return;
    }
    // ��ǰ�ջ�
    temp += grid[x][y];
    // ��¼ԭ���������
	int goldBefore = grid[x][y];
	// ����Ϊ0��ʾ���ʹ�
    grid[x][y] = 0; 
    // �����ĸ�����
    for (int i = 0; i < 4; ++i) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        help(grid, new_x, new_y);
	}
    // ����
	grid[x][y] = goldBefore; 
    temp -= grid[x][y];
}
int getMaximumGold(vector<vector<int>>& grid) {
    m = grid.size();
    n = grid[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
           	// �ж��Ƿ�Ϊ���ʵ���� 
           	if (grid[i][j] && isStart(grid, i, j))  {
               	help(grid, i, j);
			}
                
        }
    }
    return ans;
}
int main() {
	int a, b;
	cout << "rows: ";
	cin >> a;
	cout << "cols: ";
	cin >> b;
	
	vector<vector<int>> grid(a, vector<int>(b));
	
	cout << "input grid" << endl;
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			cin >> grid[i][j];
		} 
	}
	
	cout << "���" << getMaximumGold(grid) << endl; 
	system("pause");
}
