/***************************************************************
Leetcode-medium-46: My runtime is 8ms.

Given a collection of distinct integers, return all possible permutations.

URL: https://leetcode.com/problems/permutations/
****************************************************************/

/*
其实algorithm这个库里有个函数能直接求全排列的，但用了就没意思啦，虽然以后要用肯定是调包。。
下面是实现的思路，其实就是递归
算法思路：
1. n个元素的全排列 = (n-1)个元素的全排列 + 剩下的那个元素作为前缀
2. 递归结束条件是：如果只有一个元素进行全排列，则说明已排完，输出数组
3. 不断将每个元素放在第一作为前缀，然后将其余元素继续全排列，直到满足递归结束条件，排完后需要还原数组
*/

#pragma once
#include<iostream>
#include<vector>
using namespace std;

void show(vector<vector<int>>& v) {
	for (auto vv : v) {
		for (auto val : vv) {
			cout << " " << val;
		}
		cout << endl;
	}
}

//交换数组两个元素的位置
void swap(vector<int>& nums, size_t a, size_t b) {
	int tmp = nums[a];
	nums[a] = nums[b];
	nums[b] = tmp;
}

void perm(vector<int>& nums, size_t left, size_t right, vector<vector<int>>& res) {
	if (left == right) {        //递归结束条件
		res.push_back(nums);
	}
	else {
		for (size_t j = left; j <= right; ++j) {
			swap(nums, j, left);  // 将需要排列的数组中的每一个元素都放到前面作为前缀
			perm(nums, left+1, right, res);   // 将剩下的元素进行全排列
			swap(nums, j, left);            // 排完之后把位置换回来
		}
	}
}

vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> res;
	if (nums.size() == 0) return res;

	perm(nums, 0, nums.size() - 1, res); // 对整个数组进行全排列

	return res;
}


/*
返回没有重复的全排列
1. 如果需要放到前缀位置的元素（当前前缀）和当前前缀相等，则不需要排
2. 如果需要放到前缀位置的元素之前没有与自己重复的元素，则需要排，否则不排
*/
bool chkUnique(vector<int> nums, size_t left, size_t j) {
  for (size_t k=left; k<j; ++k) {
    if (nums[k]==nums[j]) return false;
  }
  return true;
}

void permUnique(vector<int>& nums, size_t left, size_t right, vector<vector<int>>& res){
  if (left==right) {
    res.push_back(nums);
  }
  else {
    for (size_t j=left; j<=right; ++j){
      if ( (nums[j]!=nums[left] || j==left) && chkUnique(nums, left, j)){
        swap(nums[j], nums[left]);
        permUnique(nums, left+1, right, res);
        swap(nums[j], nums[left]);
      }
    }
  }
}