// 원판 돌리기  21/04/15
#include <iostream>

#define MAX_M 50
#define MAX_T 50
#define MAX_N 50

using namespace std;

struct round {
    int x, d, k;
};

int n, m, t;
int circles[MAX_N][MAX_M];
round rounds[MAX_T];
int cnt;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool erase[MAX_N][MAX_M];

void print_circles() {
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << circles[i][j] << " ";
        }
        cout << endl;
    }
}

bool in_range(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

void turn_one(int c, int d, int k) {
    int temp[m];
    if (d == 0) {
        for (int i = 0; i < m; i++) {
            temp[i] = circles[c][(i - k + m) % m];  // + m 안해주면 나머지가 음수됨!
        }
    }
    else {
        for (int i = 0; i < m; i++) {
            temp[i] = circles[c][(i + k) % m];
        }
    }

    for (int i = 0; i < m; i++) {
        circles[c][i] = temp[i];
    }
}

void turn(int r) {
    for (int i = 0; i < n; i++) {
        if ((i + 1) % rounds[r].x == 0) {
            turn_one(i, rounds[r].d, rounds[r].k);
        }
    }
}

int get_sum() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += circles[i][j];
        }
    }
    return sum;
}

double get_mean() {
    int sum = get_sum();
    return (double) sum / cnt;
}

void modify() {
    if (cnt != 0) {
        bool same_exist = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                erase[i][j] = false;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (circles[i][j] == 0) continue;
                for (int l = 0; l < 4; l++) {
                    int x = i + dx[l], y = (j + dy[l] + m) % m;
                    if (in_range(x, y) && circles[x][y] == circles[i][j]) {
                        erase[x][y] = erase[i][j] = true;
                        same_exist = true;
                    }
                }
            }
        }
        if (same_exist) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (erase[i][j]) {
                        circles[i][j] = 0;
                        cnt--;
                    }
                }
            }
        }

        else {
            double mean = get_mean();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (circles[i][j] == 0) continue;
                    if (circles[i][j] > mean) circles[i][j]--;
                    else if (circles[i][j] < mean) circles[i][j]++;
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> circles[i][j];
        }
    }
    cnt = n * m;
    for (int i = 0; i < t; i++) {
        int x, d, k;
        cin >> x >> d >> k;
        rounds[i] = (round) {x, d, k};
    }

    for (int r = 0; r < t; r++) {
        turn(r);
        // print_circles();
        modify();
        // print_circles();
    }

    int sum = get_sum();
    cout << sum;
    return 0;
}