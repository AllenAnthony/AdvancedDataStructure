#include<iostream>
#include<string>
#include<iterator>
#include<vector>
using namespace std;

class node
{
public:
	bool element;
	node* right;
	node* left;
	node(bool element);
};

node::node(bool element=0)
{
	this->element = element;
	right = NULL;
	left = NULL;
}

bool Build(vector<string> code, int N);
bool Checkfull(node* T);
bool Checkoptimal(vector<string> code, vector<int> freq, int N);

bool Build(vector<string> code, int N)
{
	node* T = new node;
	node* current = NULL;
	int cou;
	string::iterator P;
	for (cou = 0; cou < N; cou++)
	{
		current = T;
		for (P = code[cou].begin(); P != code[cou].end(); P++)
		{
			if (*P == '0')
			{
				if (current->left == NULL)
				{
					current->left = new node;
				}
				current = current->left;
			}
			else if (*P == '1')
			{
				if (current->right == NULL)
				{
					current->right = new node(1);
				}
				current = current->right;
			}
			else
				cout << "input error !" << endl;

		}
	}

	bool res=Checkfull(T);
	return Checkfull(T);
}

bool Checkfull(node* T)
{
	if (!T)
		return 1;

	if ((T->left == NULL && T->right == NULL))
		return 1;
	else if (T->left != NULL && T->right != NULL)
	{
		return (Checkfull(T->left) && Checkfull(T->right));
	}
	else
		return 0;
}

bool Checkoptimal(vector<string> code, vector<int> freq, int N)
{
	int cou;
	int num;
	for (cou = 0; cou < N; cou++)
	{
		for (num = cou + 1; num < N; num++)
		{
			if (((freq[cou] > freq[num]) && (code[cou].length() > code[num].length())) || ((code[cou].length() < code[num].length()) && (freq[cou] < freq[num])))
				return 0;
		}
	}

	return 1;
}

int main()
{
	int N;
	char C;
	int cou;
	int num;
	int time;
	
	cin >> N;
	vector<int> freq(N);

	for (cou = 0; cou < N; cou++)
	{
		cin >> C >> freq[cou];
	}

	cin >> time;
	vector<vector <string> > code;
	code.resize(time, vector<string>(N));

	for (cou = 0; cou < time; cou++)
	{
		for (num = 0; num < N; num++)
		{
			cin >> C >> code[cou][num];
		}
	}
	
	for (cou = 0; cou < time; cou++)
	{
		if (Checkoptimal(code[cou], freq, N) && Build(code[cou], N) )
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}