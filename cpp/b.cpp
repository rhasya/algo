#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int main() {
    random_device rd;
    srand(rd());

    vector<int> A;
    for (int i = 1; i <= 100000; i++) {
        A.push_back(i);
    }
    random_shuffle(A.begin(), A.end());

    cout << 100000 << ' ' << 5000 << '\n';
    for (int i = 0; i < 100000; i++) {
        if (i == 0) cout << A[i];
        else cout << ' ' << A[i];
    }
    cout << '\n';
    for (int i = 1; i <= 5000; i++) {
        cout << "1 100000 " << i + 3000 << '\n';
    }
    
}