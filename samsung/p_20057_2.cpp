#include <iostream>

#define MAX_N 499

using namespace std;

struct grid {
    int x, y;
};
int n;
int table[MAX_N][MAX_N];
grid loc;  // tornado location
int dir = 0;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
double rate[9] = {0.02, 0.02, 0.07, 0.07, 0.1, 0.1, 0.01, 0.01, 0.05};
int diff[2][10] = {{-2, 2, -1, 1, -1, 1, -1, 1, 0, 0}, 
                    {0, 0, 0, 0, -1, -1, 1, 1, -2, -1}};
int x_idx[4] = {0, 1, 0, 1};
int x_mul[4] = {1, -1, 1, 1};
int y_mul[4] = {1, 1, -1, 1};
int out_sand = 0;

void print_table() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << table[i][j] << " ";
            
        }
        cout << endl;
    }
    cout << endl;
}
bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

void move_sand(int x, int y, int sand) {
    if (in_range(x, y)) table[x][y] += sand;
    else out_sand += sand;
}

void solution() {
    bool is_first = true;
    for (int length = 1; ; length++) {
        if (!is_first) length--;
        is_first = !is_first;

        int curr_length = length;
        while (curr_length--) {
            loc.x += dx[dir];
            loc.y += dy[dir];
            int sand = table[loc.x][loc.y];
            table[loc.x][loc.y] = 0;

            int sand_moved = 0;
            for (int i = 0; i < 9; i++) {
                grid curr_grid;
                curr_grid.x = loc.x + (diff[x_idx[dir]][i] * x_mul[dir]);
                curr_grid.y = loc.y + (diff[1 - x_idx[dir]][i] * y_mul[dir]);
                move_sand(curr_grid.x, curr_grid.y, sand * rate[i]);                
                sand_moved += sand * rate[i];
            }
            grid alpha;
            alpha.x = loc.x + (diff[x_idx[dir]][9] * x_mul[dir]);
            alpha.y = loc.y + (diff[1 - x_idx[dir]][9] * y_mul[dir]);
            move_sand(alpha.x, alpha.y, sand - sand_moved);

            if (loc.x == 0 && loc.y == 0) return;
        }
        dir = (dir + 1) % 4;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> table[i][j];
        }
    }

    loc = (grid) {n / 2, n / 2};
    solution();

    cout << out_sand;
    return 0;
}