// tsp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

void shortestpath(int n, int* W, int* D, int* P, int i, int A, int& minj)
{
    int numSubset = 1 << (n - 1);
    int min = INT_MAX;
    minj = 0;

    for (int j = 1; j < n; j++) {
        int vj = 1 << (j - 1);
        int value;
        if (vj & A) {
            int w, d;

            int vnj = A & (~vj);
            w = W[i * n + j];
            d = D[j * numSubset + vnj];
            if (w >= INT_MAX || d >= INT_MAX)
                value = INT_MAX;
            else
                value = w + d;
            if (value < min) {
                min = value;
                minj = j;
            }
        }
    }
    D[i * numSubset + A] = min;
    P[i * numSubset + A] = minj;
}

void tsp(int n, int *W, int *P, int& minlength)
{
    int* D;
    int numSubset = 1 << (n - 1);
    D = new int [n * numSubset];

    for (int i = 1; i < n; i++)
        D[i * numSubset] = W[i * n];
    
    
    for (int A = 1; A < numSubset; A++) {
        for (int i = 1; i < n; i++) {
            int vi = 1 << (i - 1);
            if (vi & A)
                continue;
            int minj;
            shortestpath(n, W, D, P, i, A, minj);
        }
    }

    int minj;
    int A = numSubset - 1;
    shortestpath(n, W, D, P, 0, A, minj);

    minlength = D[A];
}

void showPath(int n, int* P, int i, int A)
{
    int numSubset = 1 << (n - 1);
    while (A) {
        int next = P[i * numSubset + A];
        cout << next;
        int vnext = 1 << (next - 1);
        A &= ~vnext;
        i = next;
    }
    cout << endl;
}

int main()
{
    int W1[4][4] = { 0, 2, 9, INT_MAX, 1, 0, 6, 4, INT_MAX, 7, 0, 8, 6, 3, INT_MAX, 0 };
    int P1[4][8];
    int W2[4][4] = { 0, 10, 15, 20, 5, 0, 9, 10, 6, 13, 0, 12, 8, 8, 9, 0 };
    int P2[4][8];
    int W3[5][5] = { 0, 14, 4, 10, 20, 
                     14, 0, 7, 8, 7,
                     4, 5, 0, 7, 16,
                     11, 7, 9, 0, 2,
                     18, 7, 17, 4, 0};
    int P3[5][16];

    int W4[8][8] = { 0, 4, 8, INT_MAX, 1, 4, 5, 14,
                       1, 0, 2, 4, 5, 8, INT_MAX, 10,
                       INT_MAX, 3, 0, 9, 6, 7, 8, 10,
                       INT_MAX, 4, 4, 0, 8, 10, 11, 14,
                        5, 4, 6, 3, 0, 8, 10, 11,
                        8, 9, 10, 4, 9, 0, 12, 1,
                        3, 5, 4, INT_MAX, 3, 9, 0, 7,
                        13, 5, 4, 8, 3, 2, INT_MAX, 0
    };
    int P4[8][128];
       
    int minlength;

    tsp(4, (int *)W1, (int *)P1, minlength);
    
    cout << minlength << endl;

    showPath(4, (int *)P1, 0, (1 << 3) - 1);
    

    tsp(4, (int*)W2, (int*)P2, minlength);

    cout << minlength << endl;

    showPath(4, (int*)P2, 0, (1 << 3) - 1);


    tsp(5, (int*)W3, (int*)P3, minlength);

    cout << minlength << endl;

    showPath(5, (int*)P3, 0, (1 << 4) - 1);



    tsp(8, (int*)W4, (int*)P4, minlength);

    cout << minlength << endl;

    showPath(8, (int*)P4, 0, (1 << 7) - 1);
}
