// 모노미노도미노 2  21/03/31
#include <iostream>

#define MAX_N 1000
#define TILE_NUM 3

using namespace std;

int n = 0;
int rows = 4;
int cols = 6;
bool table[2][4][6] = {{{false}}};  // blue, green
int points = 0;
bool block_shapes[TILE_NUM + 1][2][2] = {
    {},
    {{1, 0}, {0, 0}},
    {{1, 1}, {0, 0}}, 
    {{1, 0}, {1, 0}}
};


void print_table() {
    for (int i = 0; i < 2; i++) {
        cout << "table " << i << endl;
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cout << table[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool is_full(int table_num, int col) {
    for (int row = 0; row < rows; row++) {
        if (!table[table_num][row][col]) {
            return false;
        }
    }
    return true;
}

void delete_col(int table_num, int col) {
    for (int row = 0; row < rows; row++) {
        table[table_num][row][col] = false;
    }
}

void move_right(int table_num, int col) {
    for (int row = 0; row < rows; row++) {
        table[table_num][row][col + 1] = table[table_num][row][col];
        table[table_num][row][col] = false;
    }
}

void check_full() {
    for (int table_num = 0; table_num < 2; table_num++) {
        for (int col = 0; col < cols; col++) {
            if (is_full(table_num, col)) {
                delete_col(table_num, col);
                points++;
                for (int i = col - 1; i >= 0; i--) {
                    move_right(table_num, i);
                }
            }
        }
    }
}

bool block_exists(int table_num, int col) {
    for (int row = 0; row < rows; row++) {
        if (table[table_num][row][col]) {
            return true;
        }
    }
    return false;
}

void check_light() {
    // cout << "check_light" << endl;
    for (int table_num = 0; table_num < 2; table_num++) {
        for (int col = 0; col < 2; col++) {
            if (block_exists(table_num, col)) {
                // cout << "block exists" << endl;
                delete_col(table_num, cols - 1);
                for (int i = cols - 2; i >= 0; i--) {
                    move_right(table_num, i);
                }
            }
        }
    }
}

bool in_range(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool col_avail(int col, int table_num, int t, int row) {
    for (int dx = 0; dx < 2; dx++) {
        for (int dy = 0; dy < 2; dy++) {
            if (block_shapes[t][dx][dy]) {
                int x = row + dx;
                int y = col + dy;
                if (!in_range(x, y) || table[table_num][x][y]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void put(int table_num, int t, int row, int col) {
    for (int dx = 0; dx < 2; dx++) {
        for (int dy = 0; dy < 2; dy++) {
            if (block_shapes[t][dx][dy]) {
                int x = row + dx;
                int y = col + dy;
                table[table_num][x][y] = true;
            }
        }
    }
}

void put_block(int table_num, int t, int row) {
    for (int i = 0; i < cols; i++) {
        // if next column is unavailable, put the block
        if (!col_avail(i + 1, table_num, t, row)) {
            // put the block
            put(table_num, t, row, i);
            break;
        }
    }
}

void simulate(int t, int x, int y) {
    // put block on blue board
    put_block(0, t, x);

    // put block on green board -> 90 degrees rotate
    if (t == 1) {
        put_block(1, t, rows - 1 - y);
    }
    else if (t == 2) {
        put_block(1, 3, rows - 2 - y);
    }
    else if (t == 3) {
        put_block(1, 2, rows - 1 - y);
    }
    
    check_full();
    check_light();
}

int count_blocks() {
    int cnt = 0;
    for (int table_num = 0; table_num < 2; table_num++) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (table[table_num][row][col]) {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

int main() {
    // read input
    cin >> n;
    while (n--) {
        int t, x, y;
        cin >> t >> x >> y;
        simulate(t, x, y);
    }
    int num_blocks = count_blocks();
    cout << points << endl << num_blocks;

    return 0;
}