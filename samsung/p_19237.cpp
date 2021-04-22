// 어른 상어  21/04/01
#include <iostream>
#include <vector>

#define MAX_N 20
#define MAX_M 400
#define MAX_K 1000
#define NUM_DIRS 4

using namespace std;

struct shark {
    int x, y, dir;
    int dir_priority[NUM_DIRS + 1][NUM_DIRS];
    bool is_dead;
};
struct smell {
    int shark, time;
};

int n, m, k;
shark sharks[MAX_M + 1];
smell smells[MAX_N][MAX_N] = {{0}};
int curr_time = 0;
int num_dead = 0;

int dx[NUM_DIRS + 1] = {0, -1, 1, 0, 0};  // 순서: null, 상, 하, 좌, 우
int dy[NUM_DIRS + 1] = {0, 0, 0, -1, 1};


bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

int** get_candidates(int s) {
    // candidates[0]: no smell 
    // candidates[1]: my smell
    int **candidates = new int*[2];
    for (int i = 0; i < 2; i++) candidates[i] = new int[NUM_DIRS + 1];

    for (int i = 1; i <= NUM_DIRS; i++) {
        int x = sharks[s].x + dx[i], y = sharks[s].y + dy[i];
        if (in_range(x, y)) {
            if (smells[x][y].time == 0)
                candidates[0][i] = 1;
            else if (smells[x][y].shark == s)  // time != 0 && shark == s
                candidates[1][i] = 1;
        }
    }
    return candidates;
}

void move_shark(int s, int dir) {
    sharks[s].x += dx[dir];
    sharks[s].y += dy[dir];
    sharks[s].dir = dir;
}

void move_sharks() {
    for (int i = 1; i <= m; i++) {
        if (sharks[i].is_dead) continue;
        int **candidates = get_candidates(i);
        bool moved = false;
        for (int j = 0; j < 2; j++) {
            if (moved) break;
            for (int l = 0; l < NUM_DIRS; l++) {
                int curr_dir = sharks[i].dir_priority[sharks[i].dir][l];
                if (candidates[j][curr_dir]) {
                    move_shark(i, curr_dir);
                    moved = true;
                    break;
                }
            }
        }
    }
}

void kill_shark(int s) {
    sharks[s].is_dead = true;
    num_dead++;
}

void kill_sharks() {
    for (int i = 1; i <= m; i++) {
        if (sharks[i].is_dead) continue;
        for (int j = i + 1; j <= m; j++) {
            if (sharks[j].is_dead) continue;
            if (sharks[i].x == sharks[j].x && sharks[i].y == sharks[j].y) {
                kill_shark(j);  // kill bigger shark
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
        if (sharks[i].is_dead) continue;
        smells[sharks[i].x][sharks[i].y] = (smell) {i, k};
    }
}

int main() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            smells[i][j] = (smell) {0, 0};
        }
    }
    cin >> n >> m >> k;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            if (a != 0) {
                sharks[a] = (shark) {i, j};
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> sharks[i].dir;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= NUM_DIRS; j++) {
            for (int l = 0; l < NUM_DIRS; l++) {
                cin >> sharks[i].dir_priority[j][l];
            }
        }
    }

    spill_smells();
    while (num_dead < m - 1 && curr_time <= 1000) {
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