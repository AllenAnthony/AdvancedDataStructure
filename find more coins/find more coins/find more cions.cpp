#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;


bool compare(const int& A, const int& B)
{
	return A>B;
}
//sort(&S[1], &S[n + 1], compare);
int R[10000][100];			//R[n][m]表示 前n个数中 得出的 最接近m 的值
bool used[10000][100];		//used[n][m]表示在前n个数中得出最接近m的值时 是否用到c[n]

int result(int n, int m,int* S)//f[n][m]表示 前n个数中 得出的 最接近m 的值
{
	int i, j;
	int sub;

	memset(R, 0, sizeof(int)*10000*100);
	memset(used, false, sizeof(bool)*10000*100);

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)//F(N, M) = max{ F(N–1, M), F(N–1, M–c(N)) + c(N) }
		{
			if ((j - S[i]) >= 0)
				sub = R[i - 1][j - S[i]] + S[i];
			else
				sub = 0;
			if (R[i - 1][j] > sub)
			{
				R[i][j] = R[i - 1][j];
			}
			else
			{
				R[i][j] = sub;
				used[i][j] = true;		//用到c[i]了 设has[i][j]为true
			}
		}
	}
	return R[n][m];
}



int main()
{
	int n, m;
	int* S;
	while (1)
	{
		cin >> n >> m;
		S = new int[n + 1];
		memset(S, 0, sizeof(int)*(n + 1));

		int i;
		for (i = 0; i < n; i++)
		{
			cin >> S[i + 1];
		}
		sort(&S[1], &S[n + 1], compare);		//从大到小排序

		int res = result(n, m, S);
		if (res == m)					//有解
		{
			vector<int> v;
			while (m)
			{
				while (!used[n][m])
					n--;
				v.push_back(S[n]);
				m = m - S[n];
				n--;
			}
			for (i = 0; i < v.size() - 1; i++)
				cout << v[i] << ' ';
			cout << v[i] << endl;
		}
		else						//无解
			cout << "No Solution" << endl;

		delete[]S;
	}
}