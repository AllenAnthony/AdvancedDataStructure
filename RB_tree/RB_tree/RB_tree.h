#ifndef  BR_TREE_H
#define BR_TREE_H

#include<iostream>
#include<stack>
using namespace std;

#define BLACK 0
#define RED 1

template <class T>
class BRtreeNode
{
public:
	BRtreeNode() :key(T()), color(BLACK), Parent(NULL), Left(NULL), Right(NULL){};
	BRtreeNode(T key, int color, BRtreeNode<T>* Parent, BRtreeNode<T>* Left, BRtreeNode<T>* Right) :key(key), color(color), Parent(Parent), Left(Left), Right(Right){};
	T key;
	int color;
	BRtreeNode<T>* Parent;
	BRtreeNode<T>* Left;
	BRtreeNode<T>* Right;
};

template <class T>
class BRtree
{
public:
	BRtree();//构造函数
	int get_min(T&)const;//调用get_min()
	int get_max(T&)const;//调用get_max()
	int search_element(const T& K)const; //调用search_node(k)
	BRtreeNode<T>* get_root()const;//公有函数，返回root
	~BRtree();//析构函数
	int delete_tree(const T&);//利用二叉搜索树中的delete后，调用delete_fix(node);
	int insert_tree(const T&);//调用insert_fix(node)
	void inorder()const;//循环中序遍历

private:
	BRtreeNode<T>* root;
	static BRtreeNode<T>* NIL;
    void insert_fix(BRtreeNode<T>*);
	void delete_fix(BRtreeNode<T>*);
	void empty(BRtreeNode<T>*);
	void rotateWleft(BRtreeNode<T>*);
	void rotateWright(BRtreeNode<T>*);

	BRtreeNode<T>* get_min(BRtreeNode<T>*)const;
	BRtreeNode<T>* get_max(BRtreeNode<T>*)const;
	BRtreeNode<T>* search_node(const T& k)const;

};

#endif