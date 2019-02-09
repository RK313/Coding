/*
	LeetCode Questions : 315. Count of Smaller Numbers After Self

	Solution: Using segment tree
	Implementation : Using array
					 - First build dummy segment tree with min and max value of given input.
					 - Run loop in reverse order [i = size of vector]
						[I]   -  Get the next smaller number of ith number [ first time in loop, it will return zero ]
						[II]  -  Update the ith number in segment tree.
						[III] -  back to step [I]. i--
*/



#include<iostream>
#include<vector>
#include"Header.h"

const int MAX = 100000;

struct Tree_Node
{
	int count;
};

Tree_Node seg_tree[MAX];

void build_seg_tree(int start, int end, int idx)
{
	if (start == end)
	{
		seg_tree[idx].count = 0;
		return;
	}

	int mid = start + (end - start) / 2;
	build_seg_tree(start, mid, 2 * idx + 1);
	build_seg_tree(mid + 1, end, 2 * idx + 2);
	seg_tree[idx].count = 0;
}

void update(int start, int end, int qs, int qe, int idx)
{

	if (qs > end || qe < start)
		return;

	if (start == end)
	{
		seg_tree[idx].count++;
		return;
	}

	int mid = start + (end - start) / 2;
	update(start, mid, qs, qe, 2 * idx + 1);
	update(mid + 1, end, qs, qe, 2 * idx + 2);

	seg_tree[idx].count = seg_tree[2 * idx + 1].count + seg_tree[2 * idx + 2].count;
}

int query(int start, int end, int qs, int qe, int idx)
{
	if (qs > end || qe < start)
		return 0;

	if (qs <= start && qe >= end)
		return seg_tree[idx].count;
	
	int mid = start + (end - start) / 2;
	
	return query(start, mid, qs, qe, 2 * idx + 1)  + query(mid + 1, end, qs, qe, 2 * idx + 2);
}

class Solution {
public:
	std::vector<int> Solution::countSmaller(std::vector<int>& nums)
	{
		int min = INT_MAX; int max = INT_MIN;
		
		for (int i = 0; i < nums.size(); i++)
		{
			if (min > nums[i]) 	min = nums[i];
			if (max < nums[i]) 	max = nums[i];
		}
		int tmp = (-1 * min) + 1;
		if (min < 0)
		{
			min += tmp;
			max += tmp;
			for (int i = 0; i < nums.size(); i++)
				nums[i] += tmp;
		}
		build_seg_tree(min, max, 0);
	
		int size = nums.size();
		std::vector<int> res(size);
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			int l = query(min, max, 0, nums[i] - 1, 0);
			res[i] = l;
			update(min, max, nums[i], nums[i], 0);
		}
		return res;
	}
};
