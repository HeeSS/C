//2015.11.26
//1492018 서희선
//알고리즘(A)
//그래프 프로그램

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define INF 999

typedef struct {
	int *weight;	//가중치
}Node;
typedef struct {
	int size; //노드 개수
	Node *node; //노드
}Matrix;
typedef struct {
	int weight;
	int from;
	int to;
}Dist;
typedef struct {
	int key;
	int u;
	int v;
} element;
typedef struct{
	element heap[100];
	int heap_size;
}HeapType;

//Kruskal
void set_init(int num[], int parent[], int n)
{
	int i;
	for (i = 0; i<n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}
int set_find(int parent[], int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p)// 루트 노드까지 반복
	{ }
	s = i;			// 집합의 대표 원소
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;	// 집합의 모든 원소들의 부모를 p로 설정
	return s;
}
void set_union(int num[], int parent[], int s1, int s2)
{
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}
void init(HeapType *h)
{
	h->heap_size = 0;
}
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)){
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size){
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void min_insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}
void min_insert_all_edges(Matrix *matrix, int n, HeapType *h)
{
	int i, j;
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			if (matrix->node[i].weight[j] != 0 && matrix->node[i].weight[j] != 999)
				min_insert_heap_edge(h, i, j, matrix->node[i].weight[j]);
}
void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)){
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size){
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void max_insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_max_heap(h, e);
}
void max_insert_all_edges(Matrix *matrix, int n, HeapType *h)
{
	int i, j;
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			if (matrix->node[i].weight[j] != 0 && matrix->node[i].weight[j] != 999)
				max_insert_heap_edge(h, i, j, matrix->node[i].weight[j]);
}
void Min_kruskal(Matrix *matrix)
{
	int n = matrix->size;
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;
	int *parent = (int*)malloc(sizeof(int)*n);	// 부모 노드
	int *num = (int*)malloc(sizeof(int)*n);		// 각 집합의 크기

	init(&h);
	min_insert_all_edges(matrix, n, &h);
	set_init(num, parent, n);

	while (edge_accepted < (n - 1)){
		e = delete_min_heap(&h);
		uset = set_find(parent, e.u);
		vset = set_find(parent, e.v);
		if (uset != vset){
			printf("(%d,%d) %d \n", e.u + 1, e.v + 1, e.key);
			edge_accepted++;
			set_union(num, parent, uset, vset);
		}
	}
	free(parent);
	free(num);
}
void Max_kruskal(Matrix *matrix)
{
	int n = matrix->size;
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;
	int *parent = (int*)malloc(sizeof(int)*n);	// 부모 노드
	int *num = (int*)malloc(sizeof(int)*n);		// 각 집합의 크기

	init(&h);
	max_insert_all_edges(matrix, n, &h);
	set_init(num, parent, n);

	while (edge_accepted < (n - 1)){
		e = delete_max_heap(&h);
		uset = set_find(parent, e.u);
		vset = set_find(parent, e.v);
		if (uset != vset){
			printf("(%d,%d) %d \n", e.u + 1, e.v + 1, e.key);
			edge_accepted++;
			set_union(num, parent, uset, vset);
		}
	}
	free(parent);
	free(num);
}
//Prim
int get_min_vertex(int selected[], Dist dist[], int n)
{
	int v, i;
	for (i = 0; i <n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i].weight < dist[v].weight)) v = i;
	return (v);
}
int get_max_vertex(int selected[], Dist dist[], int n)
{
	int v, i;
	for (i = 0; i <n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i].weight > dist[v].weight)) v = i;
	return (v);
}
void Min_prim(Matrix *matrix)
{
	int *selected = (int*)malloc(sizeof(int)*matrix->size);
	Dist *dist = (Dist*)malloc(sizeof(Dist)*matrix->size);
	int i, u, v;
	int n = matrix->size;
	int s;

	printf("출발노드(1~n): ");
	scanf(" %d", &s);
	s = s - 1;
	if (s > n || s < 0) {
		printf("범위 안의 값을 입력하세요\n");
		return;
	}

	for (u = 0; u < n; u++){
		dist[u].weight = INF; selected[u] = FALSE;
	}
	dist[s].weight = 0;
	for (i = 0; i<n; i++) {
		u = get_min_vertex(selected, dist, n);
		selected[u] = TRUE;
		if (dist[u].weight == INF) return;
		if(i!=0)
			printf("(%d,%d) %d \n", dist[u].from + 1, dist[u].to + 1, dist[u].weight);
		for (v = 0; v<n; v++)
			if (matrix->node[u].weight[v] != INF)
				if (!selected[v] && matrix->node[u].weight[v] < dist[v].weight) {
					dist[v].weight = matrix->node[u].weight[v];
					dist[v].from = u;
					dist[v].to = v;
				}
	}
	free(selected);
	free(dist);
}
void Max_prim(Matrix *matrix)
{
	int *selected = (int*)malloc(sizeof(int)*matrix->size);
	Dist *dist = (Dist*)malloc(sizeof(Dist)*matrix->size);
	int i, u, v;
	int n = matrix->size;
	int s;

	printf("출발노드(1~n): ");
	scanf(" %d", &s);
	s = s - 1;
	if (s > n || s < 0) {
		printf("범위 안의 값을 입력하세요\n");
		return;
	}

	for (u = 0; u < n; u++) {
		dist[u].weight = -1; selected[u] = FALSE;
	}
	dist[s].weight = 0;
	for (i = 0; i<n; i++) {
		u = get_max_vertex(selected, dist, n);
		selected[u] = TRUE;
		if (dist[u].weight == INF) return;
		if(i!=0)
			printf("(%d,%d) %d \n", dist[u].from + 1, dist[u].to + 1, dist[u].weight);
		for (v = 0; v<n; v++)
			if (matrix->node[u].weight[v] != INF)
				if (!selected[v] && matrix->node[u].weight[v] > dist[v].weight && matrix->node[u].weight[v]!=INF) {
					dist[v].weight = matrix->node[u].weight[v];
					dist[v].from = u;
					dist[v].to = v;
				}
	}
	free(selected);
	free(dist);
}
//Dijkstra
void print_path(int start, int end, int path[])
{
	if (path[end] != start)
		print_path(start, path[end], path);
	printf("<%d->%d> ", path[end], end);
}
void print_distance(int size, int start, int path[], int distance[])
{
	int i;
	for (i = 0; i<size; i++) {
		printf("정점 %d까지의 최단경로의 길이: %d\n", i, distance[i]);
		print_path(start, i, path);
		printf("\n");
	}
	printf("\n");
}
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i<n; i++)
		if (distance[i]< min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void simple_print_distance(Matrix *matrix)
{
	int s, i, u, w;
	int start;
	int n = matrix->size;
	int *distance = (int*)malloc(sizeof(int)*n);
	int *found = (int*)malloc(sizeof(int)*n);
	int *path = (int*)malloc(sizeof(int)*n);

	for (s = 0; s<n; s++) {
		start = s;
		for (i = 0; i<n; i++) /* 초기화 */
		{
			distance[i] = matrix->node[start].weight[i];
			path[i] = start;
			found[i] = FALSE;
		}
		found[start] = TRUE;    /* 시작노드 방문 표시 */
		distance[start] = 0;
		for (i = 0; i<n; i++) {
			u = choose(distance, n, found);
			found[u] = TRUE;
			for (w = 0; w<n; w++)
				if (!found[w])
					if (distance[u] + matrix->node[u].weight[w] < distance[w]) {
						distance[w] = distance[u] + matrix->node[u].weight[w];
						path[w] = u;		/* 경유노드 저장 */
					}
		}
		for (i = 0; i < n; i++) {
			printf("%3d ", distance[i]);
		}
		printf("\n");
	}
}
void Dijkstra(Matrix *matrix) /* 시작노드 start  */
{
	int i, u, w;
	int start;
	int n = matrix->size;
	int *distance = (int*)malloc(sizeof(int)*n);
	int *found = (int*)malloc(sizeof(int)*n);
	int *path = (int*)malloc(sizeof(int)*n);

	printf("시작노드(0~n): ");
	scanf(" %d", &start);
	if (start > n || start < 0) {
		printf("범위 안의 값을 입력하세요\n");
		return;
	}

	for (i = 0; i<n; i++) /* 초기화 */
	{
		distance[i] = matrix->node[start].weight[i];
		path[i] = start;
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작노드 방문 표시 */
	distance[start] = 0;
	for (i = 0; i<n; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w<n; w++)
			if (!found[w])
				if (distance[u] + matrix->node[u].weight[w] < distance[w]) {
					distance[w] = distance[u] + matrix->node[u].weight[w];
					path[w] = u;		/* 경유노드 저장 */
				}
	}
	print_distance(n, start, path, distance);

	printf("\n+) 모든 노드의 쌍에 대한 최단경로의 길이 행렬\n");
	simple_print_distance(matrix);
}
//Floyd
void printA(int n, Node *A)
{
	int i, j;
	printf("===============================================\n");
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			if ((A+i)->weight[j] == INF)
				printf("INF ");
			else printf("%3d ", (A+i)->weight[j]);
		}
		printf("\n");
	}
	printf("===============================================\n");
}
void printPath(int n, Node *path)
{
	int i, j;
	printf("===============================================\n");
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			printf("%3d ", (path + i)->weight[j]);
		}
		printf("\n");
	}
	printf("===============================================\n");
}
void path(int start, int end, Node *A, Node *next) {
	int intermediate = (next + start)->weight[end];
	
	if ((A+start)->weight[end] == INF) {
		printf("no path\n");
		return;
	}
	if (intermediate==-1) {
		printf("\n	");
		return;
	}
	else {
		printf("Path(%d,%d)", start, intermediate);
		path(start, intermediate, A, next);
		printf("Path(%d,%d)", intermediate, end);
		path(intermediate, end, A, next);
	}
}
void floyd(Matrix *matrix)
{
	int n = matrix->size;
	Node *A = (Node*)malloc(sizeof(Node)*n);
	Node *next = (Node*)malloc(sizeof(Node)*n);
	int i, j, k;
	int start, end;

	for (i = 0; i < matrix->size; i++) {
		(A+i)->weight = (int*)malloc(sizeof(int)*n);
	}
	for (i = 0; i < matrix->size; i++) {
		(next + i)->weight = (int*)malloc(sizeof(int)*n);
	}

	for (i = 0; i<n; i++)
		for (j = 0; j < n; j++) {
			(A+i)->weight[j] = matrix->node[i].weight[j];
			next[i].weight[j] = -1;
		}

	for (k = 0; k<n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if ((A + i)->weight[k] + (A + k)->weight[j] < (A + i)->weight[j]) {
					(A + i)->weight[j] = (A + i)->weight[k] + (A + k)->weight[j];
					(next + i)->weight[j] = k;
				}
			}
		}
	}

	printf("시작노드(0~n): ");
	scanf(" %d", &start);
	printf("도착노드(0~n): ");
	scanf(" %d", &end);

	if (start > n || start < 0 || end>n || end < 0) {
		printf("범위 안의 값을 입력하세요\n");
		return;
	}

	printf("노드%d에서 노드%d까지의 최단 경로의 길이: ", start, end);
	if ((A + start)->weight[end] == INF)
		printf("INF\n");
	else printf("%d\n", (A + start)->weight[end]);

	printf("Path(%d,%d) = \n", start, end);
	path(start, end, A, next);

	printf("\n\n+) 모든 노드의 쌍에 대한 최단경로의 길이\n");
	printA(n, A);
	printf("\n+) 모든 노드의 쌍에 대한 최단경로의 경로\n");
	printPath(n, next);

	for (i = 0; i < matrix->size; i++) {
		free((A + i)->weight);
		free((next + i)->weight);
	}
	free(A);
	free(next);
}

