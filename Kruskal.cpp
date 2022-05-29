/*
	V: vertex(그래프에서의 원 모양, 마디, 모든 도시)의 집합
	A : V의 부분집합
	D[vi][A] = A에 속한 도시를 각각 한 번씩만 거쳐서 vi에서 v1으로 가는 최단경로의 길이

	G : 마디의 유한 집합 V 와 V에 속한 마디의 쌍의 집합 E로 구성됨, G = (V, E)
	E : 최소비용 신장트리 이음선의 집합
	T : G와 같은 마디 V를 가지지만, 이음선은 F를 가짐, T = (V, F)
	F : E의 부분 집합(E의 값이 부분적으로 추가되기 때문에 부분집합이다) : 최소 비용 이음선을 찾아내서 저장할 그릇 -> 최종적으로는 E와 같아진다.

	이음선 : 마디를 잇는 선
	가중치 : 이음선과 관련된 값(음수가 아니라고 가정함, 보통 거리를 나타내는 경우가 많음)
	directed graph / digraph(방향 그래프) : 이음선에 방향이 있는 그래프
	weighted graph(가중치포함 그래프) : 이음선에 가중치가 있는 그래프
	path : 이음선이 있는 마디의 나열.ex)[v1, v4, v3]는 v1->v4->v3
	length(경로의 길이) : 경로 상에 있는 가중치의 합
*/

/*
크루스칼 알고리즘 -> 이음선 선택
	1. 이음선이 적은 그래프를 MST로 만들 때 적합
	2. 사이클 검사가 필요하다.
	(이음선을 선택하므로 트리가 여러개 생길 수 있음.
	사이클이 생기지 않도록 선택애야 함.)
*/

/*
	MST = Forest = a Collection of Trees
	크루스칼 알고리즘은 MST를 생성하는 과정에서 여러 개의 Tree들이 생성되고
	이 Tree들이 이어지면서 결국 MST가 생성된다.
*/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define CofVtx	10	// n : 정점 10개
#define CofEdge 13	// m : 이음선 13개

// 이음선선 클래스 선언 
class Edge { // vtx[0]과 vtx[1]을 잇는 이음선
public:
	Edge(int a, int b, int distance) {
		this->vtx[0] = a;
		this->vtx[1] = b;
		this->distance = distance;
	}
public:
	int vtx[2];		// 연결된 2개의 정점
	int distance;	// 거리(비용)
public:
	bool operator <(Edge& edge) {	// Sort 함수를 사용하기 위한 연산자 재정의
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
	//edge* F = new edge[CofVtx - 1];	// MST의 이음선을 저장할 배열
	vector<Edge> F; // 이음선 데이터 배열

	vector<Edge> V; // 이음선 데이터 배열
	V.push_back(Edge(0, 1, 32)); // 정점0과 정점1의 이음선 비용32
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
	V.push_back(Edge(8, 9, 12));	// 13개

	//kruskal(n, m, V, F);
	
	// 이음선의 비용으로 오름차순 정렬 
	sort(V.begin(), V.end());

	// 부모 vtx : 바로 직전에 연결된 vtx
	// 각 정점이 포함된 그래프가 어디인지 저장 => 어느 부모에 속했는지 
	int parents[CofVtx];
	for (int i = 0; i < CofVtx; i++) {	// initail(n);		// n개의 서로소 부분집합을 초기화
		parents[i] = i;					// 부모 vtx를 자기 자신으로 초기화 : 연결된 vtx가 없기 때문에
	}

	// 거리의 합을 0으로 초기화 
	int sum = 0;
	for (int i = 0; i < (int)V.size(); i++) {
		// 동일한 부모를 가르키지 않는 경우, 즉 사이클이 발생하지 않을 때만 선택 
		if (!compareParent(parents, V[i].vtx[0], V[i].vtx[1])) {

			sum += V[i].distance;

			unionParent(parents, V[i].vtx[0], V[i].vtx[1]);
			F.push_back(V[i]);
		}
	}
	printf("%d\n", sum);

	for (int i = 0; i < (int)F.size(); ++i) {
		printf("%d. %d번째 마디와 %d번째 마디를 잇고, 가중치 값은 %d\n", i + 1, F[i].vtx[0] + 1, F[i].vtx[1] + 1, F[i].distance);
	}
}

// ppt에서 find 함수와 동일함
// 부모 노드를 가져옴 
int getParent(int parent[], int x) {
	if (parent[x] == x) {	// 부모가 자기자신이면 그대로 반환
		return x;
	}
	else {					// 아니면 부모를 갱신하고 그 값을 반환
		return parent[x] = getParent(parent, parent[x]);
	}
}

// 의사코드에서 equal 부분
// 같은 부모를 가지는지 확인
int compareParent(int parent[], int vtx1, int vtx2) {
	vtx1 = getParent(parent, vtx1);
	vtx2 = getParent(parent, vtx2);
	if (vtx1 == vtx2) return 1;	// 두 vtx의 부모가 같으면 1(Ture)
	else return 0;				// 다르면 0 (False)
}

// 의사코드에서의 merge 함수와 동일함
// 부모 노드를 병합 
void unionParent(int parent[], int vtx1, int vtx2) {
	vtx1 = getParent(parent, vtx1);
	vtx2 = getParent(parent, vtx2);

	// 더 숫자가 작은 부모로 병합
	if (vtx1 < vtx2) parent[vtx2] = vtx1;
	else parent[vtx1] = vtx2;
}
/*
void kruskal(int n, int m, vector<Edge> V, vector<Edge> F) {
	int k = 0;
	while (k < m) {	// 이음선 가중치 비교										// while (F에서 이음선의 수는 n - 1보다 작다) {	
		e = V[k];	// k번째 이음선												// e = 아직 고려하지 않은 이음선 중 가중치가 최소인 이음선;
		i = e.vtx[0], j = e.vtx[1];	// k번째 이음선의 두 vtx					// i, j = e로 연결된 마디의 인덱스;
		p = getParent(parent, i);	// 두 vtx의 부모							// p = find(i);
		q = getParent(parent, j);												// q = find(j);
			
		if (!compareParent(parent, p, q)) {	 // 두 vtx의 부모가 같지 않으면		// if (!equal(p, q)) {
			unionParent(parent, p, q);		// 작은 번호의 vtx를 부모로 갱신	// merge(p, q);
			
			sum += V[k].distance;

			// 사이클이 발생하지 않는 최소 가중치 이음선 저장
			F.push_back(V[k]);								// e를 F에 추가;
		}
		++k;
	}
}
*/