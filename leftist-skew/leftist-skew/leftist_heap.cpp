#include<iostream>


struct Node
{
	Node *left;
	Node *right;
	int  data;
	int  npl;
};

class LeftHeap
{
public:
	LeftHeap();
	~LeftHeap();

	void Insert(int data);
	int  Delete();
	int  GetMin() const;
	bool IsEmpty() const;


private:

	Node *_leftHeap;

	Node* _Merge(Node* h1, Node* h2);
	Node* _MergeImp(Node* h1, Node* h2);
	void  _SwapChildren(Node* root);
};


LeftHeap::LeftHeap()
{
	_leftHeap = NULL;
}

LeftHeap::~LeftHeap()
{
	while (IsEmpty() == false)
	{
		Delete();
	}
}

void LeftHeap::Insert(int data)
{
	Node *node = new Node;
	node->data = data;
	node->left = node->right = NULL;
	node->npl = 0;

	_leftHeap = _Merge(_leftHeap, node);

}

int  LeftHeap::Delete()
{

	int data = _leftHeap->data;

	Node *left = _leftHeap->left;
	Node *right = _leftHeap->right;

	delete _leftHeap;
	_leftHeap = _Merge(left, right);

	return data;
}

int  LeftHeap::GetMin() const
{
	return _leftHeap->data;
}

bool LeftHeap::IsEmpty() const
{
	return (_leftHeap == NULL);
}

void  LeftHeap::_SwapChildren(Node* root)
{
	Node *tmp = root->left;
	root->left = root->right;
	root->right = tmp;
}

Node* LeftHeap::_Merge(Node* h1, Node* h2)
{
	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h1;

	if (h1->data < h2->data)
		return _MergeImp(h1, h2);
	else
		return _MergeImp(h2, h1);
}

Node* LeftHeap::_MergeImp(Node* h1, Node* h2)
{
	if (h1->right == NULL)
	{
		h1->right = h2;
	}
	else
	{
		h1->right = _Merge(h1->right, h2);
		if (h1->left->npl < h1->right->npl)
			_SwapChildren(h1);

		h1->npl = h1->right->npl + 1;
	}
	return h1;
}