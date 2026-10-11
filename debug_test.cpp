#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct State {
    int x, y, visited_shop;
    int dist;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    
    pair<int, int> start, home;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = {i, j};
            } else if (grid[i][j] == 3) {
                home = {i, j};
            }
        }
    }
    
    cout << "Start: (" << start.first << "," << start.second << ")" << endl;
    cout << "Home: (" << home.first << "," << home.second << ")" << endl;
    cout << "Grid:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    // BFS with state: (x, y, visited_shop)
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
    queue<State> q;
    
    // Check if start position is already a shop
    int start_visited_shop = (grid[start.first][start.second] == 4) ? 1 : 0;
    
    cout << "Start visited shop: " << start_visited_shop << endl;
    
    dist[start.first][start.second][start_visited_shop] = 0;
    q.push({start.first, start.second, start_visited_shop, 0});
    
    int min_distance = INT_MAX;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        cout << "Processing: (" << curr.x << "," << curr.y << ") visited=" << curr.visited_shop << " dist=" << curr.dist << endl;
        
        // If we reached home and have visited a shop, update answer
        if (curr.x == home.first && curr.y == home.second && curr.visited_shop == 1) {
            min_distance = min(min_distance, curr.dist);
            cout << "Found path to home with shop! Distance: " << curr.dist << endl;
            continue; // Continue searching for potentially shorter paths
        }
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 1) {
                int next_visited_shop = curr.visited_shop;
                if (grid[nx][ny] == 4) {
                    next_visited_shop = 1;
                }
                
                if (dist[nx][ny][next_visited_shop] > curr.dist + 1) {
                    dist[nx][ny][next_visited_shop] = curr.dist + 1;
                    q.push({nx, ny, next_visited_shop, curr.dist + 1});
                    cout << "  Pushing: (" << nx << "," << ny << ") visited=" << next_visited_shop << " dist=" << curr.dist + 1 << endl;
                }
            }
        }
    }
    
    if (min_distance == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_distance << endl;
    }
    
    return 0;
}