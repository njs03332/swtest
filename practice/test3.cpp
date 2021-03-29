#include <iostream>
#include <vector>

#define MAX_N 20

using namespace std;

int main() {
	int n;
	vector<int> seq[MAX_N + 1];
	
	cin >> n;
	
    // 첫 번째 수열에 첫 번째 원소는 1입니다.
    seq[1].push_back(1);
	
    // i번째 수열이 이미 완성되어 있을 때, i + 1번째 수열을 구합니다.
	for(int i = 1; i < n; i++) {
		int contiguous_cnt = 1;
		for(int j = 1; j <= (int) seq[i].size(); j++) {
            // 끝에 다다랐거나 인접한 두 숫자가 다르다면
            // 방금 전까지의 묶음에 해당하는 정보를
            // i + 1 번째 수열에 추가해줍니다.
			if(j == (int) seq[i].size() || seq[i][j] != seq[i][j - 1]) {
				seq[i + 1].push_back(seq[i][j - 1]);
				seq[i + 1].push_back(contiguous_cnt);
				contiguous_cnt = 1;
			}
            // 인접한 두 숫자가 같다면
            // 지금까지 연속하여 같은 숫자가 나온 횟수를 갱신합니다.
            else
                contiguous_cnt++;
		}
	}
	
    // n번째 수열을 출력합니다.
	for(int j = 0; j < (int) seq[n].size(); j++)
		cout << seq[n][j];
	return 0;
}