/*
* 주의 사항
	
	본 코드는 의사 코드입니다.
	컴파일이 되는 언어가 아니므로 유의해주세요
	
	참고 사항 : 의사(pseudo code) 코드에서 인덱스 n은 1부터 시작이다.
*/

/**/
	V: vertex(그래프에서의 원 모양, 마디, 모든 도시)의 집합
	A : V의 부분집합
	D[vi][A] = A에 속한 도시를 각각 한 번씩만 거쳐서 vi에서 v1으로 가는 최단경로의 길이

	G : 마디의 유한 집합 V 와 V에 속한 마디의 쌍의 집합 E로 구성됨, G = (V, E)
	E : 이음선의 집합
	T : G와 같은 마디 V를 가지지만, 이음선은 F를 가짐, T = (V, F)
	F : E의 부분 집합

	이음선 : 마디를 잇는 선
	가중치 : 이음선과 관련된 값 ( 음수가 아니라고 가정함, 보통 거리를 나타내는 경우가 많음)
	directed graph / digraph(방향 그래프) : 이음선에 방향이 있는 그래프
	weighted graph  (가중치포함 그래프) : 이음선에 가중치가 있는 그래프
	path : 이음선이 있는 마디의 나열. ex) [v1, v4, v3]는 v1 -> v4 -> v3
	length(경로의 길이) : 경로 상에 있는 가중치의 합

/**/
	W[i][j] {
		1. 이음선 가중치	: vi에서 vj로 가는 이음선이 있는 경우
		2. 무한				:  "	"			"		없는 경우
		3. 0				: i = j 인 경우
	}	

	D(k)[][]
/**/
	F = 공집합;		// F : 이음선의 집합, 공집합으로 초기화
	Y = { v1 };		// Y : 최소 가중치를 검출한 마디의 집합, 가장 처음에는 첫째마디부터 검사를 시작하기 위해 
/**/


// Floyd 알고리즘
void Floyd(int n, const number W[][], number D[][]) {
	index i, j, k;
	D = W;
	for (k = 1; k <= n; ++k) {
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				D[i][j] = minimum(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}
}

// Floyd2 알고리즘
void Floyd2(int n, const number W[][], number D[][], index P[][]) {
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			P[i][j] = 0;
		}
	}
	D = W;
	for (k = 1; k <= n; ++k) {
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				D[i][j] = minimum(D[i][j], D[i][k] + D[k][j]);
			}
			if (D[i][k] + D[k][j] < D[i][j]) {
				P[i][j] = k;
				D[i][j] = D[i][k] + D[k][j];
			}
		}
	}
}


/**/
연습문제2

(v1, v2), (v1, v4), (v2, v5), (v3, v4), (v3, v7), (v4, v5), (v4, v8),
(v5, v6), (v5, v9), (v6, v10), (v7, v8), (v8, v9), (v9, v10);

	1	2	3	4	5	6	7	8	9	10
1	0	32	무	17	무	무	무	무	무	무
2	32	0	무	무	45	무	무	무	무	무
3	무	무	0	18	무	무	5	무	무	무
4	17	무	18	0	10	무	무	무	무	무
5	무	45	무	10	0	28	무	무	25	무
6	무	무	무	무	28	0	무	무	무	6
7	무	무	5	무	무	무	0	59	무	무
8	무	무	무	3	무	무	59	0	4	무
9	무	무	무	무	25	무	무	4	0	12
10	무	무	무	무	무	6	무	무	12	0

// 노드1 부터 노드10까지의 이음선 가중치
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
	}

// MST(Minimum (Cost) Spanning Tree) : 최소(비용) 신장 트리의 성질
1. 트리의 성질 : n개 노드 -(n-1)개 에지, 에지 삭제 -> 두개의 부트리로 분할됨
 에지 삽입 - > 에지를 포함한 사이클이 생성

2. Cut Property : Prim Algorithm
	Cut에서 최소(비용) 에지를 포함하는 MST는 최소 하나 이상 존재한다.

