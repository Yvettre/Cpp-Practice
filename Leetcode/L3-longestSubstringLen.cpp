/***************************************************************
Leetcode-medium-3: My runtime is 32ms.

Given a string, find the length of the longest substring without repeating chars.

URL: https://leetcode.com/problems/longest-substring-without-repeating-characters/
****************************************************************/
#pragma once
#include<string>
#include<map>
#include<algorithm>
using namespace std;

int lengthOfLongestSubstring(string s) {
	map<char, int> dict;
	int res = 0;
	int left = -1;
	for (int i = 0; i < int(s.size()); ++i) {
		if (dict.find(s[i]) == dict.end()) {
			dict.insert({ s[i], -1 });
		}
		if (dict[s[i]] > left) {
			left = dict[s[i]];
		}
		dict[s[i]] = i;
		res = max(res, i - left);
	}
	return res;
}