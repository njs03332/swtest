// 컨베이어 벨트 위의 로봇  21/04/21
#include <iostream>

#define MAX_N 100

using namespace std;

struct grid {
    int strong;
    bool robot;
};

int n, k;
int round = 0;
grid conveyer[2 * MAX_N + 1];
// index 확인

void print_conveyer() {
    cout << "conveyer" << endl;
    for (int i = 1; i <= 2 * n; i++) {
        cout << conveyer[i].strong << " ";
    }
    cout << endl;
}

void print_robot() {
    cout << "robot" << endl;
    for (int i = 1; i <= 2 * n; i++) {
        cout << conveyer[i].robot << " ";
    }
    cout << endl;
}

void belt_move() {
    // move last robot
    if (conveyer[n].robot) {
        conveyer[n].robot = false;
    }
    // move belt one
    grid temp = conveyer[2 * n];
    for (int i = 2 * n; i > 1; i--) {
        conveyer[i] = conveyer[i - 1];
    }
    conveyer[1] = temp;
}

void robot_move() {
    if (conveyer[n].robot) conveyer[n].robot = false;
    for (int i = n - 1; i >= 1; i--) {
        if (conveyer[i].robot && !conveyer[i + 1].robot && conveyer[i + 1].strong > 0) {
            conveyer[i + 1].robot = true;
            conveyer[i + 1].strong--;
            conveyer[i].robot = false;
        }
    }
}

void put_robot() {
    if (!conveyer[1].robot && conveyer[1].strong > 0) {
        conveyer[1].robot = true;
        conveyer[1].strong--;
    }
}

bool check_strong() {
    int num_weak = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (conveyer[i].strong == 0) num_weak++;
    }
    if (num_weak >= k) return false;
    return true;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= 2 * n; i++) {
        int a;
        cin >> a;
        conveyer[i] = (grid) {a, 0};
    }

    while (1) {
        round++;
        // cout << round << " round" << endl;
        belt_move();
        robot_move();
        put_robot();

        // print_conveyer();
        // print_robot();

        if (!check_strong()) break;
        // if (round == 30) break;
        // cout << endl;
    }

    cout << round;
    return 0;
}