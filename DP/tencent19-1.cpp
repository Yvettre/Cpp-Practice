/***************************************************************
腾讯19年实习-后台综合卷：凑零钱问题

小Q现在手上有n种不同面值的硬币，每种面值的硬币有无限多个。
为了方便购物，小Q希望带尽量少的硬币，并且要能组合出1~m之间（包括1和m）的所有面值。

- 输入描述：
  第一行包含两个整数m，n（1<=n<=100,1<=m<=10^9），含义如题目描述。
  接下来的n行，每一行一个整数，第i+1行的整数表示第i种硬币的面值。
- 输出描述：
  输出一个整数，表示最少需要携带的硬币的数量。如果无解，则输出-1。

输入：
20 4
1
2
5
10
输出：
5
****************************************************************/

/*
笔试的时候由于粗心，把是否能整除的条件写反了。。导致只能通过10%样例。。
时间紧迫，没来得及发现问题已经到了交卷时间，交卷后两分钟，就发现问题了。。心碎=。=
所以没有办法验证这样的解法是否能够ac，但是我觉得应该是这样解的

首先容易想到的是，如果没有面值为1的硬币，那么肯定无解。
然后用动态规划的办法，dp[i]表示要组合1~i之间所有面值所需要的最少硬币数量，
那么n种面值的硬币用value数组存储，先进行排序，然后有：
dp[1]=1，当i大于1时，从value数组反向遍历，找到能凑面值i的最大面值硬币value[j]，然后分为两种情况：
1、当i不能被value[j]整除，那么先携带i/value[j]个面值为value[j]的硬币，此时已经有了面值为value[j]的硬币，
因此只需要携带能凑出1~value[j]-1的全部面值的硬币即可，所以dp[i] = dp[value[j] - 1] + i/value[j]
2、当i能够被value[j]整除，本来是可以直接带i/value[j]个面值为value[j]的硬币的，但是
这样的话1~value[j]-1的全部面值不能确保可以组合出来，因此应该先携带i/value[j]-1个面值为value[j]的硬币，
然后再携带能够凑出1~value[j]的全部面值的硬币即可，所以dp[i] = dp[value[j]] + i/value[j] -1
*/

#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

int main() {
	int m, n;
	while (cin >> m >> n) {
		vector<int> value(n, 0);
		vector<int> dp(m + 1, 0);
		for (int i = 0; i<n; i++) cin >> value[i];

		sort(value.begin(), value.end());
		if (value[0] != 1) {
			cout << -1 << endl;
		}
		else {
			dp[1] = 1;
			bool check = false;
			for (int i = 2; i <= m; i++) {
				check = false;
				for (int j = n - 1; j >= 0 && !check; j--) {
					if (i > value[j]) {
						check = true;
						if (i % value[j]) {
							dp[i] = dp[value[j] - 1] + i / value[j];
						}
						else {
							dp[i] = dp[value[j]] + i / value[j] - 1;
						}
					}
				}
			}
			// for (int i = 0; i <= m; i++) cout << dp[i] << " ";
			// cout << endl;
			cout << dp[m] << endl;
		}
	}
	return 0;
}