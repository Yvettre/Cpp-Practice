/***************************************************************
Leetcode-medium-79: My runtime is 20ms, beats 98.30%.

Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell,
where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once.

URL: https://leetcode.com/problems/word-search/
****************************************************************/
#include<vector>
using namespace std;

bool DFS(vector<vector<char>>& board, vector<vector<bool>>& path, vector<int> node, string subword) {
  
  // 向下走一步
  if (node[0]+1<board.size() && !path[node[0]+1][node[1]]) {
    if (board[node[0]+1][node[1]]==subword[0]) {
      path[node[0]+1][node[1]] = true;
      if (subword.size()==1 || DFS(board, path, {node[0]+1, node[1]}, subword.substr(1))){
        return true;
      }
      path[node[0]+1][node[1]] = false;
    }
  }
  
  // 向右走一步
  if (node[1]+1<board[0].size() && !path[node[0]][node[1]+1]) {
    if (board[node[0]][node[1]+1]==subword[0]) {
      path[node[0]][node[1]+1] = true;
      if (subword.size()==1 || DFS(board, path, {node[0], node[1]+1}, subword.substr(1))){
        return true;
      }
      path[node[0]][node[1]+1] = false;
    }
  }
  
  // 向左走一步
  if (node[1]-1>=0 && !path[node[0]][node[1]-1]) {
    if (board[node[0]][node[1]-1]==subword[0]) {
      path[node[0]][node[1]-1] = true;
      if (subword.size()==1 || DFS(board, path, {node[0], node[1]-1}, subword.substr(1))){
        return true;
      }
      path[node[0]][node[1]-1] = false;
    }
  }
  
  // 向上走一步
  if (node[0]-1>=0 && !path[node[0]-1][node[1]]) {
    if (board[node[0]-1][node[1]]==subword[0]) {
      path[node[0]-1][node[1]] = true;   
      if (subword.size()==1 || DFS(board, path, {node[0]-1, node[1]}, subword.substr(1))){
        return true;
      }
      path[node[0]-1][node[1]] = false;  
    }
  }
  
  return false;  //四步走完没有匹配值，寻找不成功，返回false
}

bool exist(vector<vector<char>>& board, string word) {
  int rows = board.size();
  if (rows==0) return false;
  
  int cols = board[0].size();
  if (cols==0 || rows*cols<word.size()) return false;
  
  vector<vector<bool>> path(rows, vector<bool>(cols, false));  //标记点是否被访问
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      if (board[i][j]==word[0]) {
        path[i][j] = true;   //匹配的值的位置先标记为true
        if (word.size()==1 || DFS(board, path, {i, j}, word.substr(1))) {
          return true;
        }
        path[i][j] = false;  //寻找不成功将路径对应的点还原标记为false
      }
    }
  }
  return false;
}