#include <iostream>
#include <climits>

using namespace std;

// least n

int main() {
    int n;
    cin >> n;
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int min = INT_MAX;
    int num_min = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] < min) {
            min = nums[i];
            num_min = 1;
        }
        else if (nums[i] == min) {
            num_min++;
        }
    }
    cout << min << " " << num_min;
    return 0;    
}