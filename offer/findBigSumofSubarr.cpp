/***************************************************************
剑指offer：连续子数组的最大和

一个整型数组，数组中有正数也有负数。数组中一个或连续多个正数组成一个子数组。
求所有子数组的和的最大值，要求时间复杂度O(n)。
****************************************************************/
#include<iostream>
#include<vector>
using namespace std;

int FindGreatestSumOfSubArray(vector<int> array) {
    //默认数组不为空
    if (array.size()==1) return array[0];

    int sum = array[0];
    int res = sum;
    for (size_t i=1;i<array.size();i++){
        if (sum<0) {
            // 如果当前数字前面的子数组的和小于0，那么加上当前值一定会比当前值小
            // 因此最大和肯定不包括前面已经求和的数字，因此重新求和
            sum = array[i];
        }
        else {
            sum = sum + array[i];
        }
        res = res>sum?res:sum;  // 记录最大和
    }
    return res;
}