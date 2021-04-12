// 다리 만들기 2  21/04/02
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <algorithm>

#define MAX_N 10
#define MAX_M 10
#define MAX_ISLANDS 6

using namespace std;

struct bridge {
    int a, b, length;
};

int n = 0, m = 0;
bool map[MAX_N][MAX_M];
vector<pair<int, int> > islands[MAX_ISLANDS];
int num_islands = 0;
bool visited[MAX_N][MAX_M];
vector<bridge> bridges;
int parent[MAX_ISLANDS];
int result;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

bool compare(bridge a, bridge b) {
    return a.length < b.length;
}

int find(int x) {
    if (parent[x] == x) return x;
    else return find(parent[x]);
}

void union_(int a, int b) {
    int u = find(a), v = find(b);
    parent[v] = min(u, v);
    if (u < v) parent[v] = u;
    else parent[u] = v;
}

bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

vector<pair<int, int> > BFS(int a, int b) {
    queue<pair<int, int> > q;
    q.push(make_pair(a, b));
    visited[a][b] = true;
    vector<pair<int, int> > island;
    island.push_back(make_pair(a, b));

    while (q.empty() == 0) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (in_range(nx, ny) && map[nx][ny] && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
                island.push_back(make_pair(nx, ny));
            }
        }
    }
    return island;
}

void find_islands() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && map[i][j]) {
                islands[num_islands] = BFS(i, j);
                num_islands++;
            }
        }
    }
}

int shortest_bridge(int a, int b) {
    // return shortest possible bridge length
    // if no bridge is possible, return INT_MAX
    vector<pair<int, int> > island_a = islands[a], island_b = islands[b];
    int min_length = INT_MAX;
    // 같은 열 또는 같은 행에 있는 원소가 존재하고, 길이 1이상이어야 하고, 중간에 가로막는 섬이 없어야.
    for (int i = 0; i < island_a.size(); i++) {
        for(int j = 0; j < island_b.size(); j++) {
            int ax = island_a[i].first, ay = island_a[i].second;
            int bx = island_b[j].first, by = island_b[j].second;
            if (ax == bx) {
                // check if nothing blocks the two
                int larger = max(ay, by), smaller = min(ay, by);
                bool is_blocked = false;
                for (int y = smaller + 1; y < larger; y++) {
                    if (map[ax][y]) {
                        is_blocked = true;
                        break;
                    }
                }
                if (!is_blocked) {
                    int length = (int) abs(ay - by) - 1;
                    if (length > 1 && length < min_length) {
                        min_length = length;
                    }
                }
            }
            else if (ay == by) {
                int larger = max(ax, bx), smaller = min(ax, bx);
                bool is_blocked = false;
                for (int x = smaller + 1; x < larger; x++) {
                    if (map[x][ay]) {
                        is_blocked = true;
                        break;
                    }
                }
                if (!is_blocked) {
                    int length = (int) abs(ax - bx) - 1;
                    if (length > 1 && length < min_length) {
                        min_length = length;
                    }
                }
            }
        }
    }
    return min_length;
}

void find_bridges() {
    for (int i = 0; i < num_islands; i++) {
        for (int j = i + 1; j < num_islands; j++) {
            int length = shortest_bridge(i, j);
            if (length < INT_MAX) {
                bridge b = {i, j, length};
                bridges.push_back(b);
            }
        }
    }
}

void find_mst() {
    sort(bridges.begin(), bridges.end(), compare);

    // set parents
    for (int i = 0; i < num_islands; i++) {
        parent[i] = i;
    }

    // find mst
    for (int i = 0; i < bridges.size(); i++) {
        // union if a and b have different parents
        if (find(bridges[i].a) != find(bridges[i].b)) {
            result += bridges[i].length;
            union_(bridges[i].a, bridges[i].b);
        }
    }
}

bool check_connected() {
    int common_parent = find(0);
    for (int i = 1; i < num_islands; i++)
        if (common_parent != find(i)) return false;
    return true;
}

int main () {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    find_islands();

    find_bridges();

    find_mst();
    
    // check if all islands are connected
    if (check_connected()) cout << result;
    else cout << -1;
    
    return 0;
}


