#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;
vector<vector<int>> grid;
vector<vector<int>> dist;

int bfs(int start_x, int start_y) {
    dist.assign(m, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;
    
    dist[start_x][start_y] = 0;
    q.push({start_x, start_y});
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    grid.resize(m, vector<int>(n));
    
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
    
    // BFS from start
    bfs(start.first, start.second);
    vector<vector<int>> dist_from_start = dist;
    
    // BFS from home
    bfs(home.first, home.second);
    vector<vector<int>> dist_from_home = dist;
    
    int min_distance = INT_MAX;
    
    // For each umbrella shop, calculate total distance
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
    
    return 0;
}