3. Cycle Property : kruskal Algorithms
	임의의 cycle의 최대 비용 에지를 포함한 MST는 없다!

// Prim Algorithm
void Prim(int n, const number W[][], set_of_edges& F) {
	index i, vnear;
	number min;
	edge e;
	index nearest[2 ..n];
	number distance[2 ..n];

	F = 공집합;		// F는 이음선의 집합
	for (i = 2; i <= n; ++i) {	//  : 의사코드에서 첫번째 인덱스는 1부터 시작하므로 자기 자신(1번)과 0번을 제외한다.
		nearest[i] = 1;						// 모든 마디에 대하여 Y에 속한 가장 가까운 마디
		distance[i] = W[1][i];				// (nearest[i])는 v1로 초기화하고,
	}										// Y로부터 거리(distance[i])는 vi와 v1을
											// 연결하는 이음선의 가중치로 초기화한다.

	repeat(n - 1 times) {					// n-1개의 마디를 Y에 추가한다.
		min = 무한;
		for (i = 2; i <= n; ++i) {			// 각 마디에 대하여 distance[i]를 검사하여 Y에
			if (0 <= distance[i] < min) {	// 가장 가까이 있는 마디(vnear)를 찾는다.
				min = distance[i];
				vnear = i;
			}
		}

		e = evnear가 인덱스인 마디를 Y에 추가한다;
		add e to F;
		distance[vnear] = -1;					// Y에 속하지 않은
		for (i = 2; i <= n; ++i) {				// 각 마디에 대하여
			if (W[i][vnear] < distance[i]) {	// Y로부터 거리(distance[i])를
				distance[i] = W[i][vnear];		// 갱신한다.
				nearest[i] = vnear;
			}
		}
	}
}

// Kruskal Algoirtm
void kruskal(int n, int m, set_of_edges E, set_of_edges& F) {
	index i, j;
	set_pointer p, q;
	edge e;

	E에 속한 m개의 이음선을 가중치가 작은 것부터 차례로 정렬한다;
	F = 공집합;
	initail(n);		// n개의 서소로 부분집합을 초기화
	while (F에서 이음선의 수는 n - 1보다 작다) {
		e = 아직 고려하지 않은 이음선 중 가중치가 최소인 이음선;
		i, j = e로 연결된 마디의 인덱스;
		p = find(i);
		q = find(j);
		if (!equal(p, q)) {
			merge(p, q);
			e를 F에 추가;
		}
	}
}

// Dijkstra Algorithm
void dijkstra(int n, const number W[][], set_of_edges& F) {
	index i, vnear;
	edge e;
	index touch[2..n];
	number length[2..n];

	F = 공집합;
	for (i = 2; i <= n; ++i) {			// 각마디에 대해서,
		touch[i] = 1;					// v1에서 출발하는 현재 최단 경로의 마지막 마디를
		length[i] = W[1][i];			// v1으로 초기화한다.
	}

	repeat(n - 1)번 {
		min = 무한;
		for (i = 2; i <= n; ++i) {		// 최단경로를 가지는지 각 마디를 점검한다.
			if (0 <= length[i] < min) {
				min = length[i];
				vnear = i;
			}
			e = touch[vnear]가 인덱스인 마디에서 vnear가 인데스인 마디로 가는 이음선;
			e를 F에 추가;
			for (i = 2; i <= n; ++i) {
				if (length[vnear] + W[vnear][i] < length[i]) {
					length[i] = length[vnear] + W[vnear][i];
					touch[i] = vnear;			// Y에 속하지 않는 각마디에 대해서,
				}								// 최단경로를 바꾼다.
				length[vnear] = -1;				// vnear가 인덱스인 마디를 Y에 추가한다.
			}
		}
	}
}


// 칠판에 써주신거
if (p != q) {
	if (p < q) {
		for (r = 0; r < n; ++r) {
			if (parent[r] == q) {
				parent[r] = p;
			}
		}
	}
	else {
		for (r = 0; r < n; ++r) {
			if (parent[r] = p) {
				parent[r] = q;
			}
		}
	}
}