int main(int argc, char *argv[]) {
	int n, m, menu;
	Matrix matrix;
	FILE *fp = NULL;

	if (argc < 2) {
		printf("Input ERROR!\n");
		return 0;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("File Open ERROR for reading\n");
		return 0;
	}

	fscanf(fp, " %d", &matrix.size);
	matrix.node = (Node*)malloc(sizeof(Node)*matrix.size);
	for (n = 0; n < matrix.size; n++) {
		matrix.node[n].weight = (int*)malloc(sizeof(int)*matrix.size);
	}

	for (n = 0; n < matrix.size; n++) {
		for (m = 0; m < matrix.size; m++) {
			fscanf(fp, " %d", &matrix.node[n].weight[m]);
		}
	}

	while (1) {
		printf("\n---------------------------------------------\n");
		printf("1. Kruskal Min\n");
		printf("2. Kruskal Max\n");
		printf("3. Prim Min\n");
		printf("4. Prim Max\n");
		printf("5. Dijkstra SP(Shortest Path)\n");
		printf("6. Floyd SP(Shortest Path)\n");
		printf("7. Exit\n");
		printf("\n---------------------------------------------\n");
		printf("Menu: ");
		scanf(" %d", &menu);

		switch (menu) {
		case 1: Min_kruskal(&matrix); break;
		case 2: Max_kruskal(&matrix); break;
		case 3: Min_prim(&matrix); break;
		case 4: Max_prim(&matrix); break;
		case 5: Dijkstra(&matrix); break;
		case 6: floyd(&matrix); break;
		case 7: fclose(fp); 
			for (n = 0; n < matrix.size; n++) {
				free(matrix.node[n].weight);
			}
			free(matrix.node); 
			return 0;
		default: printf("menu를 다시 입력하세요.\n"); break;
		}
	}
}