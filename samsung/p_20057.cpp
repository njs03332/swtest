// 마법사 상어와 토네이도  21/03/30
#include <iostream>

#define MAX_N 499

using namespace std;

int n;
int A[MAX_N][MAX_N];
pair<int, int> curr_loc;
// left, down, right, up
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
// sand moving direction & portion of sand to move
int move_x[][10] = {{-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {0, 0, 1, 1, -1, -1, 0, 0, 2, 1}, 
                {-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {0, 0, 1, 1, -1, -1, 0, 0, 2, 1}};  // last is alpha
int move_y[][10] = {{0, 0, -1, -1, 1, 1, 0, 0, -2, -1}, {1, -1, 1, -1, 1, -1, 2, -2, 0, 0},
                {0, 0, 1, 1, -1, -1, 0, 0, 2, 1}, {1, -1, 1, -1, 1, -1, 2, -2, 0, 0}};
int sand[] = {7, 7, 10, 10, 1, 1, 2, 2, 5};
int temp_x[10] = {0};
int temp_y[10] = {0};
// sand going out
int out_sand = 0;

void make_tornado();
void move_sand(pair<int, int> y, int y_sand, int i);


int main() {
    // read input
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    curr_loc = make_pair(n / 2, n / 2);

    // make tornado
    make_tornado();
    
    // print out sand
    cout << out_sand;

    return 0;
}


void make_tornado() {
    // for each arrow
    for (int i = 0; i < 2 * n - 2; i++) {
        // arrow length: (i / 2 + 1)
        // direction: 4k left, 4k+1 down, 4k+2 right, 4k+3 up

        // number of moves in the same direction
        for (int j = 0; j < i / 2 + 1; j++) {
            pair<int, int> y = make_pair(curr_loc.first + dx[i % 4], curr_loc.second + dy[i % 4]);
            int y_sand = A[y.first][y.second];
            curr_loc = y;
            A[y.first][y.second] = 0;

            move_sand(y, y_sand, i);
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    cout << A[a][b] << " ";
                }
                cout << endl;
            }
        }
    }
    // last arrow: left, length n-1
    for (int i = 0; i < n - 1; i++) {
        pair<int, int> y = make_pair(curr_loc.first + dx[0], curr_loc.second + dy[0]);
        int y_sand = A[y.first][y.second];
        curr_loc = y;
        A[y.first][y.second] = 0;

        move_sand(y, y_sand, 0);
    }
}


void move_sand(pair<int, int> y, int y_sand, int i) {
    
    int total_moved = 0;
    for (int k = 0; k < 9; k++) {
        int to_move = y_sand * sand[k] / 100;
        int nx = y.first + move_x[i % 4][k];
        int ny = y.second + move_y[i % 4][k];
        if (nx >= n || ny >= n || nx < 0 || ny < 0) {
            out_sand += to_move;
        }
        else {
            A[nx][ny] += to_move;
        }
        total_moved += to_move;
    }
    // alpha
    int ax = y.first + move_x[i % 4][9];
    int ay = y.second + move_y[i % 4][9];
    if (ax >= n || ay >= n || ax < 0 || ay < 0) {
        out_sand += y_sand - total_moved;
    }
    else {
        A[ax][ay] += y_sand - total_moved;
    }
}

