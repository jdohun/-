// beer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>

using namespace std;

#define MAX 100000 // 십만

typedef struct {
    int id;
    int x, y;
} Node;

int manhathan(Node a, Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void beer(int n, Node* cvs) {
    queue<Node> q;
    int depth = 0;
    Node node;
    Node& src = cvs[0];
    Node& dst = cvs[n - 1];

    bool* visited = new bool[MAX + 1]{};
    int* path = new int[MAX + 1];
    bool found = false;
    q.push(src);


    while (!q.empty()) {
        node = q.front();
        q.pop();

        if (manhathan(node, dst) <= 1000) {
            cout << "found\n";
            found = true;
            break;
        }

        for (int i = 1; i < n - 1; i++) {
            if (manhathan(node, cvs[i]) <= 1000) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(cvs[i]);
                    path[i] = node.id;
                }
            }
        }
    }

    if (found) {
        int length = 0;
        int x = node.id;
        cout << x << endl;
        while (x != src.id) {
            cout << '\t' << x;
            x = path[x];
            length++;
        }

        cout << '\t' << src.id << endl;
        cout << length << endl;
    }
    delete visited;
    delete path;
}

int path[100] = {};

void  dfs(int n, Node* node, int a, int depth) {
    if (a == n - 1) {
        cout << "found\n";
        for (int i = 0; i < depth; i++)
            cout << '\t' << path[i];
        cout << endl;
        return;
    }

    for (int i = 1; i < n; i++) {
        if (a == i)
            continue;
        bool visited = false;
        for (int j = 1; j < depth; j++) {
            if (path[j] == i) {
                visited = true;
                break;
            }
        }
        if (!visited && manhathan(node[a], node[i]) <= 1000) {
            path[depth + 1] = i;
            cout << "trying " << i << endl;
            dfs(n, node, i, depth + 1); // 재귀호출
        }
    }
}

int main() {
    Node a[4] = { { 0, 0, 0}, { 1, 1000, 0}, { 2, 1000, 1000}, {3, 2000, 1000 } };
    Node b[7] = { { 0, 0, 0}, { 1, 1000, 0}, {2, 1000, 0}, { 3, 1000, 1000}, {4, 2000, 1000 }, {5, 3000, 1000 }, {6, 3000, 0} };
    beer(4, a);
    beer(7, b);

    dfs(4, a, 0, 0);
    dfs(7, b, 0, 0);
}
