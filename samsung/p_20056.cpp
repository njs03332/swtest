// 마법사 상어와 파이어볼  21/04/21
#include <iostream>
#include <vector>

#define MAX_N 50
#define NUM_DIRS 8

using namespace std;

struct ball {
    int mass, dir, speed;
};

int n, m, k;
vector<ball> table[MAX_N][MAX_N];
vector<ball> temp[MAX_N][MAX_N];

int dx[NUM_DIRS] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[NUM_DIRS ] = {0, 1, 1, 1, 0, -1, -1, -1};

void print_table() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < (int) table[i][j].size(); l++) {
                cout << table[i][j][l].mass << "," << table[i][j][l].dir << "," << table[i][j][l].speed << " ";
            }
            cout << " / ";
        }
        cout << endl;
    }
}

void move_balls() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j].clear();
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < (int) table[i][j].size(); l++) {
                ball curr_ball = table[i][j][l];
                int x = ((i + dx[curr_ball.dir] * curr_ball.speed) % n + n) % n;
                int y = ((j + dy[curr_ball.dir] * curr_ball.speed) % n + n) % n;
                temp[x][y].push_back(curr_ball);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[i][j] = temp[i][j];
        }
    }
}

void divide_balls() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num_balls = (int) table[i][j].size();
            if (num_balls <= 1) continue;

            int total_mass = 0, total_speed = 0, is_odd = 0;
            for (int l = 0; l < num_balls; l++) {
                total_mass += table[i][j][l].mass;
                total_speed += table[i][j][l].speed;
                if (table[i][j][l].dir % 2 == 1) is_odd++;
            }
            int new_mass = total_mass / 5;
            int new_speed = total_speed / num_balls;

            table[i][j].clear();
            if (new_mass == 0) continue;

            int start_dir;
            if (is_odd == num_balls || is_odd == 0) start_dir = 0;
            else start_dir = 1;
            for (int l = start_dir; l < NUM_DIRS; l += 2) {
                table[i][j].push_back((ball) {new_mass, l, new_speed});
            }
        }
    }
}

int calc_mass() {
    int total_mass = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < (int) table[i][j].size(); l++) {
                total_mass += table[i][j][l].mass;
            }
        }
    }
    return total_mass;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int r, c, mass, speed, dir;
        cin >> r >> c >> mass >> speed >> dir;
        table[r - 1][c - 1].push_back((ball) {mass, dir, speed});
    }
    // print_table();
    while (k--) {
        move_balls();
        divide_balls();
    }
    // print_table();

    cout << calc_mass();
    return 0;
}