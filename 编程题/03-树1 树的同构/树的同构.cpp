#include <cstdio>

#define MAXSIZE 10

struct TreeNode {
	char data;
	int left, right;
} t1[MAXSIZE], t2[MAXSIZE];

int createTree(struct TreeNode t[]) {
	int n;
	scanf("%d", &n);
	int root = -1;
	getchar();
	if (n) {
		int visited[n];
		for (int i = 0; i < n; i++) {
			visited[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			char l, r;
			scanf("%c %c %c", &(t[i].data), &l, &r);
			if (l != '-') {
				t[i].left = l - '0';
				visited[t[i].left] = 1;
			} else {
				t[i].left = -1;
			}
			if (r != '-') {
				t[i].right = r - '0';
				visited[t[i].right] = 1;
			} else {
				t[i].right = -1;
			}
			getchar();
		}
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				root = i;
				break;
			}
		}
	}
	return root;
}
bool isomorphism(int root1, int root2) {
	// 两棵树均为空
	if (root1 == -1 && root2 == -1) {
		return true;
	}
	// 一棵为空，一棵不空
	if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1)) {
		return false;
	}
	// 根结点值不相等
	if (t1[root1].data != t2[root2].data) {
		return false;
	}
	// 若均无左子树，则比较右子树
	if (t1[root1].left == -1 && t2[root2].left == -1) {
		return isomorphism(t1[root1].right, t2[root2].right);
	}
	// 若均有左子树，且左子树根结点值相等
	if (t1[root1].left != -1 && t2[root2].left != -1
			&& t1[t1[root1].left].data == t2[t2[root2].left].data) {
		return isomorphism(t1[root1].left, t2[root2].left)
				&& isomorphism(t1[root1].right, t2[root2].right);
	}
	return isomorphism(t1[root1].left, t2[root2].right)
			&& isomorphism(t1[root1].right, t2[root2].left);
}
int main() {
	int root1 = createTree(t1);
	int root2 = createTree(t2);
	if (isomorphism(root1, root2)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	return 0;
}
