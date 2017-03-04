#include"RB_tree.h"
//此程序还未debug

template <class T>
BRtreeNode<T>* BRtree<T>::NIL=new BRtreeNode<T>();

template <class T>
BRtree<T>::BRtree()//构造函数
{
	root = NIL;
}

template <class T>
int BRtree<T>::get_min(T& Ret)const//调用get_min()
{
	if (root!=NIL)
	{
		Ret = get_min(root)->key;
		return 1;
	}
	else
		return 0;

}

template <class T>
int BRtree<T>::get_max(T& Ret)const//调用get_max()
{
	if (root!=NIL)
	{
		Ret = get_max(root)->key;
		return 1;
	}
	else
		return 0;
}

template<class T>
int BRtree<T>::search_element(const T& K)const //调用search_node(k)
{
	return !(NIL == search_node(K));
}

template<class T>
BRtreeNode<T>* BRtree<T>::get_root()const//公有函数，返回root
{
	return root;
}

template<class T>
BRtree<T>::~BRtree()//析构函数
{
	empty(root);
}

template<class T>
int BRtree<T>::delete_tree(const T& k)//利用二叉搜索树中的delete后，调用delete_fix(node)
{
	BRtreeNode<T>* node;
	node = search_node(k);
	if (node==NIL)
		return 0;

	BRtreeNode<T>* tmp;
	if (NIL == node->Left || NIL == node->Right)
		tmp = node;
	else
	{
		tmp = get_min(node->Right);
		node->key = tmp->key;
	}

	BRtreeNode<T>* ctmp;
	if (NIL != tmp->Right)
		ctmp = tmp->Right;
	else
		ctmp = tmp->Left;

	if (ctmp != NIL)
	   ctmp->Parent = tmp->Parent;

	if (tmp->Parent == NIL)
		root = ctmp;
	else if (tmp == tmp->Parent->Right)
		tmp->Parent->Right = ctmp;
	else
		tmp->Parent->Right = ctmp;

	if (tmp->color==BLACK)
	delete_fix(ctmp);

	delete(tmp);
	return 1;
}

template<class T>
int BRtree<T>::insert_tree(const T& K)//调用insert_fix(node)
{
	BRtreeNode<T>*node = &BRtreeNode<T>(K, RED, NIL, NIL, NIL);
	BRtreeNode<T>* RT = root;
	BRtreeNode<T>*PRT=NIL;

	while (RT != NIL)
	{
		PRT = RT;
		if (RT->key > K)
			RT = RT->Left;
		else
			RT = RT->Right;
	}

	if (PRT == NIL)
		root = node;
	else if (PRT->key > node->key)
		PRT->Left = node;
	else
		PRT->Right = node;

	insert_fix(node);
	return 1;

}

template<class T>
void BRtree<T>::insert_fix(BRtreeNode<T>* node)
{
	BRtreeNode<T>* uncle;
	while (node->Parent->color == RED)
	{
		if (node->Parent==node->Parent->Parent->Left)
		{
			uncle = node->Parent->Parent->Right;
			if (uncle->color == RED)
			{
				node->Parent->color = BLACK;
				uncle->color = BLACK;
				node->Parent->Parent->color = RED;
				node = node->Parent->Parent;
			}
			else
			{
				if (node->Parent->Right == node)
				{
					node = node->Parent;
					rotateWright(node);
				}
				node->Parent->color = BLACK;
				node->Parent->Parent->color = RED;
				rotateWleft(node->Parent->Parent);
			}
		}
		else
		{
			uncle = node->Parent->Parent->Left;
			if (uncle->color == RED)
			{
				node->Parent->color = BLACK;
				uncle->color = BLACK;
				node->Parent->Parent->color = RED;
				node = node->Parent->Parent;
			}
			else
			{
				if (node->Parent->Left == node)
				{
					node = node->Parent;
					rotateWleft(node);
				}
				node->Parent->color = BLACK;
				node->Parent->Parent->color = RED;
				rotateWright(node->Parent->Parent);
			}
		}
	}

	root->color = BLACK;
}

