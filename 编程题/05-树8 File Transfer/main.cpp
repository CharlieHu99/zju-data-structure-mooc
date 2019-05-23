#include <cstdio>

int find(int arr[], int x) {
	if (arr[x] < 0) {
		return x;
	}
	// 路径压缩
	arr[x] = find(arr, arr[x]);
	return arr[x];
}

void set_union(int arr[], int root1, int root2) {
	if (root1 == root2) {
		return;
	}
	//arr[root2] = root1;
	// 按秩归并,根结点存储树的高度的相反数
	if (arr[root1] < arr[root2]) {
		arr[root2] = root1;
	} else {
		if (arr[root1] == arr[root2]) {
			arr[root2] -= 1;
		}
		arr[root1] = root2;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	getchar();
	char c;
	int c1, c2;
	int arr[n + 1];
	for (int i = 0; i < n + 1; i++) {
		arr[i] = -1;
	}
	while (scanf("%c", &c), c != 'S') {
		scanf("%d %d", &c1, &c2);
		int root1 = find(arr, c1);
		int root2 = find(arr, c2);
		if (c == 'I') {
			set_union(arr, root1, root2);
		} else if (c == 'C') {
			if (root1 == root2) {
				printf("yes\n");
			} else {
				printf("no\n");
			}
		}
		getchar();
	}
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		if (arr[i] < 0) {
			count++;
		}
	}
	if (count == 1) {
		printf("The network is connected.");
	} else {
		printf("There are %d components.", count);
	}
	return 0;
}
