/***************************************************************
剑指offer：和为S的两个数字

输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S。
如果有多对数字的和等于S，输出两个数的乘积最小的。
对应每个测试案例，输出两个数，小的先输出。

拓展A：非排序数组中找出两个数字和为sum？（leetcode1）
拓展B：非排序数组中找出三个数字和为0？（leetcode15）
****************************************************************/
#include<iostream>
#include<vector>
#include<limits.h>
#include<map>
#include<algorithm>
using namespace std;

/* 排序数组中找两个数字，找不到返回空的vector */
vector<int> Find2NumsWithSum(vector<int>& array, int sum) {
    if (array.size() <= 1) return vector<int>();
    
    vector<int> res(2,-1);
    int left = 0, right = (int) array.size()-1;
    long long multi = LLONG_MAX;
    while(left<right){
        if (array[left] + array[right] == sum){
            long long tmp = (long long) array[left] * array[right];
            if (tmp < multi){
                multi = tmp;
                res[0] = array[left];
                res[1] = array[right];
            }
            left++;
            right--;
        }
        else if (array[left] + array[right] > sum){
            right--;
        }
        else left++;
    }

    if (res[0]==-1 && res[1]==-1) return vector<int>();
    else return res;
}


/* 拓展A：数组非排序，只要找到一对即可 */
// 不能排序，因为需要返回的是下标，排序后的可能更复杂
vector<int> twoSum(vector<int>& nums, int target) {
    // 1. 暴力求解：时间复杂度O(n^2)，空间复杂度O(1)
    // 假设一定有一个解

    int i = 0, j = 0;
    vector<int> result;
    for (i = 0; i != nums.size(); i++)
    {
        for (j = i+1; j != nums.size(); j++)
        {
            if (nums[j] == target - nums[i])
            {
                result.push_back(i);
                result.push_back(j);
            }
        }
    }
    return result;
}

vector<int> twoSum(vector<int>& nums, int target) {
    // 2. 借助一个hashMap：时间复杂度O(n)，空间复杂度O(n)

    if(nums.size()<=1) return vector<int>();
    
    map<int, size_t> value_index;
    vector<int> res(2, -1);
    for (size_t i=0;i<nums.size();i++){
        int tmp = target - nums[i];
        if (value_index.find(tmp) != value_index.end()){
            res[0] = value_index[tmp];
            res[1] = i;
            return res;
        }
        else {
            value_index.insert(pair<int, size_t>(nums[i], i));
        }
    }
    if (res[0]==-1 && res[1]==-1) return vector<int>();
    else return res;
}


/* 拓展B：非排序数组找出三个数字使得它们的和等于0，找出所有解 */
// 可以排序，因为需要返回的是数字，而不是下标
// 但是数组中有可能出现负数和重复的数字，需要避开重复的数字
vector<vector<int>> threeSum(vector<int>& nums) {
    if (nums.size()<=2) return vector<vector<int>>();
    
    sort(nums.begin(), nums.end());
    vector<vector<int>> threeRes;
    for (size_t i=0;i<nums.size()-2;i++){
        if(i > 0 && nums[i-1] == nums[i]) continue;
        size_t left = i+1;
        size_t right = nums.size()-1;
        while(left<right){
            if (nums[i]+nums[left]+nums[right]==0){
                threeRes.push_back({ nums[i], nums[left], nums[right] });
                left++;
                right--;
                while(left<right && nums[left]==nums[left-1]) left++;
                while(left<right && nums[right]==nums[right+1]) right--;
            }
            else if (nums[i]+nums[left]+nums[right]>0) right--;
            else left++;
        }
    }
    return threeRes;
}