/***************************************************************
Leetcode-medium-48: Runtime is 4ms.

You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.

URL: https://leetcode.com/problems/rotate-image/
****************************************************************/
#pragma once
#include<vector>
#include<algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
	size_t n = matrix[0].size();
	
	for (size_t i = 0; i < n / 2; i++) {         // i<n/2+n%2(调换约束条件是一样的)
		for (size_t j = 0; j < n / 2 + n % 2; j++) { // j<n/2
			vector<int> tmplist(4);
			size_t row = i;
			size_t col = j;
			for (size_t k = 0; k < 4; k++) {
				tmplist[k] = matrix[row][col];
				int x = row;
				row = col;
				col = n - 1 - x;
			}
			for (size_t k = 0; k < 4; k++) {
				matrix[row][col] = tmplist[(k + 3) % 4];
				int x = row;
				row = col;
				col = n - 1 - x;
			}
		}	
	}
}