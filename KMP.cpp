/***************************************************************
实现KMP算法，求B串在A串中首次出现的位置，若没有出现则返回-1

怎么说呢，其实A.find(B)就可以搞定的了。。我还是想写一下=。=
一开始呢，我是用python实现的，代码在KMP.py中
然后呢，觉得想看看用C++怎么实现求部分匹配表，就按照python实现的思路写了一遍。。
确实踩了不少坑。。还是不熟练呀。。当作教训吧
当然也有很多看起来很简单的方法实现的，我实在折腾不动了，还是做个安静的调包侠吧=。=
****************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

void showVector(const vector<string>& result) {
	for (size_t i = 0; i<result.size(); i++) {
		cout << " " << result[i];
	}
	cout << endl;
}

void showVector(const vector<int>& partList) {
	for (size_t i = 0; i<partList.size(); i++) {
		cout << " " << partList[i];
	}
	cout << endl;
}

void showSet(const set<string>& obj) {
	for (set<string>::iterator it = obj.begin(); it != obj.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;
}

void generatePartMatchList(const string& B, vector<int>& partList) {
	/*
	根据模式串B生成部分匹配表
	*/
	partList.push_back(0);

	set<string> prefix = {};
	for (size_t i = 1; i<B.size(); i++) {
		prefix.insert(B.substr(0, i));

		// 求真后缀的集合
		set<string> postfix = {};
		for (size_t j = 1; j <= i; j++) {
			postfix.insert(B.substr(0, i + 1).substr(j));
		}
		showSet(prefix);
		showSet(postfix);

		// 求交集
		vector<string> result(B.size() - 1);
		vector<string>::iterator retEndPos;
		retEndPos = set_intersection(prefix.begin(), prefix.end(), postfix.begin(), postfix.end(), result.begin());
		result.resize(retEndPos - result.begin());
		showVector(result);
		if (result.size() == 0) {
			partList.push_back(0);
		}
		else {
			partList.push_back(result.back().size());
		}
	}
}

int kmpMatch(const string& A, const string& B) {
	/*
	在主串A中找到模式串B首次出现的位置，若不匹配则返回-1
	*/
	if (A.size() < B.size()) {
		return -1;
	}

	vector<int> partList;
	generatePartMatchList(B, partList);
	showVector(partList);
	
	size_t curA = 0;  //A串当次匹配的起始指针
	size_t curB = 0;  //B串当次匹配的起始指针
	while (curA <= (A.size() - B.size())) {
		for (size_t i = curB; i<B.size(); i++) {
			if (A[curA + i] != B[i]) {
				// curA向后移动位数 = 已匹配的字符数-对应的部分匹配值
				if (i == 0) { curA++; curB = 0; }
				else {
					curA = curA + max(i - partList[i - 1], size_t(1));
					curB = partList[i - 1];
				}						
				break;
			}
			else {
				curB = 0;
			}
			if (i == B.size() - 1) {
				return curA;
			}
		}
	}
	return -1;
}

int main() {
	string A = "BBC ABCDAB ABCDABCDABDE";
	string B = "ABCDABD";

	int pos = kmpMatch(A, B);
	cout << pos << endl;

	// set<string> one;
	// one.insert("a");
	// one.insert("ab");
	// set<string> two;
	// two.insert("ba");
	// two.insert("a");

	// vector<string> result(one.size()+two.size());
	// vector<string>::iterator retEndPos;

	// retEndPos = set_intersection(one.begin(), one.end(), two.begin(), two.end(), result.begin());
	// result.resize(retEndPos - result.begin());

	// showVector(result);
}