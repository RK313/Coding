/*
LeetCode Questions : 315. Count of Smaller Numbers After Self

Solution: Using segment tree
Implementation 2: Using dynamic tree
- First build dummy segment tree with min and max value of given input.
- Run loop in reverse order [i = size of vector]
[I]   -  Get the next smaller number of ith number [ first time in loop, it will return zero ]
[II]  -  Update the ith number in segment tree.
	     (i) - If current node's start and end are equal to the key, then update the count of   
				current node.
         (ii) - if val <= mid  ==> call update with root->left
		 (iii) - if val > mid  ==> call update with root->right
		 (iv) - After updating count of left and right subtree, update the count of current node. 
[III] -  back to step [I]. i--
*/


#include<iostream>
#include<vector>
#include"Header.h"

class Tree_Node
{
public:
	int count;
	int start;
	int end;
	Tree_Node *left;
	Tree_Node * right;
};

Tree_Node* newTreeNode (int l, int h)
{
	Tree_Node *new_node = new Tree_Node();
	new_node->start = l;
	new_node->end = h;
	new_node->left = nullptr;
	new_node->right = nullptr;
	return new_node;
}

Tree_Node* build(int start, int end);
void update(Tree_Node* r, int val);
int query(Tree_Node* r, int start, int end);


Tree_Node* build(int start, int end)
{
	if (start > end) return nullptr;
	Tree_Node* root = newTreeNode(start, end);
	if (start == end) return root;
	int mid = start + (end - start) / 2;
	root->left = build(start, mid);
	root->right = build(mid + 1, end);
	return root;
}

int query(Tree_Node* r, int qs, int qe)
{
	if (r == nullptr) return 0;
	if (qs > r->end || qe < r->start) return 0;

	if (qs <= r->start && qe >= r->end) return r->count;

	int mid = r->start + (r->end - r->start) / 2;
	if (qs > mid)
		return query(r->right, qs, qe);
	else if (qe <= mid)
		return query(r->left, qs, qe);


	return query(r->left, qs, qe) + query(r->right, qs, qe);
}

void update(Tree_Node* r, int val)
{
	if (r == nullptr) return;

	if (r->start == val && r->end == val)
	{
		r->count++;
		return;
	}

	int mid = r->start + (r->end - r->start) / 2;
	if (val <= mid)
		update(r->left, val);
	else if (val > mid)
		update(r->right, val);

	r->count = r->left->count + r->right->count;

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
	
	Tree_Node* root = build(min, max);

	int size = nums.size();
	std::vector<int> res(size, 0);
	for (int i = nums.size() - 1; i >= 0; --i)
	{
		int l = query(root, min, nums[i] - 1);
		res[i] = l;
		update(root, nums[i]);
	}
	return res;
}
};


