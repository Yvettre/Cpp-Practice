/***************************************************************
Leetcode-easy-9

Determine whether an integer is a palindrome. 
An integer is a palindrome when it reads the same backward as forward.

URL: https://leetcode.com/problems/palindrome-number/
****************************************************************/
#include<vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) { return false; }
        if (x == 0) { return true; }
        vector<int> tmp;
        while (x != 0) {
            tmp.emplace_back(x % 10);
            x = x / 10;
        }
        if (tmp.size() == size_t(1)) { return true; }
        
        size_t i = 0; 
        size_t j = tmp.size() - size_t(1);
        while (i <= j) {
            if (tmp[i++] != tmp[j--]) {
                return false;
            }
        }
        return true;
    }
};