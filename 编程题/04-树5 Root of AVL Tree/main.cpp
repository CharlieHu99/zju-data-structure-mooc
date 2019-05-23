#include <cstdio>
#include <cstdlib>

typedef struct AVLNode * AVLTree; /* AVL树类型 */
struct AVLNode {
	int data; /* 结点数据 */
	AVLTree left; /* 指向左子树 */
	AVLTree right; /* 指向右子树 */
	int height; /* 树高 */
};

int max(int a, int b) {
	return a >= b ? a : b;
}

int getHeight(AVLTree a) {
	return a == NULL ? 0 : a->height;
}

// LL
AVLTree singleLeftRotation(AVLTree a) {
	AVLTree b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
	b->height = max(getHeight(b->left), a->height) + 1;
	return b;
}

// RR
AVLTree singleRightRotation(AVLTree a) {
	AVLTree b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
	b->height = max(a->height, getHeight(b->right)) + 1;
	return b;
}

// LR
AVLTree doubleLeftRightRotation(AVLTree a) {
	a->left = singleRightRotation(a->left);
	return singleLeftRotation(a);
}

// RL
AVLTree doubleRightLeftRotation(AVLTree a) {
	a->right = singleLeftRotation(a->right);
	return singleRightRotation(a);
}

AVLTree insert(AVLTree t, int x) {
	if (!t) {
		t = (AVLTree) malloc(sizeof(struct AVLNode));
		t->data = x;
		t->height = 0;
		t->left = t->right = NULL;
	} else if (x < t->data) {
		t->left = insert(t->left, x);
		if (getHeight(t->left) - getHeight(t->right) == 2) {
			if (x < t->left->data) {
				t = singleLeftRotation(t);
			} else {
				t = doubleLeftRightRotation(t);
			}
		}
	} else if (x > t->data) {
		t->right = insert(t->right, x);
		if (getHeight(t->right) - getHeight(t->left) == 2) {
			if (x > t->right->data) {
				t = singleRightRotation(t);
			} else {
				t = doubleRightLeftRotation(t);
			}
		}
	}

	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	return t;
}

int main() {
	int n, x;
	scanf("%d", &n);
	AVLTree t;
	while (n--) {
		scanf("%d", &x);
		t = insert(t, x);
	}
	printf("%d\n", t->data);
	free(t);
	return 0;
}
