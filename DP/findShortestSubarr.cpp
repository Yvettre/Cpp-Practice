/***************************************************************
2016年校招真题：最短排序

对于一个无序数组A，请设计一个算法，求出需要排序的最短子数组的长度。
给定一个整数数组A及它的大小n，请返回最短子数组的长度。

输入：
[1,5,3,4,2,6,7],7
输出：
4
****************************************************************/

/*
哎，我自己只想到了从左往右出发找到子数组的结尾，然后以为弄个res++就可以了，
结果是不行的，这样子数组的开头一般都是错的。。
别人的结果就是两次遍历，再从右往左出发找到子数组的开头，然后两者的差就是答案了。
*/

#include<vector>
using namespace std;

int findShortest(vector<int> A, int n) {
    if (n==0 || n==1) return 0;
    int left = n-1, right = 0;
    int cur_subarr_max = A[right];
    for (int i=1;i<n;i++){
        if (A[i]>=cur_subarr_max) cur_subarr_max = A[i];
        else right = i;
    }
    int cur_subarr_min = A[n-1];
    for (int i=n-2;i>=0;i--){
        if (A[i]<=cur_subarr_min) cur_subarr_min = A[i];
        else left = i;
    }
    if (right<left) return 0;
    else return right-left+1;
}