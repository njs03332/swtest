#include <iostream>

#define MAX_N 100

using namespace std;

int n;
int blocks[MAX_N];
int seq[2][2];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> blocks[i];
    }
    for (int i = 0; i < 2; i++) {
        cin >> seq[i][0] >> seq[i][1];
    }
    
    for (int i = 0; i < 2; i++) {
        int len = seq[i][1] - seq[i][0] + 1;
        for (int b = seq[i][0] - 1; b < n - len; b++) {
            blocks[b] = blocks[b + len];
        }
        n -= len;
    }
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << blocks[i] << endl;
    }
    return 0;
}