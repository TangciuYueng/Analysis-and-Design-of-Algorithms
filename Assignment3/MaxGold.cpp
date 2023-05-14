#include <iostream>
#include <vector>
using namespace std;
  
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int m, n;
int ans = 0;
int temp = 0;
// 判断是否为合适的起点，周围有两条路以上的处于中间，不适合为起点 
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
// 递归函数 
void help(vector<vector<int>>& grid, int x, int y) {
    ans = max(ans, temp);
    // 出界
    if (x < 0 || y < 0 || x >= m || y >= n) {
        return;
    }
    // 没东西或访问过 
    if (grid[x][y] == 0) {
        return;
    }
    // 当前收获
    temp += grid[x][y];
    // 记录原来金矿数量
	int goldBefore = grid[x][y];
	// 更改为0表示访问过
    grid[x][y] = 0; 
    // 遍历四个方向
    for (int i = 0; i < 4; ++i) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        help(grid, new_x, new_y);
	}
    // 回溯
	grid[x][y] = goldBefore; 
    temp -= grid[x][y];
}
int getMaximumGold(vector<vector<int>>& grid) {
    m = grid.size();
    n = grid[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
           	// 判断是否为合适的起点 
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
	
	cout << "输出" << getMaximumGold(grid) << endl; 
	system("pause");
}
