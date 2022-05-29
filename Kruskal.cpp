/*
	V: vertex(�׷��������� �� ���, ����, ��� ����)�� ����
	A : V�� �κ�����
	D[vi][A] = A�� ���� ���ø� ���� �� ������ ���ļ� vi���� v1���� ���� �ִܰ���� ����

	G : ������ ���� ���� V �� V�� ���� ������ ���� ���� E�� ������, G = (V, E)
	E : �ּҺ�� ����Ʈ�� �������� ����
	T : G�� ���� ���� V�� ��������, �������� F�� ����, T = (V, F)
	F : E�� �κ� ����(E�� ���� �κ������� �߰��Ǳ� ������ �κ������̴�) : �ּ� ��� �������� ã�Ƴ��� ������ �׸� -> ���������δ� E�� ��������.

	������ : ���� �մ� ��
	����ġ : �������� ���õ� ��(������ �ƴ϶�� ������, ���� �Ÿ��� ��Ÿ���� ��찡 ����)
	directed graph / digraph(���� �׷���) : �������� ������ �ִ� �׷���
	weighted graph(����ġ���� �׷���) : �������� ����ġ�� �ִ� �׷���
	path : �������� �ִ� ������ ����.ex)[v1, v4, v3]�� v1->v4->v3
	length(����� ����) : ��� �� �ִ� ����ġ�� ��
*/

/*
ũ�罺Į �˰��� -> ������ ����
	1. �������� ���� �׷����� MST�� ���� �� ����
	2. ����Ŭ �˻簡 �ʿ��ϴ�.
	(�������� �����ϹǷ� Ʈ���� ������ ���� �� ����.
	����Ŭ�� ������ �ʵ��� ���þ־� ��.)
*/

/*
	MST = Forest = a Collection of Trees
	ũ�罺Į �˰����� MST�� �����ϴ� �������� ���� ���� Tree���� �����ǰ�
	�� Tree���� �̾����鼭 �ᱹ MST�� �����ȴ�.
*/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define CofVtx	10	// n : ���� 10��
#define CofEdge 13	// m : ������ 13��

// �������� Ŭ���� ���� 
class Edge { // vtx[0]�� vtx[1]�� �մ� ������
public:
	Edge(int a, int b, int distance) {
		this->vtx[0] = a;
		this->vtx[1] = b;
		this->distance = distance;
	}
public:
	int vtx[2];		// ����� 2���� ����
	int distance;	// �Ÿ�(���)
public:
	bool operator <(Edge& edge) {	// Sort �Լ��� ����ϱ� ���� ������ ������
		return this->distance < edge.distance;
	}
};

int getParent(int parent[], int x);
int compareParent(int parent[], int vtx1, int vtx2);
void unionParent(int parent[], int vtx1, int vtx2);

// void kruskal(int n, int m, vector<Edge> V, vector<Edge> F);

int main(void) {
	int n = CofVtx;
	int m = CofEdge;

	// edge* E = new edge[];
	//edge* F = new edge[CofVtx - 1];	// MST�� �������� ������ �迭
	vector<Edge> F; // ������ ������ �迭

	vector<Edge> V; // ������ ������ �迭
	V.push_back(Edge(0, 1, 32)); // ����0�� ����1�� ������ ���32
	V.push_back(Edge(0, 3, 17));
	V.push_back(Edge(1, 4, 45));
	V.push_back(Edge(2, 3, 18));
	V.push_back(Edge(2, 6, 5));
	V.push_back(Edge(3, 4, 10));
	V.push_back(Edge(3, 7, 3));
	V.push_back(Edge(4, 5, 28));
	V.push_back(Edge(4, 8, 25));
	V.push_back(Edge(5, 9, 6));
	V.push_back(Edge(6, 7, 59));
	V.push_back(Edge(7, 8, 4));
	V.push_back(Edge(8, 9, 12));	// 13��

	//kruskal(n, m, V, F);
	
	// �������� ������� �������� ���� 
	sort(V.begin(), V.end());

	// �θ� vtx : �ٷ� ������ ����� vtx
	// �� ������ ���Ե� �׷����� ������� ���� => ��� �θ� ���ߴ��� 
	int parents[CofVtx];
	for (int i = 0; i < CofVtx; i++) {	// initail(n);		// n���� ���μ� �κ������� �ʱ�ȭ
		parents[i] = i;					// �θ� vtx�� �ڱ� �ڽ����� �ʱ�ȭ : ����� vtx�� ���� ������
	}

	// �Ÿ��� ���� 0���� �ʱ�ȭ 
	int sum = 0;
	for (int i = 0; i < (int)V.size(); i++) {
		// ������ �θ� ����Ű�� �ʴ� ���, �� ����Ŭ�� �߻����� ���� ���� ���� 
		if (!compareParent(parents, V[i].vtx[0], V[i].vtx[1])) {

			sum += V[i].distance;

			unionParent(parents, V[i].vtx[0], V[i].vtx[1]);
			F.push_back(V[i]);
		}
	}
	printf("%d\n", sum);

	for (int i = 0; i < (int)F.size(); ++i) {
		printf("%d. %d��° ����� %d��° ���� �հ�, ����ġ ���� %d\n", i + 1, F[i].vtx[0] + 1, F[i].vtx[1] + 1, F[i].distance);
	}
}

// ppt���� find �Լ��� ������
// �θ� ��带 ������ 
int getParent(int parent[], int x) {
	if (parent[x] == x) {	// �θ� �ڱ��ڽ��̸� �״�� ��ȯ
		return x;
	}
	else {					// �ƴϸ� �θ� �����ϰ� �� ���� ��ȯ
		return parent[x] = getParent(parent, parent[x]);
	}
}

// �ǻ��ڵ忡�� equal �κ�
// ���� �θ� �������� Ȯ��
int compareParent(int parent[], int vtx1, int vtx2) {
	vtx1 = getParent(parent, vtx1);
	vtx2 = getParent(parent, vtx2);
	if (vtx1 == vtx2) return 1;	// �� vtx�� �θ� ������ 1(Ture)
	else return 0;				// �ٸ��� 0 (False)
}

// �ǻ��ڵ忡���� merge �Լ��� ������
// �θ� ��带 ���� 
void unionParent(int parent[], int vtx1, int vtx2) {
	vtx1 = getParent(parent, vtx1);
	vtx2 = getParent(parent, vtx2);

	// �� ���ڰ� ���� �θ�� ����
	if (vtx1 < vtx2) parent[vtx2] = vtx1;
	else parent[vtx1] = vtx2;
}
/*
void kruskal(int n, int m, vector<Edge> V, vector<Edge> F) {
	int k = 0;
	while (k < m) {	// ������ ����ġ ��										// while (F���� �������� ���� n - 1���� �۴�) {	
		e = V[k];	// k��° ������												// e = ���� ������� ���� ������ �� ����ġ�� �ּ��� ������;
		i = e.vtx[0], j = e.vtx[1];	// k��° �������� �� vtx					// i, j = e�� ����� ������ �ε���;
		p = getParent(parent, i);	// �� vtx�� �θ�							// p = find(i);
		q = getParent(parent, j);												// q = find(j);
			
		if (!compareParent(parent, p, q)) {	 // �� vtx�� �θ� ���� ������		// if (!equal(p, q)) {
			unionParent(parent, p, q);		// ���� ��ȣ�� vtx�� �θ�� ����	// merge(p, q);
			
			sum += V[k].distance;

			// ����Ŭ�� �߻����� �ʴ� �ּ� ����ġ ������ ����
			F.push_back(V[k]);								// e�� F�� �߰�;
		}
		++k;
	}
}
*/