#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(m, vector<int>(n));
        
        pair<int, int> start, home;
        vector<pair<int, int>> shops;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 2) {
                    start = {i, j};
                } else if (grid[i][j] == 3) {
                    home = {i, j};
                } else if (grid[i][j] == 4) {
                    shops.push_back({i, j});
                }
            }
        }
        
        // If no shops, no solution
        if (shops.empty()) {
            cout << -1 << endl;
            continue;
        }
        
        // BFS from start
        vector<vector<int>> dist_from_start(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        dist_from_start[start.first][start.second] = 0;
        q.push(start);
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    grid[nx][ny] != 1 && dist_from_start[nx][ny] == INT_MAX) {
                    dist_from_start[nx][ny] = dist_from_start[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        
        // BFS from home
        vector<vector<int>> dist_from_home(m, vector<int>(n, INT_MAX));
        dist_from_home[home.first][home.second] = 0;
        q.push(home);
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    grid[nx][ny] != 1 && dist_from_home[nx][ny] == INT_MAX) {
                    dist_from_home[nx][ny] = dist_from_home[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        
        int min_distance = INT_MAX;
        
        // Check each shop
        for (auto shop : shops) {
            int x = shop.first, y = shop.second;
            if (dist_from_start[x][y] != INT_MAX && dist_from_home[x][y] != INT_MAX) {
                int total_dist = dist_from_start[x][y] + dist_from_home[x][y];
                min_distance = min(min_distance, total_dist);
            }
        }
        
        if (min_distance == INT_MAX) {
            cout << -1 << endl;
        } else {
            cout << min_distance << endl;
        }
    }
    
    return 0;
}