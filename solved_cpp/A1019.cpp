#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    
    // 바로 직전까지 구하자 0 ~ 999999
    int x = N;
    int M = 0;
    while (x > 10) {
        x /= 10;
        M++;
    }
    
    // zero cnt
    int D[10][10] = { 0, };
    // 기본 데이터
    for (int i = 0; i < 10; i++) {
        D[0][i] = 1;
    }
    
    int z1 = 0, z2 = 1;
    for (int k = 1; k <= M; k++) {
        // 첫자리수
        for (int i = 0; i < 10; i++) {
            // 숫자의 개수
            if (k == 1) {
                D[k][i] = D[k - 1][i];
                continue;
            }
            for (int j = 0; j < 10; j++) {
                D[k][i] += D[k - 1][i];
                if (j != 0 && i == j) {
                    D[k][0] += z1;
                    D[k][j] += z2;
                }
            }
        }
        z1 += z2; z2 *= 10;
        if (z1 == 1) z1 = 0;
    }
    
    // last pang
    x = N;
    int idx = 0;
    while (x > 0) {
        // 각 자리수 까지 반복
        int v = x % 10;
        for (int i = 0; i < v; i++) {
            D[M + 1][i] = D[idx][i];
        }
        idx++;
        x /= 10;
    }
    
    D[M + 1][0]--;
    for (int i = 0; i < 10; i++) {
        cout << D[M + 1][i] << " ";
    }
    cout << "\n";
    
    
    
    // 19281
    // 9999 + 9282
}
