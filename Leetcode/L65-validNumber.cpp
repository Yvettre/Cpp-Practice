/***************************************************************
Leetcode-hard-65: My runtime is 12ms, memory is 8.2MB.

Validate if a given string can be interpreted as a decimal number.
Some examples:
"0"           => true
" 0.1 "       => true
"abc"         => false
"1 a"         => false
"2e10"        => true
" -90e3   "   => true
" 1e"         => false
"e3"          => false
" 6e-1"       => true
" 99e2.5 "    => false
"53.5e93"     => true
" --6 "       => false
"-+3"         => false
"95a54e53"    => false

It is intended for the problem statement to be ambiguous.
You should gather all requirements up front before implementing one.
However, here is a list of characters that can be in a valid decimal number:
- Numbers 0-9
- Exponent - "e"
- Positive/negative sign - "+"/"-"
- Decimal point - "."
Of course, the context of these characters also matters in the input.

URL:https://leetcode.com/problems/valid-number/
****************************************************************/

/*
参考了剑指offer的面试题54的解法，增加了以下三点考虑：
1、字符串两端空格
2、小数点两边是否有数字
3、指数标志e/E后面是否有数字
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool scan_digits(string& s, int& idx) {
    int tmp_idx = idx;
    while (idx != s.size() && s[idx] >= '0' && s[idx] <= '9') {
        idx++;
    }
    if (tmp_idx == idx) return false;
    return true;
}

void scan_space(string& s, int& idx) {
    while (idx != s.size() && s[idx] == ' ') {
        idx++;
    }
}

bool is_exponential(string& s, int& idx) {
    if (s[idx] != 'e' && s[idx] != 'E') return false;

    idx++;
    if (s[idx] == '+' || s[idx] == '-') idx++;

    if (idx == s.size()) return false;

    bool have_digits = scan_digits(s, idx);
    if (!have_digits) return false;

    scan_space(s, idx);
    return idx == s.size() ? true : false;
}

bool isNumber(string s) {
    if (s.size() == 0) return false;

    int idx = 0;
    scan_space(s, idx); // 扫描前导空格
    if (s[idx] == '+' || s[idx] == '-') idx++;
    if (idx == s.size()) return false;

    bool res = true;
    bool int_digits = scan_digits(s, idx); // 扫描0~9的数位
    if (idx != s.size()) {
        // for floats
        if (s[idx] == '.') {
            idx++;
            bool frac_digits = scan_digits(s, idx);
            if (!frac_digits && !int_digits) {
                res = false;
            }
            else if (s[idx] == 'e' || s[idx] == 'E') {
                res = is_exponential(s, idx);
            }
        }
        // for integers
        else if (int_digits && (s[idx] == 'e' || s[idx] == 'E')) {
            res = is_exponential(s, idx);
        }
        else if (!int_digits) res = false;
    }
    scan_space(s, idx); // 扫描后缀空格
    return res && idx == s.size();
}

int main() {
	vector<string> data = { " 1 ","1.",".1",".","e1","6.e3","-1.e49046 " };
	for (auto s : data) {
		cout << isNumber(s) << endl;
	}	
	return 0;
}
