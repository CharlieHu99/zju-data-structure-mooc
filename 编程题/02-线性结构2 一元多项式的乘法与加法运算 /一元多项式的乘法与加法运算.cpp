#include <cstdio>
#include <cstdlib>

struct Polynomial {
	int coefficient;
	int exponent;
	struct Polynomial * next;
};
void append(int coefficient, int exponent, Polynomial * &rear) {
	Polynomial * node = (Polynomial *) malloc(sizeof(Polynomial));
	node->coefficient = coefficient;
	node->exponent = exponent;
	node->next = NULL;
	rear->next = node;
	rear = node;
}
Polynomial * add(Polynomial * p1, Polynomial * p2) {
	Polynomial * p, *rear;
	p = (Polynomial *) malloc(sizeof(Polynomial));
	p->next = NULL;
	rear = p;
	while (p1 && p2) {
		if (p1->exponent == p2->exponent) {
			if (p1->coefficient + p2->coefficient) {
				append(p1->coefficient + p2->coefficient, p1->exponent, rear);
			}
			p1 = p1->next;
			p2 = p2->next;
		} else if (p1->exponent > p2->exponent) {
			append(p1->coefficient, p1->exponent, rear);
			p1 = p1->next;
		} else {
			append(p2->coefficient, p2->exponent, rear);
			p2 = p2->next;
		}
	}
	while (p1) {
		append(p1->coefficient, p1->exponent, rear);
		p1 = p1->next;
	}
	while (p2) {
		append(p2->coefficient, p2->exponent, rear);
		p2 = p2->next;
	}
	Polynomial * temp = p;
	p = p->next;
	free(temp);
	return p;
}
Polynomial * multiply(Polynomial * p1, Polynomial * p2) {
	Polynomial * p, *rear, *node, *t1, *t2, *temp;
	if (!p1 || !p2) {
		return NULL;
	}
	p = (Polynomial *) malloc(sizeof(Polynomial));
	p->next = NULL;
	rear = p;
	t2 = p2;
	t1 = p1;
	while (t2) {
		append(t1->coefficient * t2->coefficient, t1->exponent + t2->exponent,
				rear);
		t2 = t2->next;
	}
	t1 = t1->next;
	while (t1) {
		t2 = p2;
		rear = p;
		while (t2) {
			int coefficient = t1->coefficient * t2->coefficient;
			int exponent = t1->exponent + t2->exponent;
			while (rear->next && rear->next->exponent > exponent) {
				rear = rear->next;
			}
			//若该指数已存在
			if (rear->next && rear->next->exponent == exponent) {
				if (rear->next->coefficient + coefficient) {
					rear->next->coefficient += coefficient;
				} else {
					//若系数相加为0，则从原来的多项式中删除该项
					temp = rear->next;
					rear->next = temp->next;
					free(temp);
				}
			} else {
				//该指数不存在，直接将其插入
				Polynomial * node = (Polynomial *) malloc(sizeof(Polynomial));
				node->coefficient = coefficient;
				node->exponent = exponent;
				node->next = rear->next;
				rear->next = node;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	temp = p;
	p = p->next;
	free(temp);
	return p;
}
void print(Polynomial * p) {
	if(!p) {
		printf("0 0");
	} else {
		while (p) {
			printf("%d %d", p->coefficient, p->exponent);
			if (p->next) {
				printf(" ");
			}
			p = p->next;
		}
	}
	printf("\n");
}
Polynomial * input() {
	int n;
	scanf("%d", &n);
	Polynomial * p, *rear;
	p = (Polynomial *) malloc(sizeof(Polynomial));
	rear = p;
	while (n--) {
		Polynomial * node = (Polynomial *) malloc(sizeof(Polynomial));
		scanf("%d %d", &node->coefficient, &node->exponent);
		rear->next = node;
		rear = node;
	}
	Polynomial * temp = p;
	p = p->next;
	free(temp);
	return p;
}
int main() {
	Polynomial * p1 = input();
	Polynomial * p2 = input();
	Polynomial * pAdd = add(p1, p2);
	Polynomial * pMultiply = multiply(p1, p2);
	print(pMultiply);
	print(pAdd);
	return 0;
}
