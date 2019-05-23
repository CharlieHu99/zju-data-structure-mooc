#include <cstdio>
#include <cstdlib>

#define MAX 10

typedef struct ANode {
	int adjvex;
	struct ANode * nextarc;
} ArcNode;
typedef struct VNode {
	ArcNode * firstarc;
} VerNode;
typedef VerNode AdjList[MAX];
typedef struct {
	AdjList adjlist;
	int n, e;
} ALGraph;

void insertEdge(ALGraph * g, int start, int end) {
	ArcNode * a = (ArcNode *) malloc(sizeof(ArcNode));
	a->adjvex = end;
	ArcNode * node1 = g->adjlist[start].firstarc;
	ArcNode * pre1 = NULL;
	while (node1 != NULL && node1->adjvex < a->adjvex) {
		pre1 = node1;
		node1 = node1->nextarc;
	}
	if (pre1 == NULL) {
		a->nextarc = g->adjlist[start].firstarc;
		g->adjlist[start].firstarc = a;
	} else {
		a->nextarc = pre1->nextarc;
		pre1->nextarc = a;
	}

	ArcNode * b = (ArcNode *) malloc(sizeof(ArcNode));
	b->adjvex = start;
	ArcNode * node2 = g->adjlist[end].firstarc;
	ArcNode * pre2 = NULL;
	while (node2 != NULL && node2->adjvex < b->adjvex) {
		pre2 = node2;
		node2 = node2->nextarc;
	}
	if (pre2 != NULL) {
		b->nextarc = pre2->nextarc;
		pre2->nextarc = b;
	} else {
		b->nextarc = g->adjlist[end].firstarc;
		g->adjlist[end].firstarc = b;
	}
}

void dfs(ALGraph * g, int v, int visited[]) {
	visited[v] = 1;
	printf("%d ", v);
	ArcNode * p = g->adjlist[v].firstarc;
	while (p != NULL) {
		if (visited[p->adjvex] == 0) {
			dfs(g, p->adjvex, visited);
		}
		p = p->nextarc;
	}
}

void dfs(ALGraph * g, int visited[]) {
	for (int i = 0; i < g->n; i++) {
		if (visited[i] == 0) {
			printf("{ ");
			dfs(g, i, visited);
			printf("}\n");
		}
	}
}

void bfs(ALGraph * g, int v, int visited[]) {
	ArcNode * node;
	int queue[g->n], front = 0, rear = 0, w;
	printf("%d ", v);
	visited[v] = 1;
	rear = (rear + 1) % g->n;
	queue[rear] = v;
	while (front != rear) {
		front = (front + 1) % g->n;
		w = queue[front];
		node = g->adjlist[w].firstarc;
		while (node != NULL) {
			if (visited[node->adjvex] == 0) {
				printf("%d ", node->adjvex);
				visited[node->adjvex] = 1;
				rear = (rear + 1) % g->n;
				queue[rear] = node->adjvex;
			}
			node = node->nextarc;
		}
	}
}

void bfs(ALGraph * g, int visited[]) {
	for (int i = 0; i < g->n; i++) {
		if (visited[i] == 0) {
			printf("{ ");
			bfs(g, i, visited);
			printf("}\n");
		}
	}
}

void reset(int visited[], int n) {
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
}

void release(ALGraph * g) {
	for (int i = 0; i < g->n; i++) {
		ArcNode * node = g->adjlist[i].firstarc;
		while (node != NULL) {
			ArcNode * next = node->nextarc;
			free(node);
			node = next;
		}
	}
	free(g);
}

int main() {
	// 初始化图
	ALGraph * g = (ALGraph *) malloc(sizeof(ALGraph));
	scanf("%d %d", &(g->n), &(g->e));
	for (int i = 0; i < g->n; i++) {
		g->adjlist[i].firstarc = NULL;
	}

	int a, b;
	for (int i = 0; i < g->e; i++) {
		scanf("%d %d", &a, &b);
		insertEdge(g, a, b);
	}
	// dfs 连通集
	int visited[g->n];
	reset(visited, g->n);
	dfs(g, visited);

	// bfs 连通集
	reset(visited, g->n);
	bfs(g, visited);

	// 释放空间
	release(g);
	return 0;
}
