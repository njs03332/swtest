#include <iostream>
#include <climits>

// 가장 왼쪽에 있는 최댓값

using namespace std;

void print_max_indices(int arr[], int size);
int get_max_index(int arr[], int size);

int main() {
    int n;
    cin >> n;
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    print_max_indices(nums, n);
    return 0;
}

void print_max_indices(int arr[], int size) {
    if (size == 0) 
        return;
        
    int max_index = get_max_index(arr, size);
    cout << max_index + 1 << " ";
    print_max_indices(arr, max_index);
}
        
int get_max_index(int arr[], int size) {
    int max = INT_MIN;
    int max_index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max_index = i;
            max = arr[i];
        }
    }
    return max_index;
}