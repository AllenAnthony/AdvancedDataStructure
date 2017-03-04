#include<iostream>
#include<vector>
using namespace std;


int main()
{
	int C, M, L;//C是颜色总数
	int max = 0;
	int dai;
	int cou,suv,tmp;
	cin >> C;
	cin >> M;
	vector<int> FC(M);
	for (cou = 0; cou < M; cou++)
		cin >> FC[cou];

    cin >> L;
	vector<int> S(L);
	for (cou = 0; cou < L; cou++)
		cin >> S[cou];

	int**R = new int*[L];
	for (cou = 0; cou < L; cou++)
	{
		R[cou] = new int[M]();
	}

	for (cou = 0; cou < M; cou++)
	{
		if (S[0] == FC[cou])
		{
            R[0][cou] = 1;
			max = 1;
			
		}
	}

	for (cou = 1; cou < L; cou++)
	{
		for (suv = 0; suv < M; suv++)
		{
			R[cou][suv] = R[cou - 1][suv];
			dai = R[cou][suv];
			if (S[cou] == FC[suv])
			{
                for (tmp = 0; tmp <=suv; tmp++)
			       {
				       R[cou][suv] = R[cou][suv]>(R[cou - 1][tmp]+1) ? R[cou][suv] : (R[cou - 1][tmp]+1);
			       }
			}


			max = max > R[cou][suv] ? max : R[cou][suv];
		}
	}
	cout << max;

}