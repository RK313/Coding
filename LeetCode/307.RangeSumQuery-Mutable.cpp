#include<iostream>
#include<vector>

using namespace std;

class Tree_Node
{

public:
	int start, end, sum;
	Tree_Node *left;
	Tree_Node *right;
	Tree_Node(int s, int e, int sm)
	{
		start = s; end = e; sum = sm;
		left = right = nullptr;
	}
};


Tree_Node* build(int start, int end, vector<int> &nums)
{
	if (start > end) return nullptr;

	Tree_Node* r = new Tree_Node(start, end, nums[start]);
	if (start == end) return r;
	int mid = start + (end - start) / 2;

	r->left = build(start, mid, nums);
	r->right = build(mid + 1, end, nums);
	r->sum = r->left->sum + r->right->sum;
	return r;
}

void update_tree(Tree_Node* r, int idx, int val)
{
	if (!r) return;

	if (r->start == idx && r->end == idx)
	{
		r->sum = val;
		return;
	}

	int mid = r->start + (r->end - r->start) / 2;
	if (idx > mid)
		update_tree(r->right, idx, val);
	else// if(idx > mid)
		update_tree(r->left, idx, val);

	r->sum = r->left->sum + r->right->sum;

}

int get_sum(Tree_Node* r, int qs, int qe)
{
	if (!r) return 0;
	if (qs > r->end || qe < r->start) return 0;

	if (qs <= r->start && qe >= r->end) return r->sum;


	int mid = r->start + (r->end - r->start) / 2;
	if (qs > mid)
		return get_sum(r->right, qs, qe);
	if (qe <= mid)
		return get_sum(r->left, qs, qe);

	return get_sum(r->left, qs, qe) + get_sum(r->right, qs, qe);

}

//class NumArray {
//	Tree_Node *root;

//public:

Tree_Node *root;
void NumArray(vector<int> nums)
	{
		int min = INT_MAX; int max = INT_MIN;
		for (int i = 0; i < nums.size(); i++)
		{
			if (min > nums[i]) min = nums[i];
			if (max < nums[i]) max = nums[i];
		}

		root = build(0, nums.size() - 1, nums);
	}

	void update(int i, int val)
	{
		update_tree(root, i, val);
	}

	int sumRange(int i, int j)
	{
		int s = get_sum(root, i, j);
		return s;
	}
//};

/**
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* obj.update(i,val);
* int param_2 = obj.sumRange(i,j);
*/