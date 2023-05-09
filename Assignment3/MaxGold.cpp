#include <iostream>
#include <vector>
using namespace std;
  
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int m, n;
int ans = 0;
int temp = 0;
void help(vector<vector<int>>& grid, vector<vector<bool>>& vis, int x, int y) {
    ans = max(ans, temp);
        // 出界
        if (x < 0 || y < 0 || x >= m || y >= n) {
            return;
        }
        // 没东西
        if (grid[x][y] == 0 || vis[x][y]) {
            return;
        }
        // 当前收获
        temp += grid[x][y];
        // 访问过
        vis[x][y] = true;
        // 遍历四个方向
        for (int i = 0; i < 4; ++i) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            help(grid, vis, new_x, new_y);
        }
        vis[x][y] = false;
        temp -= grid[x][y];
    }
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<vector<bool>> vis(m, vector<bool>(n, false));
                help(grid, vis, i, j);
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
	
	cout << "输出" << getMaximumGold(grid) << endl; 
	system("pause");
}
