#include "AvlTree.h"

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMin(
		AvlNode *t) const {
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMax(
		AvlNode *t) const {
	if (t == NULL)
		return NULL;
	if (t->right == NULL)
		return t;
	return findMax(t->right);
}

/**
 * Internal method to test if an item is in a subtree.
 * x is item to search for.
 * t is the node that roots the subtree.
 */
template<typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable & x, AvlNode *t) const {
	if (t == NULL)
		return false;
	else if (t->element > x)
		return contains(x, t->left);
	else if (x > t->element)
		return contains(x, t->right);
	else
		return true; // Match
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template<typename Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, AvlNode * & t) {
	if (t == NULL)
		t = new AvlNode(x, NULL, NULL);
	else if (t->element > x) {
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2) {
			if (t->left->element > x)
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
	} else if (x > t->element) {
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2) {
			if (x > t->right->element)
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
	} else
		; // Duplicate; do nothing
	t->height = std::max(height(t->left), height(t->right)) + 1;
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template<typename Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode * & t) {
	if (t == NULL)
		return;
	// Item not found; do nothing
	if (t->element > x) {
		remove(x, t->left);
		if (height(t->right) - height(t->left) == 2) {
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
	} else if (x > t->element) {
		remove(x, t->right);
		if (height(t->left) - height(t->right) == 2) {
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
	} else if (t->left != NULL && t->right != NULL) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
		t->height = std::max(height(t->left), height(t->right)) + 1;
	} else {
		AvlNode *oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}

	if (t != NULL)
		t->height = std::max(height(t->left), height(t->right)) + 1;
}

/**
 * Internal method to make subtree empty.
 */
template<typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode * & t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

/**
 * Internal method to clone subtree.
 */
template<typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::clone(
		AvlNode *t) const {
	if (t == NULL)
		return NULL;
	return new AvlNode(t->element, clone(t->left), clone(t->right));
}

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template<typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode *t, std::ostream & out) const {
	if (t != NULL) {
		printTree(t->left, out);
		out << t->element << ' ';
		printTree(t->right, out);
	}
}

/**
 * Return the height of node t or -1 if NULL.
 */
template<typename Comparable>
int AvlTree<Comparable>::height(AvlNode *t) const {
	return t == NULL ? -1 : t->height;
}

/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
template<typename Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode * & k2) {
	AvlNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	k1->height = std::max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
template<typename Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode * & k2) {
	AvlNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = std::max(height(k2->right), height(k2->left)) + 1;
	k1->height = std::max(height(k1->right), k2->height) + 1;
	k2 = k1;
}

/**
 * Double rotate binary tree node: first left child
 * with its right child; then node k3 with new left child.
 * For AVL trees, this is a double rotation for case 2.
 * Update heights, then set new root.
 */
template<typename Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode * & k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/**
 * Double rotate binary tree node: first right child
 * with its left child; then node k3 with new right child.
 * For AVL trees, this is a double rotation for case 2.
 * Update heights, then set new root.
 */
template<typename Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode * & k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}

/**
 * Internal method to compute the height of a subtree rooted at t.
 */
template<typename Comparable>
int AvlTree<Comparable>::treeHeight(AvlNode *t) const {
	if (t == NULL)
		return -1;
	else
		return 1 + std::max(treeHeight(t->left), treeHeight(t->right));
}
