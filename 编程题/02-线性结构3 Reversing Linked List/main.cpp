#include <cstdio>
#include <cstdlib>

typedef struct Node {
	int address;
	int data;
	int nextAddress;//用于构建链表，输出时不用
	Node * next;
} LinkedList;

void print(LinkedList * list) {
	LinkedList * p = list;
	while (p != NULL) {
		printf("%05d %d ", p->address, p->data);
		if (p->next == NULL) {
			printf("%d", -1);
		} else {
			printf("%05d", p->next->address);
		}
		printf("\n");
		p = p->next;
	}
}
void reverse(LinkedList * &list, int k) {
	LinkedList * p = list->next;
	list->next = NULL;
	LinkedList * start = p, *rear;
	rear = list;
	int count = 0;
	while (p != NULL) {
		count++;
		if (count % k == 0) {
			LinkedList * end = p, *q = start, *temp;
			p = p->next;
			end->next = NULL;
			LinkedList * list2 = (LinkedList *) malloc(sizeof(LinkedList));
			list2->next = NULL;
			//头插法
			while (q != NULL) {
				temp = q->next;
				q->next = list2->next;
				list2->next = q;
				q = temp;
			}
			rear->next = list2->next;
			rear = start;
			free(list2);

			start = p;

		} else {
			p = p->next;
		}
	}
	if (count % k != 0) {
		rear->next = start;
	}
}
int main() {
	LinkedList * list, *rear, *node;
	list = (LinkedList *) malloc(sizeof(LinkedList));
	rear = list;
	int firstAddress, n, k,address, data, nextAddress;
	node = (LinkedList *) malloc(sizeof(LinkedList));
	scanf("%d %d %d", &firstAddress, &n, &k);
	node->address = firstAddress;
	node->next= NULL;
	rear->next = node;
	rear = node;

	while (n--) {

		scanf("%d %d %d", &address, &data, &nextAddress);
		if (address == list->next->address) {
			list->next->data = data;
			list->next->nextAddress = nextAddress;
		} else {
			node = (LinkedList *) malloc(sizeof(LinkedList));
			node->address = address;
			node->data = data;
			node->nextAddress = nextAddress;
			node->next = NULL;

			rear->next = node;
			rear = node;
		}

	}
	node = list->next;
	while (node != NULL) {
		//若有多余结点，其不在该链表上
		if(node->nextAddress == -1) {
			node->next = NULL;
			break;
		}
		LinkedList * node2 = node, *temp;
		while (node2->next != NULL && node2->next->address != node->nextAddress) {
			node2 = node2->next;
		}
		if (node2->next != NULL) {
			temp = node2->next;
			node2->next = temp->next;

			temp->next = node->next;
			node->next = temp;

		}
		node = node->next;
	}

	reverse(list, k);
	print(list->next);
	return 0;
}
