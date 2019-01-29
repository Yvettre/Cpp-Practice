/***************************************************************
拼多多2018年校招：迷宫寻路

假设一个探险家被困在了地底的迷宫之中，要从当前位置开始找到一条通往迷宫出口的路径。
迷宫可以用一个二维矩阵组成，有的部分是墙，有的部分是路。
迷宫之中有的路上还有门，每扇门都在迷宫的某个地方有与之匹配的钥匙，只有先拿到钥匙才能打开门。
请设计一个算法，帮助探险家找到脱困的最短路径。

如前所述，迷宫是通过一个二维矩阵表示的，每个元素的值的含义如下：
0-墙，1-路，2-探险家的起始位置，3-迷宫的出口，大写字母-门，小写字母-对应大写字母所代表的门的钥匙

- 输入描述：
    迷宫的地图，用二维矩阵表示。第一行是表示矩阵的行数和列数M和N
    后面的M行是矩阵的数据，每一行对应与矩阵的一行（中间没有空格）。
    M和N都不超过100, 门不超过10扇。
- 输出描述：
    路径的长度，是一个整数
****************************************************************/

/*
我自己写的只能通过30%的case，实在是渣。。
下面这个思路其实是参考了讨论里的最前面的答案的
（我自己想破头都想不出来能通过所有用例的剪枝的办法=。=）

这个思路很巧妙：
isVisited[i][j][k]意义是横坐标为i、纵坐标为j、钥匙状态为k的点是否被访问过
钥匙的状态用二进制数表示，最多10把钥匙，也就是1024
比如现在有第二把钥匙和第四把钥匙，那么钥匙状态就是0000001010，也就是整数10
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int, int>> next_dif = { {1,0},{0,1},{0,-1},{-1,0} };  // 下右左上

int lookForPath(vector<vector<char>>& mp, int& M, int& N) {
	queue<vector<int>> q;
	vector<vector<vector<bool>>> isVisited(M, vector<vector<bool>>(N, vector<bool>(1024, false)));

	// 找到起点
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (mp[i][j] == '2') {
				// {x, y, key, cur_step}
				q.push({ i,j,0,0 });
				isVisited[i][j][0] = true;
				i = M;
				j = N;
			}
		}
	}

	while (!q.empty()) {
		//取出最先加入到队列的坐标
		vector<int> node = q.front();
		q.pop();

		// 判断当前点是否是终点
		if (mp[node[0]][node[1]] == '3') {
			// 使用广搜首次找到终点的路径必定是步数最少的路径
			return node[3];
		}

		for (size_t i = 0; i < 4; i++) {
			int next_x = node[0] + next_dif[i].first;
			int next_y = node[1] + next_dif[i].second;
			if (next_x >= M || next_x<0 || next_y>=N || next_y < 0) continue;

			char next_val = mp[next_x][next_y];

			// 如果是墙，路径无效
			if (next_val == '0') continue;

			int cur_key = node[2];
			// 如果是钥匙，更新钥匙中间变量
			if (next_val >= 'a' && next_val <= 'z') cur_key = cur_key | (1 << (next_val - 'a'));
			// 如果是门并且当前没有对应的钥匙，路径无效
			if (next_val >= 'A' && next_val <= 'Z' && (cur_key&(1 << (next_val - 'A'))) == 0) continue;
			// 如果携带已拥有的钥匙且并未访问过即将访问的这个点
			if (!isVisited[next_x][next_y][cur_key]) {
				isVisited[next_x][next_y][cur_key] = true;
				q.push({ next_x, next_y, cur_key, node[3] + 1 });
			}
		}
	}
	return 0;
}

int main() {
	int M, N;
	while (cin >> M >> N) {
		vector<vector<char>> mp(M, vector<char>(N));
		for (int i = 0; i<M; i++) {
			for (int j = 0; j<N; j++) {
				cin >> mp[i][j];
			}
		}
		cout << lookForPath(mp, M, N) << endl;
	}
	return 0;
}