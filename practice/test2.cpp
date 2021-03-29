#include <iostream>
#include <vector>

#define MAX_N 20
// 보고 말하는 수열

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    
    vector<int> seq[MAX_N];
    seq[1].push_back(1);

    for (int i = 2; i <= n; i++) {
        int curr_cnt = 1;
        for (int vec_i = 0; vec_i < seq[i - 1].size(); vec_i++) {
            if (vec_i == seq[i - 1].size() || seq[i - 1][vec_i] == seq[i - 1][vec_i + 1]) {
                seq[i].push_back(seq[i - 1][vec_i]);
                seq[i].push_back(curr_cnt);
                curr_cnt = 1;
            }
            else {
                curr_cnt++;
            }
        }
    }

    for (int i = 0; i < seq[n].size(); i++) {
        cout << seq[n][i];
    }
    return 0;
}