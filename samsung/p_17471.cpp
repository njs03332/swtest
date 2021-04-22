// 게리맨더링  21/04/10
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

#define MAX_N 10
#define MAX_P 100

using namespace std;

int n;
int population[MAX_N + 1];
vector<int> adj[MAX_N + 1];
bool mask[MAX_N + 1];


bool is_connected(vector<int> area) {
    bool visited[MAX_N + 1] = {false};
    queue<int> q;
    q.push(area[0]);
    visited[area[0]] = true;

    while (!q.empty()) {
        int city = q.front();
        q.pop();
        for (int i = 1; i <= adj[city][0]; i++) {
            int neighbor = adj[city][i];
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    for (int i = 0; i < area.size(); i++) {
        if (!visited[area[i]]) return false;
    }
    return true;
}

int get_pop_diff() {
    vector<int> area_1, area_2;
    for (int i = 1; i <= n; i++) {
        if (mask[i]) {
            area_1.push_back(i);
        }
        else {
            area_2.push_back(i);
        }
    }

    int diff = 0;
    if (is_connected(area_1) && is_connected(area_2)) {
        for (int i = 0; i < area_1.size(); i++) {
            diff += population[area_1[i]];
        }
        for (int i = 0; i < area_2.size(); i++) {
            diff -= population[area_2[i]];
        }
        return diff >= 0 ? diff : diff * (-1);
    }
    return INT_MAX;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> population[i];
    }
    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        adj[i].push_back(num);
        for (int j = 0; j < num; j++) {
            int neighbor;
            cin >> neighbor;
            adj[i].push_back(neighbor);
        }
    }

    int result = INT_MAX;
    for (int i = 1; i < n / 2 + 1; i++) {
        for (int j = 1; j <= i; j++) {
            mask[j] = false;
        }
        for (int j = i + 1; j <= n; j++) {
            mask[j] = true;
        }

        do {
            int pop_diff = get_pop_diff();
            if (result > pop_diff) {
                result = pop_diff;
            }
        } while (next_permutation(mask + 1, mask + n + 1));
    }

    if (result == INT_MAX) {
        cout << -1;
    }
    else {
        cout << result;
    }
    
    return 0;
}