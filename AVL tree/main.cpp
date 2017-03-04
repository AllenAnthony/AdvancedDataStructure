#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AvlTree.cpp"

int main() {
	AvlTree<int> t1;
	srand(time(NULL));
	for (int i = 0; i < 127; i++) {
		t1.insert(rand());
	}

	std::cout << "t1's height=" << t1.treeHeight() << std::endl;
	std::cout << "t1 is { ";
	t1.printTree();
	std::cout << "}" << std::endl;

	AvlTree<int> t2(t1);
	int n = 0;
	while (n < 96) {
		int j = rand();
		if (t2.contains(j)) {
			t2.remove(j);
			n++;
		}
	}
	t1 = t2;

	std::cout << "t1's height=" << t1.treeHeight() << std::endl;
	std::cout << "t1 is { ";
	t1.printTree();
	std::cout << "}" << std::endl;

	return 1;
}
