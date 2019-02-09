/*

 ******************547. Friend Circles****************
 Using union find.
 
 */


#define _CRT_SECURE_NO_WARNINGS = 1
#define TEST 0
#include<iostream>
#include<stdio.h>

#include<vector>

using namespace std;

const static int MAX = 1200;
short parent[MAX];
short rnk[MAX];
bool arr[MAX];

class Solution {

public:
	int count;

	void init(int size)
	{
		for (int i = 0; i < size; i++)
		{
			parent[i] = i;
			rnk[i] = 0;
			arr[i] = false;
		}
		count = 0;
	}

	int find_parent(int i)
	{
		while (parent[i] != i)
			i = parent[i];

		return i;
	}

	void make_union(int i, int j)
	{
		int pi = find_parent(i);
		int pj = find_parent(j);


		if (rnk[pi] >= rnk[pj])
		{
			rnk[pi]++;
			parent[pj] = pi;
		}
		else
		{
			rnk[pj]++;
			parent[pi] = pj;
		}
	}

	int count_circle(int size)
	{
		
		for (int i = 0; i < size; i++)
		{
			int x = find_parent(i);
			if (arr[x] == false)
			{

				arr[x] = true;
				count++;
			}
		}
		return count;
	}

	int findCircleNum(vector<vector<int>>& M) 
	{
		int size = M.size();
		init(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (M[i][j])
				{
					make_union(i, j);
				}
			}
		}

		count = count_circle(size);
		return count;
	}
};

#if TEST
int main()
{
	freopen("input.txt", "r", stdin);
	int N;
	scanf("%d", &N);
	int a;
	vector<vector<int>> input;
	for (int i = 0; i < N; i++)
	{
		vector < int> in;
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &a);
			in.push_back(a);
		}
		input.push_back(in);
	}
	Solution S;
	int ak= S.findCircleNum(input);
	printf("Count = %d\n", ak);
	return 0;
}
#endif