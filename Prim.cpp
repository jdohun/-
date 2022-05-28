/*
프림 알고리즘 -> 정점 선택
	1. 간선이 많은 그래프를 MST로 만들 때 적합
	2. 시작 정점을 정해두고 시작한다.
	3. 사이클 검사가 필요하지 않다.
	(인접한 정점들 중에서 선택해 나가므로
		트리는 시작 정점에서 발생했던 단 하나의 트리만 유지되며
		정점들을 선택해 나감으로써 하나의 트리를 확장해나가는 식이다.
		따라서 이 과정에선 사이클이 생길 일이 없다.)
*/

/* 
구현 과정
	1. 시작 단계에서는 시작 정점만이 MST(최소 비용 신장 트리) 집합에 포함된다.
	2. 앞 단계에서 만들어진 MST 집합에 인접한 정점들 중에서 최소 간선으로 연결된 정점을 선택하여 트리를 확장한다.
		즉, 가장 낮은 가중치를 먼저 선택한다.
	3. 위의 과정을 트리가 (N-1)개의 간선을 가질 때까지 반복한다.
https://gmlwjd9405.github.io/2018/08/28/algorithm-mst.html

최소 스패닝 트리-백준1197번
네트워크 연결-백준1922번
*/

/*
구현 과정
	1. 임의의 시작점 하나를 선택한다.
	2. 이 시작점과 연결된 정점들의 거리를 업데이트 한다.
	3. 선택된 정점들과 연결되어 있는 간선들 중에서, 가장 짧은 길이의 간선을 선택해서 연결해준다.
	4. 가장 짧은 간선으로 연결되어 있는 정점을 선택하고, 정점들의 거리를 업데이트 한다.
	5. 3 ~ 4번의 과정을 N(전체 노드의 갯수) - 1 번 만큼 반복해준다.

https://yabmoons.tistory.com/363?category=838490 [얍문's Coding World..:티스토리]
*/

/*
	가장 많이 참고한 코드
	https://ttum.tistory.com/3
*/

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
	W[i][j]{
		1. 이음선 가중치 : vi에서 vj로 가는 이음선이 있는 경우
		2. 무한			 : vi에서 vj로 가는 이음선이 없는 경우
		3. 0 : i = j(자기 자신)인 경우
}
*/

/*
	F = 공집합;		// F : 이음선의 집합, 공집합으로 초기화
	Y = { v1 };		// Y : 최소 가중치를 이미 검출한 마디의 집합, 가장 처음에는 첫째마디부터 검사를 시작하기 위해 v1을 포함하여 시작한다.
*/

#include <iostream>
using namespace std;

#define INF 9999 // infinite : 무한

struct edge {	// vnear번째 마디와 nearest[vnear]번째 마디를 잇는 이음선
	int IofVnear = 1;	// vnear
	int IofNVN = 1;		// nearest[vnear]
	int distance;		// 이음선 가중치
};

// Prim Algorithm
void Prim(int n, int(*W)[10], edge* F) { // 노드의 개수, 가중치포함 그래프, 
	int i, j;	// 반복문에 쓰일 변수
	int vnear;	// F(MST의 이음선 집합(E)의 부분집합)에 있는 edge들에서 가장 가까운 거리에 있는 노드의 index	// F : 이음선의 집합, 공집합으로 초기화 //
	int min;	// 최소 거리(가중치)
	edge e;		// vnear번째 마디와 nearest[vnear]번째 마디를 잇는 이음선

	int* nearest = new int[n];	// 인덱스별로 가장 가까운 노드의 index를 담아둔다.		// i번째 마디와 가장 가까우면서 Y에 속한 마디의 인덱스 //
	int* distance = new int[n];	// 인덱스와 가장 가까운 노드의 이음선의 길이(가중치)	// i번째 마디와 nearest[i]번째 마디를 연결하는 이음선의 가중치

	// 0번째 vertex의 정보만 정리하는 곳
	for (i = 1; i < n; ++i) {
		nearest[i] = 0;			// 시작할 때 Y = { 0번째 vertex }, 원소가 한 개뿐이므로 모든 마디는 0번째 vertex와 가장 가깝다
		distance[i] = W[0][i];	// i번째 마디와 0번째 마디까지의 거리(가중치)를 저장함
	}

	// 0번째를 제외한 1 ~ 9번째 vertex의 정보를 정리하는 곳
	for (int k = 0; k < n - 1; ++k) { // 여기서는 0부터 n-1 미만까지 반복하여 n-1번 반복하게 함	== n-1개의 마디를 Y에 추가한다 : v1이 이미 포함되었으므로 전체 개수 n에서 1개를 뺀다.

		min = INF;											// 최소값을 무한으로 초기화하여 작은 값을 검사하도록 함
		for (i = 1; i < n; ++i) {							//  1번째 vertex부터												// 각 마디에 대하여 distance[i]를 검사하여 Y에 //
			if (distance[i] >= 0 && distance[i] < min) {	// 가중치가 양수이고 최소값보다 작으면								// 가장 가까이 있는 마디(vnear = i)를 찾는다. //
				min = distance[i];	// 최소 거리 갱신
				vnear = i;			// 최소 거리 노드의 인덱스 갱신
			}
		}

		// 이음선 생성
		e.IofVnear = vnear;
		e.IofNVN = nearest[vnear];
		e.distance = min;
		F[k] = e;	// 이음선 저장  // add e to F;

		// 검사하지 않은 각 마디에 대하여 검사한 마디들 과의 거리를 갱신한다.
		distance[vnear] = -1;	// 검사한 vertex의 거리를 음수로 저장하여 갱신되지 않게 함
		for (i = 1; i < n; ++i) {				//											// Y에 속하지 않은
			// i번째 vertex와 vnear번째 vertex의 거리가 
			if (W[i][vnear] < distance[i]) {	//											// 각 마디에 대하여
				distance[i] = W[i][vnear];		//										 	// Y로부터 거리(distance[i])를
				nearest[i] = vnear;				//											// 갱신한다.
			}
		}
	}
}

int main() {
	
	// v1 부터 v10까지의 이음선 가중치를 2차원 배열(행렬)로 저장
	int weight_matrix[10][10] = {
		{0,32,INF,17,INF,INF,INF,INF,INF,INF},
		{32,0,INF,INF,45,INF,INF,INF,INF,INF},
		{INF,INF,0,18,INF,INF,5,INF,INF,INF},
		{17,INF,18,0,10,INF,INF,INF,INF,INF},
		{INF,45,INF,10,0,28,INF,INF,25,INF},
		{INF,INF,INF,INF,28,0,INF,INF,INF,6},
		{INF,INF,5,INF,INF,INF,0,59,INF,INF},
		{INF,INF,INF,3,INF,INF,59,0,4,INF},
		{INF,INF,INF,INF,25,INF,INF,4,0,12},
		{INF,INF,INF,INF,INF,6,INF,INF,12,0}
	};

	// MST's maximum edge number is n-1 : 공식, MST의 이음선은 최대가 n-1개이다.
	edge* F = new edge[9]; // MST의 edge를 담을 배열
	edge e;
	F[0] = e;
	Prim(10, weight_matrix, F);
	
	for (int i = 0; i < 9; ++i) {
		cout << F[i].IofVnear+1 << "번째 마디와 " << F[i].IofNVN+1  << "번째 마디를 잇고, 가중치 값은 " << F[i].distance  << endl;
	}
}