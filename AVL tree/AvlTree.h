#include <iostream>

template<typename Comparable>
class AvlTree {
public:
	AvlTree() {
		root = NULL;
	} // Constructor

	AvlTree(const AvlTree & rhs) {
		root = NULL;
		*this = rhs;
	} // Copy Constructor

	const AvlTree & operator=(const AvlTree & rhs) {
		if (this != &rhs) {
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	} // Overload "operator="

	~AvlTree() {
		makeEmpty();
	} // Destructor



	const Comparable & findMin() const {
		return findMin(root);
	} // Find Minimum Element

	const Comparable & findMax() const {
		return findMax(root);
	} // Find Maximum Element

	bool contains(const Comparable & x) const {
		return contains(x, root);
	} // Test if an item is in the tree.

	bool isEmpty() const {
		return root == NULL;
	} // Test if the tree is empty.

	void makeEmpty() {
		makeEmpty(root);
	} // Make the tree empty.

	void insert(const Comparable & x) {
		insert(x, root);
	} // Insert an item into the tree.

	void remove(const Comparable & x) {
		remove(x, root);
	} // Remove an item from the tree.

	void printTree(std::ostream & out = std::cout) const {
		if (isEmpty())
			out << "Empty Tree" << std::endl;
		else
			printTree(root, out);
	} // Print the tree in sorted order.

	int treeHeight() const {
		return treeHeight(root);
	} // Compute the height of the tree.

private:
	struct AvlNode {
		Comparable element;
		AvlNode *left;
		AvlNode *right;
		int height;

		AvlNode(const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h =0) :element(theElement), left(lt), right(rt), height(h) {}£»
	};

	AvlNode *root;

	void insert(const Comparable & x, AvlNode * & t);
	void remove(const Comparable & x, AvlNode * & t);
	AvlNode * findMin(AvlNode *t) const;
	AvlNode * findMax(AvlNode *t) const;
	bool contains(const Comparable & x, AvlNode *t) const;
	void makeEmpty(AvlNode * & t);
	void printTree(AvlNode *t, std::ostream & out) const;
	int treeHeight(AvlNode *t) const;
	AvlNode * clone(AvlNode *t) const;
	int height(AvlNode *t) const;
	void rotateWithLeftChild(AvlNode * & k2);
	void rotateWithRightChild(AvlNode * & k2);
	void doubleWithLeftChild(AvlNode * & k3);
	void doubleWithRightChild(AvlNode * & k3);
}
;
