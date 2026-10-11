#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct State {
    int x, y, visited;
    State(int _x, int _y, int _v) : x(_x), y(_y), visited(_v) {}
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
            if (grid[i][j] == 2) start = {i, j};
            else if (grid[i][j] == 3) home = {i, j};
        }
    }
    
    // BFS with state tracking
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
    queue<State> q;
    
    // Start with visited=0 (haven't visited shop yet)
    dist[start.first][start.second][0] = 0;
    q.push(State(start.first, start.second, 0));
    
    int result = INT_MAX;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        int curr_dist = dist[curr.x][curr.y][curr.visited];
        
        // If we reached home and have visited a shop
        if (curr.x == home.first && curr.y == home.second && curr.visited == 1) {
            result = min(result, curr_dist);
            continue;
        }
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 1) {
                int next_visited = curr.visited;
                if (grid[nx][ny] == 4) {
                    next_visited = 1;
                }
                
                if (dist[nx][ny][next_visited] > curr_dist + 1) {
                    dist[nx][ny][next_visited] = curr_dist + 1;
                    q.push(State(nx, ny, next_visited));
                }
            }
        }
    }
    
    if (result == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}