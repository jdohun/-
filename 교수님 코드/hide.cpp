// hide.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>

using namespace std;

#define MAX 100000

void BFS(int src, int dst)
{
    queue<int> q;
    int depth = 0;
    cout << src << endl;
    int x;
    bool* visited = new bool[MAX + 1]{};
    int* path = new int[MAX + 1];
    q.push(src);

    visited[src] = true;

    while (!q.empty()) {
        x = q.front();
        q.pop();
        if (x == dst)
            break;
        //visited[x] = true;
        cout << x << endl;
        if (!visited[x - 1]) {
            q.push(x - 1);
            path[x - 1] = x;
            visited[x - 1] = true;
        }
        if (!visited[x + 1]) {
            q.push(x + 1);
            path[x + 1] = x;
            visited[x + 1] = true;
        }
        if (!visited[x * 2]) {
            q.push(x * 2);
            path[x * 2] = x;
            visited[x * 2] = true;
        }
    }
    cout << x << endl;
    int length = 0;
    while (x != src) {
        cout << '\t' << x;
        x = path[x];
        length++;
    }

    cout << '\t' << src << endl;
    cout << length << endl;

    delete visited;
    delete path;
}

int main()
{
    BFS(5, 17);
}

