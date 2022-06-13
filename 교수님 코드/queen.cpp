// queen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int col[256];

bool promising(int i) {
    int k = 0;
    bool sw = true;

    while (k < i && sw) {
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
            sw = false;
        k++;
    }
    return sw;
}
void queens(int i, int n) {
    if (promising(i)) {
        if (i == n - 1) {
            for (int j = 0; j < n; j++)
                cout << ' ' << col[j];
            cout << endl;
        }
        else {
            for (int j = 0; j < n; j++) {
                col[i + 1] = j;
                queens(i + 1, n);
            }
        }
    }
}

int main() {
    queens(-1, 4);
}