template<class T>
void BRtree<T>::delete_fix(BRtreeNode<T>* node)
{
	BRtreeNode<T>* bro;

	while (node != root && node->color == BLACK)
	{
		if (node->Parent->Left==node)
		{
			bro = node->Parent->Right;
			if (bro->color == RED)
			{
				bro->color = BLACK;
				node->Parent->color = RED;
				rotateWright(node->Parent);
				bro = node->Parent->Right;
			}
			else if (bro->Left->color==BLACK && bro->Right->color==BLACK)
			{
				bro->color = RED;
				node = node->Parent;
			}
			else
			{
			     if (bro->Left->color == RED && bro->Right->color == BLACK)
			    {
				   bro->color = RED;
				   bro->Left->color = BLACK;
				   rotateWleft(bro);
			    }
				 bro = node->Parent->Right;
				 bro->color = node->Parent->color;
				 node->Parent->color = BLACK;
				 bro->Right->color = BLACK;
				 rotateWright(node->Parent);
				 node = root;

			}
			
		}
		else
		{
			bro = node->Parent->Left;
			if (bro->color == RED)
			{
				bro->color = BLACK;
				node->Parent->color = RED;
				rotateWleft(node->Parent);
				bro = node->Parent->Left;
			}
			else if (bro->Left->color == BLACK && bro->Right->color == BLACK)
			{
				bro->color = RED;
				node = node->Parent;
			}
			else
			{
				if (bro->Right->color == RED && bro->Left->color == BLACK)
				{
					bro->color = RED;
					bro->Right->color = BLACK;
					rotateWright(bro);
				}
				bro = node->Parent->Left;
				bro->color = node->Parent->color;
				node->Parent->color = BLACK;
				bro->Left->color = BLACK;
				rotateWleft(node->Parent);
				node = root;

			}
		}
	}

	node->color = BLACK;
}

template<class T>
void BRtree<T>::inorder()const//循环中序遍历
{
	if (NIL == root)
		return;

	BRtreeNode<T>* ptm = root;
	stack<BRtreeNode<T>*> S;
	while (ptm!=NIL || !S.empty() )
	{
		if (ptm != NIL)
		{
			S.push(ptm);
			ptm = ptm->Left;
		}
		else
		{
			ptm = S.top();
			cout << ptm->key << ":" << (ptm->color == BLACK) ? "BLACK" : "RED";
			S.pop();
			ptm = ptm->Right;
		
		}
	}
}


template<class T>
void BRtree<T>::empty(BRtreeNode<T>* node)
{
	if (node == NIL)
		return;

	BRtreeNode<T>* tmp=node;
	empty(node->Left);
	empty(node->Right);

	delete(tmp);

}

template<class T>
void BRtree<T>::rotateWleft(BRtreeNode<T>* node)
{
	BRtreeNode<T>* leftnode = node->Left;

	if (node->Parent = NIL)
	{
		root = leftnode;
	}
	else if (node->Parent->Left == node)
	{
		node->Parent->Left = leftnode;
		leftnode->Parent = node->Parent;
	}
	else
	{
		node->Parent->Right = leftnode;
		leftnode->Parent = node->Parent;
	}

	node->Left = leftnode->Right;
	if (leftnode->Right!=NIL)
	   leftnode->Right->Parent = node;

	node->Parent = leftnode;
	leftnode->Right = node;

}

template<class T>
void BRtree<T>::rotateWright(BRtreeNode<T>* node)
{
	BRtreeNode<T>* rightnode = node->Right;

	if (node->Parent = NIL)
	{
		root = rightnode;
	}
	else if (node->Parent->Left == node)
	{
		node->Parent->Left = rightnode;
		rightnode->Parent = node->Parent;
	}
	else
	{
		node->Parent->Right = rightnode;
		rightnode->Parent = node->Parent;
	}

	node->Right = rightnode->Left;
	if (rightnode->Left != NIL)
		rightnode->Left->Parent = node;

	node->Parent = rightnode;
	rightnode->Left = node;
}

template<class T>
BRtreeNode<T>* BRtree<T>::get_min(BRtreeNode<T>*)const
{
	BRtreeNode<T>* node = root;
	if (node == NIL)
		return NIL;

	while (node->Left != NIL)
		node = node->Left;

	return node;
}


template<class T>
BRtreeNode<T>* BRtree<T>::get_max(BRtreeNode<T>*)const
{
	BRtreeNode<T>* node = root;
	if (node == NIL)
		return NIL;

	while (node->Right != NIL)
		node = node->Left;

	return node;
}

template<class T>
BRtreeNode<T>* BRtree<T>::search_node(const T& K)const
{
	BRtreeNode<T>* node = root;

	while (node != NIL && node->key != K)
	{
		if (node->key > K)
			node = node->Left;
		if (node->key < K)
			node = node->Right;
	}

	return node;
}

int main()
{
	BRtree<int> rbtree;
	int value;
	rbtree.insert_tree(41);
	rbtree.insert_tree(38);
	rbtree.insert_tree(31);
	rbtree.insert_tree(12);
	rbtree.insert_tree(19);
	rbtree.insert_tree(8);
	cout << "root is: " << rbtree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	rbtree.inorder();
	if (rbtree.get_min(value) == 0)
		cout << "minmum is: " << value << endl;
	if (rbtree.get_max(value) == 0)
		cout << "maxmum is: " << value << endl;
	if (rbtree.delete_tree(38) == 0)
		cout << "delete 38 successfully" << endl;
	cout << "root is: " << rbtree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	rbtree.inorder();
	return 0;
}