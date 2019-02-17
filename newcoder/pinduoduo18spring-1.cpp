/***************************************************************
拼多多2018年校招：小熊吃糖

有n只小熊，他们有着各不相同的战斗力。
每次他们吃糖时，会按照战斗力来排，战斗力高的小熊拥有优先选择权。
前面的小熊吃饱了，后面的小熊才能吃。
每只小熊有一个饥饿值，每次进食的时候，小熊们会选择最大的能填饱自己当前饥饿值的那颗糖来吃，
可能吃完没饱会重复上述过程，但不会选择吃撑。
现在给出n只小熊的战斗力和饥饿值，并且给出m颗糖能填饱的饥饿值。
求所有小熊进食完之后，每只小熊剩余的饥饿值。

- 输入描述：
    第一行两个正整数n和m，分别表示小熊数量和糖的数量。（n <= 10, m <= 100）
    第二行m个正整数，每个表示着颗糖能填充的饥饿值。
    接下来的n行，每行2个正整数，分别代表每只小熊的战斗力和当前饥饿值。
    题目中所有输入的数值小于等于100。
- 输出描述：
    输出n行，每行一个整数，代表每只小熊剩余的饥饿值。

示例：
- 输入：
2 5
5 6 10 20 30
4 34
3 35
- 输出：
4
0
****************************************************************/

/*
一开始理解错题目了，以为是每只熊按照战斗力大小先都吃一颗糖，
然后再重新从战斗力最大的开始重复操作。（但居然都有80%的通过率。。样例选得好差=。=）
后来发现题目的意思是战斗力最高的先吃，能吃多少糖就吃多少，
吃到如果继续吃就会撑就停下来，轮到下一只熊吃。

很自然会想到先排序。。关键是：排序后得到了答案，输出却不是原来的熊的顺序，
所以就用了vector<类对象的指针>，然后备份一个未排序的，
操作完毕后按照备份的顺序逐个取出类对象的实例读取饥饿值即可。
好久没用C++写类了，有点生疏，记录一下=。=
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Bear {
public:
	int power;
	int hunger;

	Bear(int p, int h) { power = p; hunger = h; }
	~Bear() {}

	void setPower(int p) {
		this->power = p;
	}
	void setHunger(int h) {
		this->hunger = h;
	}
};

int main() {
	int bearN, candyM;
	while (cin >> bearN >> candyM) {
		vector<int> candy(candyM, 0);
        for (size_t i = 0; i<candyM; i++) cin >> candy[i];
        
		vector<Bear*> bear(bearN);
		for (size_t i = 0; i < bearN; i++) {
			int p,h;
			cin >> p >> h;
			Bear* bearTmp = new Bear(p, h);
			bear[i] = bearTmp;
		}

		vector<Bear*> bearBackup;
		for (size_t i = 0; i < bearN; i++) {
			bearBackup.push_back(bear[i]);
		}

		sort(candy.begin(), candy.end(),
			[](int a, int b)
		{ return a>b; });
		sort(bear.begin(), bear.end(),
			[](const Bear* a, const Bear* b)
		{ return (*a).power>(*b).power; });

		for (size_t i = 0; i < bearN; i++) {
			for (size_t j = 0; j < candyM; j++) {
				if ((*bear[i]).hunger == 0) break;
				if (candy[j] <= (*bear[i]).hunger && candy[j] != 0) {
					(*bear[i]).setHunger((*bear[i]).hunger - candy[j]);
					candy[j] = 0;
				}
			}	
		}

		for (size_t i = 0; i<bearN; i++)cout << (*(bearBackup[i])).hunger << endl;
		//for (size_t i = 0; i<bearN; i++)cout << (*bear[i]).hunger << endl;

		for (size_t i = 0; i < bearN; i++)
			delete bear[i];
	}
}


/*********************以下记录的是我理解错题目的骚操作****************/
/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Bear {
public:
	int power;
	int hunger;
	bool needEat;

	Bear(int p, int h, bool b) { power = p; hunger = h; needEat = b; }
	~Bear() {}

	void setPower(int p) {
		this->power = p;
	}
	void setHunger(int h) {
		this->hunger = h;
	}
	void setNeedEat(bool b) {
		this->needEat = b;
	}
};

int main() {
	int bearN, candyM;
	while (cin >> bearN >> candyM) {
		vector<int> candy(candyM, 0);
		for (size_t i = 0; i<candyM; i++) cin >> candy[i];
		vector<Bear*> bear(bearN);
		for (size_t i = 0; i < bearN; i++) {
			int p,h;
			cin >> p >> h;
			Bear* bearTmp = new Bear(p, h, true);
			bear[i] = bearTmp;
		}

		vector<Bear*> bearBackup;
		for (size_t i = 0; i < bearN; i++) {
			bearBackup.push_back(bear[i]);
		}

		sort(candy.begin(), candy.end(),
			[](int a, int b)
		{ return a>b; });
		sort(bear.begin(), bear.end(),
			[](const Bear* a, const Bear* b)
		{ return (*a).power>(*b).power; });

		bool isEat = false;
		for (size_t i = 0; i<bearN;) {
			if ((*bear[i]).needEat) {
				for (auto j = candy.begin(); j != candy.end(); j++) {
					if ((*j) <= (*bear[i]).hunger) {
						(*bear[i]).setHunger((*bear[i]).hunger - (*j));
						if ((*bear[i]).hunger == 0) (*bear[i]).needEat = false;
						candy.erase(j);
						isEat = true;
						break;
					}
					if (j == candy.end() - 1 && !isEat) {
						(*bear[i]).needEat = false;
					}
				}
			}

			if (i == bearN - 1) {
				if (isEat) {
					i = 0;
					isEat = false;
				}
				else i = bearN;
			}
			else i++;
		}

		for (size_t i = 0; i<bearN; i++)cout << (*(bearBackup[i])).hunger << endl;
		// for (size_t i = 0; i<bearN; i++)cout << (*bear[i]).hunger << endl;

		for (size_t i = 0; i < bearN; i++)
			delete bear[i];
	}
}
*/