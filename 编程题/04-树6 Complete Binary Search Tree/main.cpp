#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

// 计算左子树的元素个数
int getLeftLength(int n) {
	int h = (int) log2(n + 1);
	int x = n - (pow(2, h) - 1);
	x = x < pow(2, h - 1) ? x : pow(2, h - 1);
	return x + pow(2, h - 1) - 1;
}
// 创建完全二叉搜索树
void createCBST(int t[], int arr[], int root, int low, int high) {
	int len = high - low + 1;
	if (len == 0) {
		return;
	}
	int leftLen = getLeftLength(len);
	t[root] = arr[low + leftLen];
	int left = 2 * root + 1;
	int right = left + 1;
	createCBST(t, arr, left, low, low + leftLen - 1);
	createCBST(t, arr, right, low + leftLen + 1, high);
}

int main() {
	int n;
	scanf("%d", &n);
	int arr[n], t[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);
	createCBST(t, arr, 0, 0, n - 1);
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%d", t[i]);
	}
	printf("\n");
	return 0;
}
