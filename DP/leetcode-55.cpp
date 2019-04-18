/***************************************************************
leetcode-medium-55：Jump game

Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.

Input: [2,3,1,1,4]
Output: true

Input: [3,2,1,0,4]
Output: false

URL:https://leetcode.com/problems/jump-game/
****************************************************************/

/*
nums[i]: 2 3 1 1 4
      i: 0 1 2 3 4
nums[i]+i表示从第i个位置起跳能到达的最远位置
*/

#include<vector>
using namespace std;

bool canJump(vector<int>& nums) {  
    int lastPos = nums.size()-1;
    for (int i=nums.size()-1; i>=0; i--) {
        if (nums[i]+i>=lastPos) {
            lastPos = i;
        }
    }
    
    return lastPos==0;
}