#include <cstdio>
//在线处理 最大子列和问题
int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	int sum = 0, maxSum = 0;
	int first = 0, last = 0, temp = 0;
	bool isPositive = false, isFirst = true;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] >= 0) {
			isPositive = true;
		}
		sum += arr[i];
		if (isFirst) {
			temp = arr[i];
			isFirst = false;
		}
		if (sum > maxSum) {
			maxSum = sum;
			first = temp;
			last = arr[i];
		} else if (sum < 0) {
			sum = 0;
			isFirst = true;
		}
	}
	if (isPositive) {
		printf("%d %d %d\n", maxSum, first, last);
	} else {
		printf("%d %d %d\n", 0, arr[0], arr[n - 1]);
	}
	return 0;
}
