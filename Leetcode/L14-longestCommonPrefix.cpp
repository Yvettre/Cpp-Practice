/***************************************************************
Leetcode-easy-14: My runtime is 4ms.

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".
All given inputs are in lowercase letters a-z.

URL: https://leetcode.com/problems/longest-common-prefix/
****************************************************************/
#pragma once
#include<vector>
#include<string>
using namespace std;

string longestCommonPrefix(vector<string>& strs) {
	if (strs.size() == 0) { return ""; }
	if (strs.size() == 1) { return strs[0]; }

	size_t commonLen = strs[0].size();
	for (auto s : strs) {
		commonLen = s.size() < commonLen ? s.size() : commonLen;
	}

	for (size_t i = 0; i < commonLen; ++i) {
		for (size_t j = 1; j < strs.size(); ++j) {
			if (strs[0][i] != strs[j][i]) {
				return strs[0].substr(0, i);
			}
		}
	}
	return strs[0].substr(0, commonLen);
}