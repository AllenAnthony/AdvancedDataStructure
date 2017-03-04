#include<stdio.h>
#include<stdlib.h>


typedef struct BinNode *Position;
typedef struct BinNode *BinTree;
typedef struct Collection *BinQueue;
typedef int ElementType;
#define MaxTree 1000
#define Infinity 1000000
struct BinNode
{
	ElementType Element;
	Position LeftChild;
	Position Sibling;
};
struct Collection
{
	int CurrentSize;
	int Capacity;
	struct BinNode* TheTrees[MaxTree];
};


BinTree CombineTree(BinTree T1, BinTree T2);
BinQueue Merge(BinQueue H1, BinQueue H2);
BinQueue Initialize();
ElementType DeleteMin(BinQueue H);

BinTree CombineTree(BinTree T1, BinTree T2)
{
	if (T1->Element>T2->Element)
		return CombineTree(T2, T1);
	T2->Sibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, Carry = NULL;
	int i, j;
	if (H1->CurrentSize + H2->CurrentSize>H1->Capacity)
		printf("Exceed the Capacity");
	H1->CurrentSize = H1->CurrentSize + H2->CurrentSize;
	for (i = 0, j = 1; j<H1->CurrentSize; i++, j *= 2)
	{
		T1 = H1->TheTrees[i];
		T2 = H2->TheTrees[i];
		switch (!!T1 + 2 * !!T2 + 4 * !!Carry)
		{
		case 0: //No Trees  
		case 1: //Only H1  
			break;
		case 2:
			H1->TheTrees[i] = T2;
			H2->TheTrees[i] = NULL;
			break;
		case 4: //Only Carry  
			H1->TheTrees[i] = Carry;
			Carry = NULL;
			break;
		case 3: //T1,T2  
			Carry = CombineTree(T1, T2);
			H1->TheTrees[i] = H2->TheTrees[i] = NULL;
			break;
		case 5:
			Carry = CombineTree(T1, Carry);
			H1->TheTrees[i] = NULL;
			break;
		case 6:
			Carry = CombineTree(T2, Carry);
			H2->TheTrees[i] = NULL;
			break;
		case 7:
			H1->TheTrees[i] = Carry;
			Carry = CombineTree(T1, T2);
			H2->TheTrees[i] = NULL;
			break;
		}
	}
	return H1;
}

ElementType DeleteMin(BinQueue H)
{
	int i, j;
	int MinTree;
	BinQueue DeleteQueue;
	Position DeleteTree, OldRoot;
	ElementType MinItem;

	if (H->CurrentSize==0)
	{
		printf("Empty BinQueue!!");
		return -Infinity;
	}
	//find the minmum  
	MinItem = Infinity;
	for (i = 0; i<MaxTree; i++)
	{
		if (H->TheTrees[i] && H->TheTrees[i]->Element<MinItem)
		{
			// Updata the minmun  
			MinItem = H->TheTrees[i]->Element;
			MinTree = i;
		}
	}
	// have found the DeleteTree  
	DeleteTree = H->TheTrees[MinTree];
	OldRoot = DeleteTree;
	DeleteTree = OldRoot->LeftChild;
	free(OldRoot);

	// form the DeleteQueue  
	DeleteQueue = Initialize();
	DeleteQueue->CurrentSize = (1 << MinTree) - 1;

	for (j = MinTree - 1; j >= 0; j--)
	{
		DeleteQueue->TheTrees[j] = DeleteTree;
		DeleteTree = DeleteTree->Sibling;
		DeleteQueue->TheTrees[j]->Sibling = NULL;
	}
	H->TheTrees[MinTree] = NULL;
	H->CurrentSize -= DeleteQueue->CurrentSize + 1;

	Merge(H, DeleteQueue);
	return MinItem;

}