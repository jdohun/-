// Dijkstra.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include <iostream>

using namespace std;

void showmatrix(int n, int* M)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int value = M[i * n + j];
            if (value < INT_MAX)
                cout << '\t' << value;
            else
                cout << "\tINF";
        }
        cout << endl;
    }
}

void prim(int n, int* W, int* D)
{
    int* nearest;
    int* distance;
    nearest = new int[n];
    distance = new int[n];
    int F = 0;
    int vnear;

    for (int i = 0; i < n * n; i++)
        D[i] = INT_MAX;


    for (int i = 1; i < n; i++) {
        nearest[i] = 0;
        distance[i] = W[i];
    }

    for (int j = 0; j < n - 1; j++) {
        cout << '*' << j << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << nearest[i];
        cout << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << distance[i];
        cout << endl;

        int min = INT_MAX;
        for (int i = 1; i < n; i++) {
            if (distance[i] >= 0 && distance[i] < min) {
                min = distance[i];
                vnear = i;
            }
        }
        D[vnear * n + nearest[vnear]] = min;
        D[nearest[vnear] * n + vnear] = min;

        distance[vnear] = -1;
        for (int i = 1; i < n; i++) {
            if (W[vnear * n + i] < distance[i]) {
                distance[i] = W[vnear * n + i];
                nearest[i] = vnear;
            }
        }
    }

}

void dijikstra(int n, int* W, int* D)
{
    int* nearest;
    int* distance;
    nearest = new int[n];
    distance = new int[n];
    int F = 0;
    int vnear;

    for (int i = 0; i < n * n; i++)
        D[i] = INT_MAX;


    for (int i = 1; i < n; i++) {
        nearest[i] = 0;
        distance[i] = W[i];
    }

    for (int j = 0; j < n - 1; j++) {
        cout << '*' << j << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << nearest[i];
        cout << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << distance[i];
        cout << endl;

        int min = INT_MAX;
        for (int i = 1; i < n; i++) {
            if (distance[i] >= 0 && distance[i] < min) {
                min = distance[i];
                vnear = i;
            }
        }

        D[vnear] = min;
        cout << nearest[vnear] << "to" << vnear << endl;
        
        for (int i = 1; i < n; i++) {
            if (distance[vnear] < INT_MAX && W[vnear * n + i] < INT_MAX && distance[vnear] + W[vnear * n + i] < distance[i]) {
                distance[i] = distance[vnear] + W[vnear * n + i];
                nearest[i] = vnear;
                D[vnear * n + i] = W[vnear * n + i];
            }
        }
        distance[vnear] = -1;
    }

    cout << "result\n";
    for (int i = 1; i < n; i++) {
        cout << nearest[i] << endl;
    }

    for (int i = 1; i < n; i++) {
        cout << i << ":";
        int j = i;
        do {
            j = nearest[j];
            cout << '\t' << j;
        } while (j > 0);
        cout << endl;
    }

}
int add(int a, int b)
{
    return a + b;
}
int add(int &a, int &b)
{
    return a + b;
}

int main()
{
    int W[5][5] = {
        { 0, 1, 3, INT_MAX, INT_MAX},
        {1, 0, 3, 6, INT_MAX},
        {3, 3, 0, 4, 2},
        {INT_MAX, 6, 4, 0, 5},
        {INT_MAX, INT_MAX, 2, 5, 0}
    };
    int D[5][5];
    int W2[5][5] = {
        { 0, 7, 4, 6, 1},
        {INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, 2, 0, 5, INT_MAX},
        {INT_MAX, 3, INT_MAX, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 1, 0}
    };
    int W3[10][10] = {
        { 0, 32, INT_MAX,17, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
        { 32, 0, INT_MAX, INT_MAX, 45, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
        { INT_MAX, INT_MAX, 0, 18, INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX, INT_MAX},
        { 17, INT_MAX, 18, 0, 10, INT_MAX, INT_MAX, 3, INT_MAX, INT_MAX},
        { INT_MAX, 45, INT_MAX, 10, 0, 28, INT_MAX, INT_MAX, 25, INT_MAX},
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX, 28, 0, INT_MAX, INT_MAX, INT_MAX, 6},
        { INT_MAX, INT_MAX, 5,INT_MAX, INT_MAX, INT_MAX, 0, 59, INT_MAX, INT_MAX},
        { INT_MAX, INT_MAX, INT_MAX, 3, INT_MAX, INT_MAX, INT_MAX, 0, 4, INT_MAX},
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX, 25, INT_MAX, INT_MAX, 4, 0, 12},
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 6, INT_MAX, INT_MAX, 12, 0},
    };
    int D3[10][10];
    cout << "W" << endl;
    showmatrix(5, (int*)W2);

    dijikstra(5, (int*)W2, (int*)D);
    //kruskal2(5, (int*)W, (int*)D);

    showmatrix(5, (int*)D);

    cout << endl;

    cout << "W" << endl;
    showmatrix(10, (int*)W3);

    dijikstra(10, (int*)W3, (int*)D3);
    //kruskal2(5, (int*)W, (int*)D);

    showmatrix(10, (int*)D3);

    cout << endl;
    int a = 1, b = 2;
    cout << add(a, 3) << endl;
    cout << add(1, b) << endl;
}
