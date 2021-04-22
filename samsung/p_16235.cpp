// 나무 재테크  21/04/16
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10

using namespace std;

int n, m, k;
int nut[MAX_N][MAX_N];
int A[MAX_N][MAX_N];
vector<int> land[MAX_N][MAX_N];
vector<int> dead[MAX_N][MAX_N];
int new_trees[MAX_N][MAX_N];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

void spring() {
    // initialize dead
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dead[i][j].clear();
        }
    }

    // spring
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sort(land[i][j].begin(), land[i][j].end());
            for (int l = 0; l < (int) land[i][j].size(); l++) {
                int age = land[i][j][l];
                if (nut[i][j] < age) {
                    dead[i][j].push_back(age);
                    land[i][j].erase(land[i][j].begin() + l);
                    l--;  // for 문 변수도 이렇게 변화시켜줄 수 있음 ! for loop의 condition은 매 loop마다 계산됨
                }
                else {
                    nut[i][j] -= age;
                    land[i][j][l]++;
                }
            }
        }
    }
}

void summer() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < (int) dead[i][j].size(); l++) {
                nut[i][j] += dead[i][j][l] / 2;
            }
        }
    }
}

void autumn() {
    // initialize new_trees
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_trees[i][j] = 0;
        }
    }

    // autumn
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < (int) land[i][j].size(); l++) {
                if (land[i][j][l] % 5 != 0) continue;
                for (int p = 0; p < 8; p++) {
                    int x = i + dx[p], y = j + dy[p];
                    if (!in_range(x, y)) continue;
                    new_trees[x][y]++;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < new_trees[i][j]; l++) {
                land[i][j].push_back(1);
            }
        }
    }
}

void winter() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nut[i][j] += A[i][j];
        }
    }
}

int get_tree_cnt() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt += (int) land[i][j].size();
        }
    }
    return cnt;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        land[x - 1][y - 1].push_back(z);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nut[i][j] = 5;
        }
    }
    
    for (int i = 0; i < k; i++) {
        spring();
        summer();
        autumn();
        winter();
    }
    cout << get_tree_cnt();
    return 0;

}