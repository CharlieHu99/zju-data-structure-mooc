
#include <cstdio>
#include <cstdlib>

struct TreeNode {
	int data;
	int flag;
	TreeNode * left;
	TreeNode * right;
};
typedef struct TreeNode * Tree;
// 创建新的结点
Tree newNode(int x) {
	Tree t = (Tree) malloc(sizeof(struct TreeNode));
	t->data = x;
	t->left = t->right = NULL;
	t->flag = 0;
	return t;
}
// 在二叉搜索树中插入新的结点
Tree insert(Tree t, int x) {
	if (t == NULL) {
		t = newNode(x);
	} else {
		if (x > t->data) {
			t->right = insert(t->right, x);
		} else {
			t->left = insert(t->left, x);
		}
	}
	return t;
}
// 创建二叉搜索树
Tree createTree(int n) {
	int x;
	scanf("%d", &x);
	Tree t = newNode(x);
	for (int i = 1; i < n; i++) {
		scanf("%d", &x);
		t = insert(t, x);
	}
	return t;
}
//释放二叉搜索树所占的空间
void freeTree(Tree t) {
	if (t->left) {
		freeTree(t->left);
	}
	if (t->right) {
		freeTree(t->right);
	}
	free(t);
}

/*
//解法三：只创建一棵树
//若每次搜索所经过的结点在前面的搜索中均出现过，则一致；
//否则，若某次搜索中遇到了前面未出现过的结点，则不一致。
bool check(Tree t, int x) {
	if (t->flag == 1) {
		if (x < t->data) {
			return check(t->left, x);
		} else if (x > t->data) {
			return check(t->right, x);
		} else {
			return false;
		}
	} else {
		if (t->data == x) {
			t->flag = 1;
			return true;
		} else {
			return false;
		}
	}
}
bool judge(Tree t, int n) {
	int x;
	scanf("%d", &x);
	// flag： true表示目前还一致，false表示已经不一致
	bool flag = true;
	if (t->data != x) {
		flag = false;
	} else {
		t->flag = 1;
	}
	for (int i = 1; i < n; i++) {
		scanf("%d", &x);
		//若发现某个中间数字已经不一致时，仍需要继续执行循环
		if (!check(t, x)) {
			if (!flag) {
				continue;
			} else {
				flag = false;
			}
		}
	}
	return flag;
}
//重置树的访问情况
void resetT(Tree t) {
	if (t->left) {
		resetT(t->left);
	}
	if (t->right) {
		resetT(t->right);
	}
	t->flag = 0;
}

int main() {
	int n, l;
	while (scanf("%d", &n), n) {
		scanf("%d", &l);
		Tree t = createTree(n);
		for (int i = 0; i < l; i++) {
			if (judge(t, n)) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
			resetT(t);
		}
		freeTree(t);
	}
	return 0;
}
*/
//解法二：不创建树

//解法一：创建两棵树
bool equals(Tree t1,Tree t2) {
	if(t1 == NULL && t2 == NULL) {
		return true;
	}
	if(t1 == NULL || t2 == NULL) {
		return false;
	}
	if(t1->data != t2->data) {
		return false;
	}
	return equals(t1->left,t2->left) && equals(t1->right,t2->right);
}
int main() {
	int n, l;
	while (scanf("%d", &n), n) {
		scanf("%d", &l);
		Tree t1 = createTree(n);
		for(int i=0;i<l;i++) {
			Tree t2 = createTree(n);
			if(equals(t1,t2)) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
			freeTree(t2);
		}
		freeTree(t1);
	}
	return 0;
}
