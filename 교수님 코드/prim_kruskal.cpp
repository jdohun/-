// prim_kruskal.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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
#ifdef VERBOSE
        cout << '*' << j << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << nearest[i];
        cout << endl;
        for (int i = 1; i < n; i++)
            cout << '\t' << distance[i];
        cout << endl;
#endif
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

int find(int* parents, int index)
{
#if 1
    if (parents[index] == index)
        return index;
    else
        return find(parents, parents[index]);
#else
    return parents[index];
#endif
}

void kruskal(int n, int* W, int* D)
{
    int* edge;
    int* parents;

    edge = new int[n * (n - 1) / 2];
    parents = new int[n];

    int num_edges = 0;

    for (int i = 0; i < n * n; i++)
        D[i] = INT_MAX;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int index = i * n + j;
            int distance = W[index];
            if (distance < INT_MAX) {
                edge[num_edges++] = index;
            }
        }

    for (int i = 0; i < n; i++)
        parents[i] = i;

    for (int i = 0; i < num_edges; i++)
        for (int j = i + 1; j < num_edges; j++)
            if (W[edge[i]] > W[edge[j]]) {
                int temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }

    for (int e = 0; e < num_edges; e++) {
        int index = edge[e];
        int i = index / n;
        int j = index % n;
        int p = find(parents, i);
        int q = find(parents, j);
        if (p != q) {
            if (p < q)
                parents[q] = p;
            else
                parents[p] = q;
            D[index] = D[j * n + i] = W[index];
        }
    }
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
    showmatrix(5, (int*)W);
    cout << endl;

    cout << "prim" << endl;
    prim(5, (int*)W, (int*)D);
    cout << endl;
    showmatrix(5, (int*)D);
    cout << endl;

    cout << "kruscal" << endl;
    kruskal(5, (int*)W, (int*)D);
    showmatrix(5, (int*)D);
    cout << endl;

    cout << "W" << endl;
    showmatrix(10, (int*)W3);
    cout << endl;

    cout << "prim" << endl;
    prim(10, (int*)W3, (int*)D3);
    cout << endl;
    showmatrix(10, (int*)D3);
    cout << endl;

    kruskal(10, (int*)W3, (int*)D3);
    cout << "kruscal" << endl;
    showmatrix(10, (int*)D3);
    cout << endl;

}