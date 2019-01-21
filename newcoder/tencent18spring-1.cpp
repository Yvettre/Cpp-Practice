/***************************************************************
腾讯2018年春招技术岗位笔试题-1（共6道，120分钟）

小Q定义了一种数列称为翻转数列:
给定整数n和m, 满足n能被2m整除。对于一串连续递增整数数列1, 2, 3, 4..., 每隔m个符号翻转一次, 最初符号为'-';。
例如n = 8, m = 2, 数列就是: -1, -2, +3, +4, -5, -6, +7, +8.
而n = 4, m = 1, 数列就是: -1, +2, -3, + 4.
小Q现在希望你能帮他算算前n项和为多少。

输入包括两个整数n和m(2 <= n <= 10^9, 1 <= m), 并且满足n能被2m整除。

输入：
8 2
输出：
8
****************************************************************/
#include<iostream>
using namespace std;

long long reverse(int n, int m) {
	long long group = n / m;
	if (group % 2 == 0) {
		return (group / 2)*m*m;
	}
	else {
		long long tmp = -m*(n-m+1) - m*(m-1)/2;
		return (group - 1)*m*m / 2 + tmp;
	}
}

// 这种解法能得到正确答案，但是当n特别大的时候，会超时，无法通过题目给定的时间限制
long long reverse1(int n, int m) {
	long long res = 0;
	bool isNegtive = false;
	for (int i = 0; i < n; i++) {
		if (i%m == 0) isNegtive = !isNegtive;
		if (isNegtive) res = res - (i + 1);
		else if (!isNegtive) res = res + (i + 1);
	}
	return res;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		cout << reverse(n, m) << endl;
	}
  return 0;
}