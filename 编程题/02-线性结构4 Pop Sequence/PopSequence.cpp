#include <cstdio>

bool isPopSeq(int seq[], int n, int m) {
	int stack[m];
	int top = -1, head = 0;
	for (int i = 1; i <= n; i++) {
		if (top + 1 < m) {
			stack[++top] = i;
		} else {
			return false;
		}
		while (stack[top] == seq[head]) {
			top--;
			head++;
		}
	}
	if (head != n) {
		return false;
	}
	return true;
}
/*解题思路：*/
int main() {
	int m, n, k;
	scanf("%d %d %d", &m, &n, &k);
	int seq[n];
	while (k--) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &seq[i]);
		}
		if (isPopSeq(seq, n, m)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
