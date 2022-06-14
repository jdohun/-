// coloring.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int vcolor[10];

bool promising(int n, int* W, int i) {
	int j = 0;
	bool sw = true;
	while (j < i && sw) {
		if (W[i * n + j] < INT_MAX && vcolor[i] == vcolor[j])
			sw = false;
		j++;
	}
	return sw;
}

void m_coloring(int n, int* W, int m, int i) {
	int color;
	if (promising(n, W, i)) {
		if (i == n - 1) {
			for (int j = 0; j < n; j++)
				cout << ' ' << vcolor[j];
			cout << endl;
		}
		else {
			for (color = 0; color < m; color++) {
				vcolor[i + 1] = color;
				//cout << i << ':' << color << endl;
				m_coloring(n, W, m, i + 1);
			}
		}
	}
}

int main() {

	int W1[4][4] = {
			{ 0, 1, 1, 1},
			{1, 0, 1, INT_MAX},
			{1, 1, 0, 1},
			{1, INT_MAX, 1, 0}
	};
	int W2[5][5] = {
		{ 0, 1, 1, 1, INT_MAX},
		{1, 0, 1, INT_MAX, 1},
		{1, 1, 0, 1, 1},
		{1, INT_MAX, 1, 0, 1},
		{INT_MAX, 1, 1, 1, 0}
	};

	cout << "coloring1" << endl;
	m_coloring(4, (int*)W1, 3, -1);
	cout << "coloring2" << endl;
	m_coloring(5, (int*)W2, 3, -1);
}
