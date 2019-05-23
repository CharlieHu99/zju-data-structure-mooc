#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef struct TreeNode {
	int data;
	// flag为0表示未被遍历过；flag为1表示已被访问过。
	int flag;
	TreeNode * left;
	TreeNode * right;
}* Tree;
// 创建新的结点
Tree newNode(int x) {
	Tree t = (Tree) malloc(sizeof(struct TreeNode));
	t->data = x;
	t->flag = 0;
	t->left = t->right = NULL;
	return t;
}
// 如果当前节点t未被初始化，则将新插入的结点赋给t。
// 如果t没有被遍历过，在其左子树中插入新节点；否则，在其右子树中插入新节点。
Tree insert(Tree t, int x) {
	if (t == NULL) {
		t = newNode(x);
	} else {
		if (t->flag == 0) {
			t->left = insert(t->left, x);
		} else {
			t->right = insert(t->right, x);
		}
	}
	return t;
}
// 根据所给的值，搜索结点并更新其访问状态flag
void search(Tree t, int x) {
	if (t == NULL) {
		return;
	}
	if (t->data == x) {
		t->flag = 1;
		return;
	} else {
		search(t->left, x);
		search(t->right, x);
	}
}
// 后序遍历
bool flag = false;
void postOrderTraversal(Tree t) {
	if (t) {
		postOrderTraversal(t->left);
		postOrderTraversal(t->right);
		if (!flag) {
			flag = true;
			printf("%d", t->data);
		} else {
			printf(" %d", t->data);
		}
	}
}
// 释放树所占的空间
void freeTree(Tree t) {
	if (t->left) {
		freeTree(t->left);
	}
	if (t->right) {
		freeTree(t->right);
	}
	free(t);
}
int main() {
	int n;
	scanf("%d", &n);
	int data[n];
	int index = 0;
	Tree t;
	for (int i = 0; i < 2 * n; i++) {
		char str[5];
		scanf("%s", str);
		if (strcmp(str, "Push") == 0) {
			scanf("%d", &data[index]);
			t = insert(t, data[index++]);
		} else {
			search(t, data[--index]);
		}
	}
	postOrderTraversal(t);
	freeTree(t);
	return 0;
}
