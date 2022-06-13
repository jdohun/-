/*
* ���� ����
	
	�� �ڵ�� �ǻ� �ڵ��Դϴ�.
	�������� �Ǵ� �� �ƴϹǷ� �������ּ���
	
	���� ���� : �ǻ�(pseudo code) �ڵ忡�� �ε��� n�� 1���� �����̴�.
*/

/**/
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

/**/
	W[i][j] {
		1. ������ ����ġ : vi���� vj�� ���� �������� �ִ� ���
		2. ���� : vi���� vj�� ���� �������� ���� ���
		3. 0 : i = j(�ڱ� �ڽ�)�� ���
	}	

	D(k)[][]
/**/
	F = ������;		// F : �������� ����, ���������� �ʱ�ȭ
	Y = { v1 };		// Y : �ּ� ����ġ�� �̹� ������ ������ ����, ���� ó������ ù°������� �˻縦 �����ϱ� ���� v1�� �����Ͽ� �����Ѵ�.
/**/


// Floyd �˰���
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

// Floyd2 �˰���
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
��������2

(v1, v2), (v1, v4), (v2, v5), (v3, v4), (v3, v7), (v4, v5), (v4, v8),
(v5, v6), (v5, v9), (v6, v10), (v7, v8), (v8, v9), (v9, v10);

	1	2	3	4	5	6	7	8	9	10
1	0	32	��	17	��	��	��	��	��	��
2	32	0	��	��	45	��	��	��	��	��
3	��	��	0	18	��	��	5	��	��	��
4	17	��	18	0	10	��	��	��	��	��
5	��	45	��	10	0	28	��	��	25	��
6	��	��	��	��	28	0	��	��	��	6
7	��	��	5	��	��	��	0	59	��	��
8	��	��	��	3	��	��	59	0	4	��
9	��	��	��	��	25	��	��	4	0	12
10	��	��	��	��	��	6	��	��	12	0

// ���1 ���� ���10������ ������ ����ġ
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

// MST(Minimum (Cost) Spanning Tree) : �ּ�(���) ���� Ʈ���� ����
1. Ʈ���� ���� : n�� ��� -(n-1)�� ����, ���� ���� -> �ΰ��� ��Ʈ���� ���ҵ�
 ���� ���� - > ������ ������ ����Ŭ�� ����

2. Cut Property : Prim Algorithm
	Cut���� �ּ�(���) ������ �����ϴ� MST�� �ּ� �ϳ� �̻� �����Ѵ�.

3. Cycle Property : kruskal Algorithms
	������ cycle�� �ִ� ��� ������ ������ MST�� ����!

// Prim Algorithm
void Prim(int n, const number W[][], set_of_edges& F) {
	index i, vnear;
	number min;
	edge e;
	index nearest[2 ..n];
	number distance[2 ..n];

	F = ������;		// F�� �������� ����
	for (i = 2; i <= n; ++i) {	//  : �ǻ��ڵ忡�� ù��° �ε����� 1���� �����ϹǷ� �ڱ� �ڽ�(1��)�� 0���� �����Ѵ�.
		nearest[i] = 1;						// ��� ���� ���Ͽ� Y�� ���� ���� ����� ����
		distance[i] = W[1][i];				// (nearest[i])�� v1�� �ʱ�ȭ�ϰ�,
	}										// Y�κ��� �Ÿ�(distance[i])�� vi�� v1��
											// �����ϴ� �������� ����ġ�� �ʱ�ȭ�Ѵ�.

	repeat(n - 1 times) {					// n-1���� ���� Y�� �߰��Ѵ�.
		min = ����;
		for (i = 2; i <= n; ++i) {			// �� ���� ���Ͽ� distance[i]�� �˻��Ͽ� Y��
			if (0 <= distance[i] < min) {	// ���� ������ �ִ� ����(vnear)�� ã�´�.
				min = distance[i];
				vnear = i;
			}
		}

		e = evnear�� �ε����� ���� Y�� �߰��Ѵ�;
		add e to F;
		distance[vnear] = -1;					// Y�� ������ ����
		for (i = 2; i <= n; ++i) {				// �� ���� ���Ͽ�
			if (W[i][vnear] < distance[i]) {	// Y�κ��� �Ÿ�(distance[i])��
				distance[i] = W[i][vnear];		// �����Ѵ�.
				nearest[i] = vnear;
			}
		}
	}
}

	// ������ ���� ����
	vector<edge> v;
	v.push_back(edge(1, 2, 32));
	v.push_back(edge(1, 4, 17));
	v.push_back(edge(2, 5, 45));
	v.push_back(edge(3, 4, 18));
	v.push_back(edge(3, 7, 5));
	v.push_back(edge(4, 5, 10));
	v.push_back(edge(4, 8, 3));
	v.push_back(edge(5, 6, 28));
	v.push_back(edge(5, 9, 25));
	v.push_back(edge(6, 10, 6));
	v.push_back(edge(7, 8, 59));
	v.push_back(edge(8, 9, 4));
	v.push_back(edge(9, 10, 12));

	vector<edge> data; // ���� ������ �迭
	data.push_back(edge(0, 1, 32)); // ����0�� ����1�� ���� ���32
	data.push_back(edge(0, 3, 17));
	data.push_back(edge(1, 4, 45));
	data.push_back(edge(2, 3, 18));
	data.push_back(edge(2, 6, 5));
	data.push_back(edge(3, 4, 10));
	data.push_back(edge(3, 7, 3));
	data.push_back(edge(4, 5, 28));
	data.push_back(edge(4, 8, 25));
	data.push_back(edge(5, 9, 6));
	data.push_back(edge(6, 7, 59));
	data.push_back(edge(7, 8, 4));
	data.push_back(edge(8, 9, 12));

