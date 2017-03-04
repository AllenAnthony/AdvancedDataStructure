#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class node
{
public:
	unsigned int newwidth;
	unsigned int newheight;
	node* next;
	node(int, int, node*);
};

node* initial();
void insert(node*head,node M);

node::node(int newwidth=0, int newheight=0, node* next=NULL)
{
	this->newheight = newheight;
	this->newwidth = newwidth;
	this->next = next;
}
bool compare(const pair<int, int>& A, const pair<int, int>& B)
{
	return A.second>B.second;
}

int Packing(pair<int, int> REC[], int N, int maxheight);

int main()
{
	int cou;
	int maxwidth;
	int N;
	cout << "please input the max width: ";
	cin >> maxwidth;
	cout << endl << "please input the number of rectangles:";
	cin >> N;
	pair<int, int>* REC = new pair<int, int>[N];//first是宽度，之后视为新高度，second是高度，之后视为新宽度
	cout << endl << "please input the width and the height of the " << N << "rectangles:" << endl;
	for (cou = 0; cou < N; cou++)
	{
		cin >> REC[cou].first;
		cin >> REC[cou].second;
		if (REC[cou].first>maxwidth)
		{
			cout << "the width is beyond the max width" << endl;
			return 0;
		}
	}

	sort(&REC[0], &REC[N-1], compare);//把新宽度从大到小排序

	cout << "the min height for the packing is: " << Packing( REC, N,maxwidth)<<endl;
}

int Packing(pair<int, int> REC[], int N,int maxheight)
{
	int height=0;
	int cou;
	node M;
	node* head = initial();
	node* suv;
	node* pre;
	pair<int, int> rec;
	for (cou = 0; cou < N; cou++)
	{
		rec = REC[cou];
		suv = head->next;
		pre = head;
		while (suv != NULL && (suv->newwidth < rec.second || maxheight < rec.first))
		{
			pre = suv;
			suv = suv->next;
		}

		if (!suv)
		{
			height += rec.second;
			insert(head, node(rec.second, maxheight - rec.first,NULL));
		}
		else
		{
			insert(head, node(rec.second,suv->newheight-rec.first,NULL));
			insert(head, node(suv->newwidth-rec.second, suv->newheight, NULL));
			pre->next = suv->next;
			delete suv;
		}
	}

	return height;
}


node* initial()
{
	node M;
	M.newheight = -1;
	M.newwidth = -1;
	M.next = NULL;
	node* head = &M;
	return head;
}
void insert(node*head, node M)
{
	node* suv=head->next;
	node* pre;
	if (M.newheight == 0 || M.newwidth == 0)
		return;

	while (suv != NULL && suv->newwidth < M.newwidth)
	{
		pre = suv;
		suv = suv->next;
	}
	if (suv)
	{
		pre->next = &M;
		M.next = suv;
	}
	else
		pre->next = &M;

}