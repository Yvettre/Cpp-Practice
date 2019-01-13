/***************************************************************
Leetcode-medium-12: My runtime is 52ms.

Given an integer, convert it to a roman numeral.
Input is guaranteed to be within the range from 1 to 3999.

URL: https://leetcode.com/problems/integer-to-roman/
****************************************************************/
#pragma once
#include<vector>
#include<string>
using namespace std;

const vector<string> pattern = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
const vector<int> decimal= { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };

string intToRoman(int num) {
	string result = "";
	int tmp = 0;
	for (size_t i = 0; i < decimal.size(); ++i) {
		tmp = num / decimal[i];
		if (tmp != 0) { 
			while (tmp > 0) {
				result = result + pattern[i];
				tmp--;
			}		
		}
		num = num % decimal[i];
	}
	return result;
}