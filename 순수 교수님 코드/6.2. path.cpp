// path.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

void floyd(int n, int *W, int *D, int *P)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            P[i * n + j] = -1;
            D[i * n + j] = W[i * n + j];
        }
       
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int dij = D[i * n + j];
                int dik = D[i * n + k];
                int dkj = D[k * n + j];
                if (dik < INT_MAX && dkj < INT_MAX && dij > dik + dkj) {
                    P[i * n + j] = k;
                    D[i * n + j] = dik + dkj;
                }
            }
        }
    }
}

void path(int n, int *P, int q, int r)
{
    if (P[q * n + r] >= 0) {
        path(n, P, q, P[q * n + r]);
        cout << 'v' << P[q * n + r];
        path(n, P, P[q * n + r], r);
    }
}


void showmatrix(int n, int* M)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << '\t' << M[i * n + j];
        cout << endl;
    }
}
int main()
{
    int W[5][5] = {
        { 0, 1, INT_MAX, 1, 5},
        {9, 0, 3, 2, INT_MAX},
        {INT_MAX, INT_MAX, 0, 4, INT_MAX},
        {INT_MAX, INT_MAX, 2, 0, 3},
        {3, INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int D[5][5], P[5][5];

    floyd(5, (int*)W, (int*)D, (int*)P);

    showmatrix(5, (int *)W);
    cout << endl;
    showmatrix(5, (int *)D);
    cout << endl;
    showmatrix(5, (int*)P);
    cout << endl;

    path(5, (int *)P, 0, 3);
    
    cout << endl;
}
