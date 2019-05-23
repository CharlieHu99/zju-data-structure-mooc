#include <cstdio>
//在线处理 最大子列和问题
int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	int sum = 0, maxSum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
		if (sum > maxSum) {
			maxSum = sum;
		} else if (sum < 0) {
			sum = 0;
		}
	}
	printf("%d\n", maxSum);
	return 0;
}
