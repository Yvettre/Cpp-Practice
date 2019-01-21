/***************************************************************
腾讯2018年春招技术岗位笔试题-2（共6道，120分钟）

牛牛和羊羊正在玩一个纸牌游戏。这个游戏一共有n张纸牌, 第i张纸牌上写着数字ai。
牛牛和羊羊轮流抽牌, 牛牛先抽, 每次抽牌他们可以从纸牌堆中任意选择一张抽出, 直到纸牌被抽完。
他们的得分等于他们抽到的纸牌数字总和。
现在假设牛牛和羊羊都采用最优策略, 请你计算出游戏结束后牛牛得分减去羊羊得分等于多少。

输入包括两行。
第一行包括一个正整数n(1 <= n <= 10^5),表示纸牌的数量。
第二行包括n个正整数ai(1 <= ai <= 10^9),表示每张纸牌上的数字。

输入：
3
2 7 4
输出：
5
****************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long pokeGame(vector<int>& poke, int n) {
	sort(poke.begin(), poke.end(),
			[](const int& a, int b)
			{ return a > b; });

	if (n % 2 != 0) {
		poke.emplace_back(0);
		n++;
	}

	long long res = 0;
	for (size_t i = 0; i < n; i++) {
		res = res + poke[i] - poke[i+1];
		i++;
	}

	return res;
}

int main() {
	int n;
	while (cin >> n) {
		vector<int> poke(n);
		for (size_t i = 0; i < n; i++) {
			cin >> poke[i];
		}
		cout << pokeGame(poke, n) << endl;
	}
}