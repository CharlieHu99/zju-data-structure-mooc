#include <cstdio>

int h[1000], size;

void create() {
	h[0] = -10001;
	size = 0;
}

void insert(int x) {
	if (size > 1000) {
		return;
	}
	int i;
	for (i = ++size; h[i / 2] > x; i /= 2) {
		h[i] = h[i / 2];
	}
	h[i] = x;
}

int main() {
	int n, m, x;
	scanf("%d %d", &n, &m);
	create();
	while (n--) {
		scanf("%d", &x);
		insert(x);
	}
	while (m--) {
		scanf("%d", &x);
		printf("%d", h[x]);
		while (x > 1) {
			x /= 2;
			printf(" %d", h[x]);
		}
		printf("\n");
	}
	return 0;
}
