// 백준 20058  21/03/29
// 마법사 상어와 파이어스톰

#include <iostream>
#include <cmath>
#include <queue>
#include <utility>

#define MAX_N 64
#define MAX_Q 1000

using namespace std;

int n, q;
int n_2;
int A[MAX_N][MAX_N], L[MAX_Q];
bool visited[MAX_N][MAX_N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void rotate(int j, int k, int l);
bool has_ice(int a, int b);
int BFS(int a, int b);
void firestorm(int l);
int count_ice();
int get_largest_island();


int main() {
    // read input
    cin >> n >> q;
    n_2 = pow(2, n);
    for (int i = 0; i < n_2; i++) {
        for (int j = 0; j < n_2; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < q; i++) {
        cin >> L[i];
    }

    // firestorm
    for (int i = 0; i < q; i++) {
        int l = L[i];
        firestorm(l);
    }
    
    // print total ice
    cout << count_ice();

    // print largest island
    cout << " " << get_largest_island();

    return 0;
}


void firestorm(int l) {
    // rotate
    int l_2 = pow(2, l);
    for (int j = 0; j < n_2; j += l_2) {
        for (int k = 0; k < n_2; k += l_2) {
            rotate(j, k, l);
        }
    }

    // check for grid w/o 3 or more ice neighbors
    pair<int, int> no_ice[n_2 * n_2];
    int no_ice_cnt = 0;
    for (int j = 0; j < n_2; j++) {
        for (int k = 0; k < n_2; k++) {
            if (A[j][k] != 0) {
                if (!has_ice(j, k)) {
                    no_ice[no_ice_cnt] = make_pair(j, k);
                    no_ice_cnt++;
                }
            }
        }
    }
    // melt 1 ice for those grids
    for (int i = 0; i < no_ice_cnt; i++) {
        A[no_ice[i].first][no_ice[i].second]--;
    }
    
}


void rotate(int a, int b, int l) {  
    int half = pow(2, l) / 2;
    // (a, b) : top left end of the sub grid we are working on
    // iterate through each square frame from the center
    for (int r = 1; r <= half; r++) {
        int num_elem = 2 * r - 1;
        int top[num_elem], right[num_elem], bottom[num_elem], left[num_elem];
        // l_2 / 2 - r  ~  k + l_2 / 2 + r - 1

        int x_start = a + half - r;
        int x_end = a + half + r - 1;
        int y_start = b + half - r;
        int y_end = b + half + r - 1;
        // first, save elements in array
        // 1) top side 
        int idx = 0;
        for (int i = y_start; i <= y_end; i++) {
            top[idx] = A[x_start][i];
            idx++;
        }
        // 2) right side
        idx = 0;
        for (int i = x_start; i <= x_end; i++) {
            right[idx] = A[i][y_end];
            idx++;
        }
        // 3) bottom side
        idx = 0;
        for (int i = y_end; i >= y_start; i--) {
            bottom[idx] = A[x_end][i];
            idx++;
        }
        // 4) left side
        idx = 0;
        for (int i = x_end; i >= x_start; i--) {
            left[idx] = A[i][y_start];
            idx++;
        }

        // second, move elements
        // 1) top side
        idx = 0;
        for (int i = y_start; i <= y_end; i++) {
            A[x_start][i] = left[idx];
            idx++;
        }
        // 2) right side
        idx = 0;
        for (int i = x_start; i <= x_end; i++) {
            A[i][y_end] = top[idx];
            idx++;
        }
        // 3) bottom side
        idx = 0;
        for (int i = y_end; i >= y_start; i--) {
            A[x_end][i] = right[idx];
            idx++;
        }
        // 4) left side
        idx = 0;
        for (int i = x_end; i >= x_start; i--) {
            A[i][y_start] = bottom[idx];
            idx++;
        }
    }
}


bool has_ice(int a, int b) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        int nx = a + dx[i];
        int ny = b + dy[i];
        if (nx >= 0 && ny >= 0 && nx < n_2 && ny < n_2) {
            if (A[nx][ny] > 0) {
                cnt++;
            }
        }
    }

    if (cnt < 3) 
        return false;
    return true;
}


int count_ice() {
    int ice_cnt = 0;
    for (int i = 0; i < n_2; i++) {
        for (int j = 0; j < n_2; j++) {
            ice_cnt += A[i][j];
        }
    }
    return ice_cnt;
}


int get_largest_island() {
    int largest_sum = 0;
    for (int i = 0; i < n_2; i++) {
        for (int j = 0; j < n_2; j++) {
            if (A[i][j] != 0 && !visited[i][j]) {
                int sum = BFS(i, j);
                if (sum > largest_sum) {
                    largest_sum = sum;
                }
            }
        }
    }
    return largest_sum;
}


int BFS(int a, int b) {
    queue<pair<int, int> > waiting;
    waiting.push(make_pair(a, b));
    visited[a][b] = true;
    int cnt = 1;

    while (waiting.empty() == 0) {
        int x = waiting.front().first;
        int y = waiting.front().second;
        waiting.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n_2 && ny < n_2) {
                if (A[nx][ny] != 0 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    waiting.push(make_pair(nx, ny));
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

