// 경사로  21/04/05
#include <iostream>
#include <cmath>
#include <vector>

#define MAX_N 100
#define MAX_L 100

using namespace std;

int n, l;
int map[2][MAX_N][MAX_N];  // 0: map, 1: reversed map
int avail_roads = 0;


void find_roads() {
    for (int dir = 0; dir < 2; dir++) {
        for (int i = 0; i < n; i++) {
            int curr_num = map[dir][i][0];
            int curr_cnt = 1;
            int possible = true;
            bool checking = false;
            for (int j = 1; j < n; j++) {
                int next_num = map[dir][i][j];
                if (curr_num == next_num) {
                    curr_cnt++;
                    if (checking && curr_cnt == l) {
                        // put triangle
                        curr_cnt = 0;
                        checking = false;
                    }
                    continue;
                }
                else if (abs(curr_num - next_num) > 1 || checking) {
                    possible = false;
                    break;
                }
                else {
                    if (curr_num > next_num) {
                        // 이번부터 연속으로 l개가 같아야 함.
                        if (l == 1) {
                            // put triangle
                            curr_cnt = 0;
                            curr_num = next_num;
                            continue;
                        }
                        checking = true;
                    }
                    else {
                        if (curr_cnt < l) {  // not able to put triangle
                            possible = false;
                            break; 
                        }
                    }
                    curr_num = next_num;
                    curr_cnt = 1;
                }
            }
            if (possible) {
                if (checking && curr_cnt != l) continue;
                avail_roads++;
            }
        }
    }
}

int main() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[0][i][j];
            map[1][j][i] = map[0][i][j];
        }
    }

    find_roads();
    // 한쪽부터 쭉 읽어. 같으면 ㄱㅊ. 다르면, 1 차이만 나는지 확인. 아니면 pass.
    // 1 차이만 나면, 더 작은 애 쪽에 l개가 연속되어있는지를 확인. 
    // 쭉 읽으면서 몇 개 연속인지를 변수에 저장해둠. curr_cnt
    // 만약 읽던 쪽이 작으면 curr_cnt 확인, l보다 크거나 같으면 괜춘. 
    // 거기 놓기로 했으면, 마킹을 해줘야 함. -> curr_cnt를 0으로 만들어줌.
    // 한 길 내에서만 경사로가 겹치면 안되는 것

    cout << avail_roads;
    return 0;
}