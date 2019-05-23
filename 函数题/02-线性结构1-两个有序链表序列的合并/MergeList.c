#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}
List Read() {
	int n;
	scanf("%d",&n);
	List L = (List)malloc(sizeof(struct Node));
	List r = L;
	List node;
	for(int i=0;i<n;i++) {
		node = (List)malloc(sizeof(struct Node));
		scanf("%d",&node->Data);
		r->Next = node;
		r = node;
	}
	r->Next = NULL;
	return L;
}
void Print( List L ) {
	List p = L->Next;
	if(p == NULL) {
		printf("NULL\n");
		return;
	}
	while(p != NULL) {
		printf("%d ",p->Data);
		p = p ->Next;
	}
	printf("\n");
}
List Merge( List L1, List L2 ) {
	List list,p = L1->Next,q = L2->Next;
	L1 -> Next = L2 ->Next = NULL;
	list = (List)malloc(sizeof(struct Node));
	List r = list;
	while(p != NULL && q != NULL) {
		if(p->Data <= q->Data) {
			r->Next = p;
			r = p;
			p = p->Next;
		} else {
			r->Next = q;
			r = q;
			q = q->Next;
		}
	}
	if(p != NULL) {
		r->Next = p;
	}
	if(q != NULL) {
		r->Next = q;
	}
	return list;
}
