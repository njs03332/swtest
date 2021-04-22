// 스타트 택시  21/04/07
#include <iostream>
#include <climits>
#include <vector>
#include <queue>

#define MAX_N 20
#define MAX_M 400
#define MAX_GAS 500000

using namespace std;

struct grid {
    int x, y;
};

int n, m;
int gas = 0;
grid taxi;
bool walls[MAX_N + 1][MAX_N + 1] = {{false}};
int passengers[MAX_N + 1][MAX_N + 1] = {{0}};
grid destinations[MAX_M + 1];
vector<int> gone_passengers;
int dx[4] = {-1, 0, 0, 1};  // 상 좌 우 하
int dy[4] = {0, -1, 1, 0};


void fill_gas(int a) {
    gas += a;
}

bool use_gas(int a) {
    if (gas < a) return false;
    else gas -= a;
    return true;
}

bool in_range(int a, int b) {
    return a > 0 && b > 0 && a <= m && b <= m && !walls[a][b];
}

int** BFS(int a, int b) {
    queue<grid> q;
    bool visited[MAX_N + 1][MAX_N + 1] = {{false}};
    grid g = {a, b};
    q.push(g);
    visited[a][b] = true;
    int **dist = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) dist[i] = new int[n + 1];
    dist[a][b] = 0;
    
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (in_range(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                grid n = {nx, ny};
                q.push(n);
                dist[nx][ny] = dist[x][y] + 1;
            }
        }
    }
    return dist;
}

int goto_nearest_passenger() {
    int **dist = BFS(taxi.x, taxi.y);
    int min_dist = INT_MAX;
    int min_p;
    grid min_grid;
    for (int i = 1; i <= m; i++) {  // row first
        for (int j = 1; j <= m; j++) {  // column second
            if (passengers[i][j] > 0 && dist[i][j] < min_dist) {
                min_dist = dist[i][j];
                min_p = passengers[i][j];
                grid new_grid = {i, j};
                min_grid = new_grid;
            }
        }
    }
    if (!use_gas(min_dist)) return -1;
    taxi = min_grid;
    return min_p;
}

int move_passenger(int p) {
    int dest_x = destinations[p].x, dest_y = destinations[p].y;
    int **dist = BFS(taxi.x, taxi.y);
    int travel_dist = dist[dest_x][dest_y];
    if (!use_gas(travel_dist)) return -1;
    passengers[taxi.x][taxi.y] = 0;
    gone_passengers.push_back(p);
    taxi = destinations[p];
    fill_gas(travel_dist * 2);
    return 1;
}

int main() {
    int init_gas;
    cin >> n >> m >> init_gas;
    fill_gas(init_gas);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> walls[i][j];
        }
    }
    cin >> taxi.x >> taxi.y;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        passengers[x][y] = i;
        grid dest;
        cin >> dest.x >> dest.y;
        destinations[i] = dest;
    }

    while (gone_passengers.size() < m) {
        int p = goto_nearest_passenger();
        if (p < 0) {
            cout << -1;
            return 0;
        }
        else {
            if (move_passenger(p) < 0) {
                cout << -1;
                return 0;
            }
        }
    }
    cout << gas;
}