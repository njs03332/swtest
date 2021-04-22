#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string s;
int q, request, size;

void left() {
    char temp = s[0];
    for (int i = 0; i < size - 1; i++) {
        s[i] = s[i + 1];
    }
    s[size - 1] = temp;
}

void right() {
    char temp = s[size - 1];
    for (int i = size - 1; i > 0; i--) {
        s[i] = s[i - 1];
    }
    s[0] = temp;
}

void rev() {
    reverse(s.begin(), s.end());
}

int main() {
    cin >> s >> q;
    size = (int) s.size();
    int requests[q];
    for (int i = 0; i < q; i++) {
        cin >> requests[i];
    }
    int i = 0;
    while (q--) {
        request = requests[i++];
        if (request == 1) {
            left();
        }
        else if (request == 2) {
            right();
        }
        else if (request == 3) {
            rev();
        }
        cout << s << endl;
    }
    
}