/***************************************************************
拼多多2018年校招：最大乘积

给定一个无序数组，包含正数、负数和0，要求从中找出3个数的乘积，使得乘积最大
要求时间复杂度：O(n)，空间复杂度：O(1)

- 输入描述：
    无序整数数组A[n]
- 输出描述：
    满足条件的最大乘积

示例：
- 输入：
4
3 4 1 2
- 输出：
24
****************************************************************/

/*
记录这道题的原因是INT_MAX和INT_MIN的使用：
在本地的vs2017社区版中不包含<limits.h>这个头文件是可以通过便宜并成功执行的
但在牛客网上不能，要包含这个头文件
*/

#include<iostream>
#include<limits.h>
using namespace std;

int main() {
	long long max1=INT_MIN, max2=INT_MIN, max3=INT_MIN, min1=INT_MAX, min2=INT_MAX;
	int n;
	int x;
	while (cin >> n) {
		for (size_t i = 0; i<n; i++) {
			cin >> x;
			if (x > max1) {
				max3 = max2;
				max2 = max1;
				max1 = x;
			}
			else if (x > max2) {
				max3 = max2;
				max2 = x;
			}
			else if (x > max3) {
				max3 = x;
			}
			if (x < min1) {
				min2 = min1;
				min1 = x;
			}
			else if (x < min2) {
				min2 = x;
			}
		}
		long long res = min1*min2*max1 > max1*max2*max3 ? min1*min2*max1 : max1*max2*max3;
		cout << res << endl;
	}
	return 0;
}