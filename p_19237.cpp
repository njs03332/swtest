// 어른 상어  21/04/01
#include <iostream>
#include <vector>

#define MAX_N 20
#define MAX_M 400
#define MAX_K 1000
#define NUM_DIRS 4

using namespace std;

struct shark {
    int num, dir;
};
struct smell {
    int shark, time;
};
struct loc {
    int x, y;
};

int n, m, k;
int curr_dirs[MAX_M + 1];
loc curr_locs[MAX_M + 1];
smell smells[MAX_N][MAX_N] = {{0}};
int dir_priority[MAX_M + 1][NUM_DIRS + 1][NUM_DIRS];
int curr_time = 0;
vector<int> dead_sharks;

int dx[NUM_DIRS + 1] = {0, -1, 1, 0, 0};  // 순서: null, 상, 하, 좌, 우
int dy[NUM_DIRS + 1] = {0, 0, 0, -1, 1};

void print_locs() {
    for (int i = 1; i <= m; i++) {
        cout << i << " " << curr_locs[i].x << " " << curr_locs[i].y << endl;
    }
    cout << endl;
}

bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

bool is_dead(int s) {
    return curr_locs[s].x < 0;
}

void spill_own_smells() {
    for (int i = 1; i <= m; i++) {
        smell new_smell = {i, k};
        smells[curr_locs[i].x][curr_locs[i].y] = new_smell;
    }
}

int** get_candidates(int s) {
    // candidates[0]: no smell 
    // candidates[1]: my smell
    int **candidates = new int*[2];
    for (int i = 0; i < 2; i++) candidates[i] = new int[NUM_DIRS + 1];

    for (int i = 1; i <= NUM_DIRS; i++) {
        int x = curr_locs[s].x + dx[i], y = curr_locs[s].y + dy[i];
        if (in_range(x, y)) {
            if (!smells[x][y].time) {
                candidates[0][i] = 1;
            }
            else if (smells[x][y].shark == s) {
                candidates[1][i] = 1;
            }
        }
    }
    return candidates;
}

void move_shark(int s, int dir) {
    int curr_x = curr_locs[s].x, curr_y = curr_locs[s].y;
    int new_x = curr_x + dx[dir], new_y = curr_y + dy[dir];
    curr_locs[s].x = new_x;
    curr_locs[s].y = new_y;

    loc new_loc = {new_x, new_y};
    curr_locs[s] = new_loc;

    curr_dirs[s] = dir;
}

void move_sharks() {
    for (int i = 1; i <= m; i++) {
        if (is_dead(i)) continue;  // dead shark
        int **candidates = get_candidates(i);
        bool moved = false;
        for (int j = 0; j < 2; j++) {
            if (moved) break;
            for (int l = 0; l < NUM_DIRS; l++) {
                if (candidates[j][dir_priority[i][curr_dirs[i]][l]]) {
                    move_shark(i, dir_priority[i][curr_dirs[i]][l]);
                    moved = true;
                    break;
                }
            }
        }
    }
}

void kill_sharks() {
    for (int i = 1; i <= m; i++) {
        if (is_dead(i)) continue;  // dead shark
        for (int j = i + 1; j <= m; j++) {
            if (is_dead(j)) continue;
            if (curr_locs[i].x == curr_locs[j].x && curr_locs[i].y == curr_locs[j].y) {
                dead_sharks.push_back(j);
                loc null_loc = {-1, -1};
                curr_locs[j] = null_loc;
                break;
            }
        }
    }
}

void decrease_smells() {
    // 냄새 뿌리기 전, 냄새의 남은 시간 1씩 감소시키기 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (smells[i][j].time > 0) {
                smells[i][j].time--;
            }
        }
    }
}

void spill_smells() {
    for (int i = 1; i <= m; i++) {
        if (is_dead(i)) continue;
        smell new_smell = {i, k};
        smells[curr_locs[i].x][curr_locs[i].y] = new_smell;
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            int shark;
            cin >> shark;
            if (shark != 0) {
                loc l = {i, j};
                curr_locs[shark] = l;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> curr_dirs[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= NUM_DIRS; j++) {
            for (int l = 0; l < NUM_DIRS; l++) {
                cin >> dir_priority[i][j][l];
            }
        }
    }

    spill_own_smells();
    
    while (dead_sharks.size() < m - 1 && curr_time <= 1000) {
        move_sharks();
        // print_locs();
        kill_sharks();
        decrease_smells();
        spill_smells();
        curr_time++;
    }

    if (curr_time > 1000) cout << -1;
    else cout << curr_time;

    return 0;
}