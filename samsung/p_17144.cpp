// 미세먼지 안녕!  21/04/10
#include <iostream>
#include <vector>

#define MAX_C 50

using namespace std;

int r = 0;
int c = 0;
int t;
vector<int> room[50];    // MAX_C로 하면 안되나
int curr_time = 0;
int purifiers[2];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


void print_room() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << room[j][i] << " ";
        }
        cout << endl;
    }
}

bool in_range(int x, int y) {
    if (x < 0 || y < 0 || x >= r || y >= c) return false;
    for (int i = 0; i < 2; i++) {
        if (y == 0 && x == purifiers[i]) return false;
    }
    return true;
}

void spread_dust() {
    vector<int> diff[MAX_C];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            diff[j].push_back(0);
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                int cnt = 0;
                int dust = room[j][i] / 5;
                if (in_range(x, y)) {
                    diff[y][x] += dust;
                    cnt++;
                }
                diff[j][i] -= cnt * dust;
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            room[j][i] += diff[j][i];
        }
    }
}

void move_down(int start, int end, int col) {
    for (int i = start; i > end; i--) {
        room[col][i] = room[col][i - 1];
    }
}

void move_left(int start, int end, int row) {
    for (int i = start; i < end; i++) {
        room[i][row] = room[i + 1][row];
    }
}

void move_up(int start, int end, int col) {
    for (int i = start; i < end; i++) {
        room[col][i] = room[col][i + 1];
    }
}

void move_right(int start, int end, int row) {
    for (int i = start; i > end; i--) {
        room[i][row] = room[i - 1][row];
    }
}

void purify() {
    move_down(purifiers[0] - 1, 0, 0);
    move_left(0, c - 1, 0);
    move_up(0, purifiers[0], c - 1);
    move_right(c - 1, 0, purifiers[0]);

    move_up(purifiers[1] + 1, r - 1, 0);
    move_left(0, c - 1, r - 1);
    move_down(r - 1, purifiers[1], c - 1);
    move_right(c - 1, 0, purifiers[1]);
}

int get_total_dust() {
    int total_dust = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            total_dust += room[j][i];
        }
    }
    return total_dust;
}

int main() {
    cin >> r >> c >> t;
    int pur_i = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int dust;
            cin >> dust;
            if (dust == -1) {
                purifiers[pur_i] = i;
                pur_i++;
                room[j].push_back(0);
            }
            else if (dust != 0) {
                room[j].push_back(dust);
            }
            else {
                room[j].push_back(0);
            }
        }
    }

    int curr_time = 0;
    while (curr_time < t) {
        spread_dust();
        purify();
        curr_time++;
    }
    cout << get_total_dust();

    return 0;
}