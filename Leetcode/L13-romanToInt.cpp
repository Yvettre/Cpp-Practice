/***************************************************************
Leetcode-easy-13: My runtime is 52ms.

Given a roman numeral, convert it to an integer.
Input is guaranteed to be within the range from 1 to 3999.

URL: https://leetcode.com/problems/roman-to-integer/
****************************************************************/
#pragma once
#include<vector>
#include<string>
#include<map>
using namespace std;

const vector<string> pattern = { "IV","IX","XL","XC","CD","CM" };
const int arr[] = { 2,2,20,20,200,200 };
map<char, int> DICT = { { 'I', 1 },{ 'V', 5 },{ 'X', 10 },{ 'L', 50 },
												{ 'C', 100 },{ 'D', 500 },{ 'M', 1000 } };

int romanToInt(string s) {
	int diff = 0;
	for (size_t i = 0; i < pattern.size(); ++i) {
		string::size_type pos = 0;
		while ((pos = s.find(pattern[i], pos)) != string::npos) {
			diff = diff + arr[i];
			pos = pos + 2;
		}
	}

	int result = 0;
	for (auto c : s) {
		result += DICT[c];
	}
	return result - diff;
}