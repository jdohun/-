#include <iostream>

using namespace std;

void show(int* S, int low, int high, int i, int j)
{
    cout << i << ',' << j << ':';
    for (int k = low; k <= high; k++)
        cout << S[k] << ' ';
    cout << endl;
}

int partition(int* S, int low, int high)
{
    int pivotitem = S[low];
    int j = low;
    for (int i = low + 1; i <= high; i++) {
        if (S[i] < pivotitem) {
            j++;
            int temp = S[i];
            S[i] = S[j];
            S[j] = temp;
        }
        show(S, low, high, i, j);
    }
    
    int pivotpoint = j;

    S[low] = S[pivotpoint];
    S[pivotpoint] = pivotitem;

    show(S, low, high, 0, pivotpoint);

    return pivotpoint;
}

void quicksort(int* S, int low, int high)
{
    if (high > low) {
        int pivotpoint = partition(S, low, high);
        quicksort(S, low, pivotpoint - 1);
        quicksort(S, pivotpoint + 1, high);
    }
}

int main()
{
    int S1[8] = { 15, 22, 13, 27, 12, 10, 20, 25 };
    quicksort(S1, 0, 7);
    show(S1, 0, 7, 0, 0);

    int S2[8] = { 123, 34, 189, 56, 150, 12, 9, 240 };
    quicksort(S2, 0, 7);
    show(S2, 0, 7, 0, 0);
}
