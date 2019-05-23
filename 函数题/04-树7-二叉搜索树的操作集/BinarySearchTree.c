#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

void PreorderTraversal( BinTree BT ) {
	if(BT != NULL) {
		printf("%d ",BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
void InorderTraversal( BinTree BT ) {
	if(BT != NULL) {
		InorderTraversal(BT->Left);
		printf("%d ",BT->Data);
		InorderTraversal(BT->Right);
	}
}

BinTree Insert( BinTree BST, ElementType X ) {
	if(BST == NULL) {
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	} else {
		if(BST->Data > X) {
			BST->Left = Insert(BST->Left,X);
		} else if(BST->Data < X) {
			BST->Right = Insert(BST->Right, X);
		}
	}
	return BST;
}
BinTree Delete( BinTree BST, ElementType X ) {
	//没找到该元素
	if(BST == NULL) {
		printf("Not Found\n");
	} else {
		if(BST->Data > X) {
			BST->Left = Delete(BST->Left,X);
		} else if(BST->Data < X) {
			BST->Right = Delete(BST->Right, X);
		} else {
			//BST即为要删除的结点
			BinTree temp;
			//既有左孩子，又有右孩子
			if(BST->Left != NULL && BST->Right != NULL) {
				//从右子树中寻找值最小的结点（即最右下的那个结点）
				temp = FindMin(BST->Right);
				BST->Data = temp->Data;
				BST->Right = Delete(BST->Right, BST->Data);//妙在这里
			} else {
				temp = BST;
				if(BST->Left == NULL) {
					BST = BST->Right;
				} else {
					BST = BST->Left;
				}
				free(temp);
			}
		}
	}
	return BST;
}
Position Find( BinTree BST, ElementType X ) {
	if(BST == NULL || BST->Data == X) {
		return BST;
	}
	if(BST->Data > X) {
		return Find(BST->Left,X);
	}
	return Find(BST->Right,X);
}
//返回二叉搜索树最左边结点的位置
Position FindMin( BinTree BST ) {
	if(BST == NULL || BST->Left == NULL) {
		return BST;
	}
	return FindMin(BST->Left);
}
//返回二叉搜索树最右边结点的位置
Position FindMax( BinTree BST ) {
	if(BST == NULL || BST->Right == NULL) {
		return BST;
	}
	return FindMax(BST->Right);
}
