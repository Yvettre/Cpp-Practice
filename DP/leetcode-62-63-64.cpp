/***************************************************************
leetcode-medium-62：Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?
Notes that m and n will be at most 100.

Input: m = 7, n = 3
Output: 28

URL:https://leetcode.com/problems/unique-paths/
****************************************************************/
/***************************************************************
leetcode-medium-63：Unique Paths 2

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.
Notes that m and n will be at most 100.

Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2

URL:https://leetcode.com/problems/unique-paths-ii/
****************************************************************/
/***************************************************************
leetcode-medium-64：Minimum Path Sum

Given a m x n grid filled with non-negative numbers,
find a path from top left to bottom right which minimizes the sum of all numbers along its path.
Notes that you can only move either down or right at any point in time.

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7

URL:https://leetcode.com/problems/minimum-path-sum/
****************************************************************/

#include<vector>
using namespace std;

// 62
int uniquePaths(int m, int n) {
    if(m==0 || n==0) return 0;
    if(m==1 || n==1) return 1;
    
    vector<vector<int>> mat(m, vector<int>(n,1));
    for (int i=1;i<m;i++){
        for (int j=1;j<n;j++){
            mat[i][j] = mat[i-1][j] + mat[i][j-1];
        }
    }
    return mat[m-1][n-1];
}

// 63
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int rows = obstacleGrid.size();
    if (rows==0) return 0;
    int cols = obstacleGrid[0].size();
    if (cols==0) return 0;
    if (obstacleGrid[0][0]==1 || obstacleGrid[rows-1][cols-1]==1) return 0;
    
    vector<vector<long long>> mat(rows, vector<long long>(cols,1));
    for (int i=1;i<rows;i++) {
        if (obstacleGrid[i][0]==1) {
            for (int j=i;j<rows;j++) {
                mat[j][0] = 0;
            }
            break;
        }
        mat[i][0] = 1;
    }
    for (int i=1;i<cols;i++) {
        if (obstacleGrid[0][i]==1) {
            for (int j=i;j<cols;j++) {
                mat[0][j] = 0;
            }
            break;
        }
        mat[0][i] = 1;
    }
    
    for (int i=1;i<rows;i++){
        for (int j=1;j<cols;j++){
            if (obstacleGrid[i][j]==1) {
                mat[i][j] = 0;
            }
            else {
                mat[i][j] = mat[i-1][j] + mat[i][j-1];
            }
        }
    }
    return mat[rows-1][cols-1];
}

// 64
int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size();
    if (rows==0) return 0;
    int cols = grid[0].size();
    if (cols==0) return 0;

    vector<vector<long long>> dp(rows, vector<long long>(cols));
    dp[0][0] = grid[0][0];
    for (int i=1;i<rows;i++){
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for (int j=1;j<cols;j++){
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }

    for (int i=1;i<rows;i++){
        for (int j=1;j<cols;j++){
            if (dp[i-1][j]<dp[i][j-1]){
                dp[i][j] = dp[i-1][j] + grid[i][j];
            }
            else {
                dp[i][j] = dp[i][j-1] + grid[i][j];
            }
        }
    }

    return dp[rows-1][cols-1];
}