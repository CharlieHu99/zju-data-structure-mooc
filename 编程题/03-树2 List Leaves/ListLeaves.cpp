#include <cstdio>
#include <cstdlib>

struct TreeNode {
	int data;
	TreeNode * left, *right;
};
TreeNode * newNode(int x) {
	TreeNode * node = (TreeNode *) malloc(sizeof(struct TreeNode));
	node->data = x;
	node->left = node->right = NULL;
	return node;
}
TreeNode * createTree(int (*tree)[2], int x) {
	if (x == -1) {
		return NULL;
	}
	TreeNode * root = newNode(x);
	root->left = createTree(tree, tree[x][0]);
	root->right = createTree(tree, tree[x][1]);
	return root;
}
// 使用层次遍历输出叶子结点
void printLeaves(TreeNode * root, int n) {
	int len = n + 1;
	TreeNode * queue[len];
	int front, rear;
	front = rear = 0;
	// 进队
	rear = (rear + 1) % len;
	queue[rear] = root;
	bool flag = true;
	while (front != rear) {
		// 出队
		front = (front + 1) % len;
		TreeNode * node = queue[front];
		if (node->left == NULL && node->right == NULL) {
			if (flag) {
				printf("%d", node->data);
				flag = false;
			} else {
				printf(" %d", node->data);
			}
		}
		if (node->left) {
			rear = (rear + 1) % len;
			queue[rear] = node->left;
		}
		if (node->right) {
			rear = (rear + 1) % len;
			queue[rear] = node->right;
		}
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);
	// 吸收末尾的换行符
	getchar();
	int tree[n][2];
	// 用于表示给定下标i是否为某个结点的子节点，1表示是，0表示否
	int visited[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
	// 输入数据
	for (int i = 0; i < n; i++) {
		char l, r;
		scanf("%c %c", &l, &r);
		if (l == '-') {
			tree[i][0] = -1;
		} else {
			tree[i][0] = l - '0';
			visited[tree[i][0]] = 1;
		}

		if (r == '-') {
			tree[i][1] = -1;
		} else {
			tree[i][1] = r - '0';
			visited[tree[i][1]] = 1;
		}
		// 吸收末尾的换行符
		getchar();
	}
	// 寻找根结点的编号
	int rootNo = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] == 0) {
			rootNo = i;
			break;
		}
	}
	TreeNode * root = createTree(tree, rootNo);
	printLeaves(root, n);
	return 0;
}
