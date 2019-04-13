/***************************************************************
阿里2019年实习笔试题1：灭灯游戏-3*3矩阵
 
初始局面由键盘输入，“U”表示灯亮，“D”表示灯灭，求给定初始局面，是否存在解使得灯全灭，
若有解，输出最少操作数，若无解，输出-1
灭灯游戏规则：当按下一个灯，不仅该灯本身的状态翻转，其上下左右四个灯的状态也翻转，忽略超出边界的灯

- 输入样例：
UUD
DDU
DDU
- 输出：
2
- 解释：先按第一行第二个灯，然后按第二行第三个灯，唯一解（与顺序无关）
****************************************************************/

/*
结合网友的力量，终于理解了。。在此记录几个链接：
https://blog.csdn.net/MHL_1208980380/article/details/54618002
http://mathworld.wolfram.com/LightsOutPuzzle.html
https://blog.csdn.net/MHL_1208980380/article/details/54889018

本cpp代码主要参考上面第一个链接，有几个要点：
1、游戏的解，只与被按下的灯的位置有关，与被按下的灯的顺序无关
2、每一个灯被按下奇数次的效果与被按下一次的效果是一样的，同理，被按下偶数次的效果与没有被按的效果是一样的，所以最优解一定是要么被按一次，要么没有被按
3、当第一行的灯的操作方案确定时，从第二行开始，要使得前一行的全部灯都要灭掉，每一行的操作是确定的，因此可以得到暴力枚举第一行操作的解法
    怎么理解呢？假设按下位置[a,b]的灯，那么只会影响自身、上下左右共五个灯，其中影响前一行的灯只有[a-1,b]
    举个例子，假设现在的灯的状态如下：
    110
    001
    001
    如果第一行不按，那么第二行的操作要使第一行全灭，则必须按下第二行第一个灯和第二行第二个灯，而第二行第三个灯不能按，即操作表示为110
4、如果用0表示灯灭，用1表示灯亮，用0表示灯没有被按，用1表示灯被按下，则可以用位运算的异或来对灯状态翻转进行模拟，例如：
    灯的旧状态  灯的操作  灯的新状态
    0            0         0
    0            1         1
    1            0         1
    1            1         0
5、本cpp代码的时间复杂度为O(2^n)，另外还有求解线性方程组的方法，我理解了原理，但没有写代码。。参考上面第三个链接吧~
*/


#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

// mat：灯的初始局面，每一行的灯的状态用二进制表示，0表示灭，1表示亮，例如样例，mat={6,1,1}
// press：灯的操作，每一行的灯的操作用二进制表示，0表示不按，1表示按
// guide=2^n：表示第一行的灯的操作的组合数
// lights：在确定的第一行操作下的灯局面
// permutation：第一行的操作，0表示不按，1表示按

int main() {
	int n = 3;
	int guide = 1 << n; //第一行灯操作的组合数

	vector<int> mat(n+2); // n+2主要为了方便写循环，不会溢出
	int check = 0;
	int tmp_input;
	char char_input;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> char_input;
			if (char_input == 'U') tmp_input = 1;
			else tmp_input = 0;
			mat[i] <<= 1;
			mat[i] += tmp_input;
		}
		check |= mat[i];
	}
	if (!check) { // 已全灭
		cout << 0 << endl;
		return 0;
	}

	int permutation = 0;
	vector<int> lights(n + 2, 0); // lights存放第一行操作确定为permutation的局面
	vector<int> press(n + 2, 0);
	int solution_cnt = 0; // 解的个数
	int min_steps = INT_MAX;

	for (permutation = 0; permutation < guide; permutation++) { // 暴力枚举第一行灯的操作
		lights[0] = permutation; // 第一行的灯操作等于第0行的灯的状态，便于后续的循环

		for (int i = 1; i <= n; i++) { // 重新恢复初始化局面
			press[i] = 0;
			lights[i] = mat[i];
		}

		for (int i = 1; i <= n; i++) {
			press[i] = lights[i - 1]; // 第i行的操作等于第i-1行的灯的状态（press[i]操作后，第i-1行灯全灭）
			lights[i + 1] ^= press[i]; // 第i+1行灯的新状态等于第i+1行灯的旧状态异或第i行灯的操作

			lights[i] ^= press[i]; // 对第i行本身，先翻转被操作的灯本身的状态

			int left = press[i] << 1; // 然后翻转被操作的灯左边的灯的状态
			if (left >= guide) left ^= guide; // 若左移超出边界n，将超出边界的bit置0
			lights[i] ^= left;

			int right = press[i] >> 1; // 然后翻转被操作的灯右边的灯的状态
			lights[i] ^= right;
		}

		// 操作完最后一行的灯（i=n），检查最后一行
		if (lights[n] == 0) {
			solution_cnt++;
			int step_cnt = 0; // 当前解的操作的次数
			for (int i = 1; i <= n; i++) {
				int tmp = press[i];
				while (tmp != 0) {
					tmp = tmp & (tmp - 1);
					step_cnt++;
				}
			}
			min_steps = min_steps < step_cnt ? min_steps : step_cnt;
		}
	}

	if (solution_cnt == 0) cout << -1 << endl;
	else cout << min_steps << endl;

	return 0;
}