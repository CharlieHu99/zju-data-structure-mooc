#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main() {
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);

	return 0;
}
Position BinarySearch2(List L, ElementType X, Position left, Position right) {
	if (left <= right) {
		Position mid = (left + right) / 2;
		if (L->Data[mid] == X) {
			return mid;
		} else if (L->Data[mid] > X) {
			return BinarySearch2(L, X, left, mid - 1);
		} else {
			return BinarySearch2(L, X, mid + 1, right);
		}
	}
	return NotFound;
}
Position BinarySearch(List L, ElementType X) {
	return BinarySearch2(L, X, 1, L->Last);
}