// Kruskal Algoirtm
void kruskal(int n, int m, set_of_edges E, set_of_edges& F) {
	index i, j;
	set_pointer p, q;
	edge e;

	E�� ���� m���� �������� ����ġ�� ���� �ͺ��� ���ʷ� �����Ѵ�;
	F = ������;
	initail(n);		// n���� ���ҷ� �κ������� �ʱ�ȭ
	while (F���� �������� ���� n - 1���� �۴�) {
		e = ���� ������� ���� ������ �� ����ġ�� �ּ��� ������;
		i, j = e�� ����� ������ �ε���;
		p = find(i);
		q = find(j);
		if (!equal(p, q)) {
			merge(p, q);
			e�� F�� �߰�;
		}
	}
}

// ppt�� �ִ� Kruskal �˰���
void kruskal2(int n, int m, const number W[], number D[]) {
	index i, j, k;
	index p, q;
	index parents[0..n - 1];
	index edges[0..n * (n - 1) / 2 - 1];

	initialize D[] to ��;

	for (i = 0; i < n; i++)
		parents[i] = i;

	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (W[i * n + j] < ��)
				edges[num_edges++] = i * n + j;
	sort edges based on W[edges[]]
		for (e = 0; e < num_edges; e++) {
			k = edges[e];
			i = k / n;
			j = k % n;
			p = find(parents, i);
			q = find(parents, j);
			if (p != q) {
				if (p < q)
					parents[q] = p;
				else
					parents[p] = q;
				D[k] = D[j * n + i] = W[k];
			}
		}
}

index find(index parents[], index i) {
	if (parents[i] == i)
		return i;
	else
		return find(parents, parents[i]);
}


// Dijkstra Algorithm
void dijkstra(int n, const number W[][], set_of_edges& F) {
	index i, vnear;
	edge e;
	index touch[2..n];
	number length[2..n];

	F = ������;
	for (i = 2; i <= n; ++i) {			// ������ ���ؼ�,
		touch[i] = 1;					// v1���� ����ϴ� ���� �ִ� ����� ������ ����
		length[i] = W[1][i];			// v1���� �ʱ�ȭ�Ѵ�.
	}

	repeat(n - 1)�� {
		min = ����;
		for (i = 2; i <= n; ++i) {		// �ִܰ�θ� �������� �� ���� �����Ѵ�.
			if (0 <= length[i] < min) {
				min = length[i];
				vnear = i;
			}
		}

		e = touch[vnear]�� �ε����� ���𿡼� vnear�� �ε����� ����� ���� ������;
		e�� F�� �߰�;
		for (i = 2; i <= n; ++i) {
			if (length[vnear] + W[vnear][i] < length[i]) {
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;			// Y�� ������ �ʴ� ������ ���ؼ�,
			}								// �ִܰ�θ� �ٲ۴�.
			length[vnear] = -1;				// vnear�� �ε����� ���� Y�� �߰��Ѵ�.
		}
	}
}


// ĥ�ǿ� ���ֽŰ�
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