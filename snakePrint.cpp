/***************************************************************
牛客网2016校招真题在线编程
——之字形打印矩阵——

对于一个矩阵，请设计一个算法，将元素按“之”字形打印。具体见样例。
给定一个整数矩阵mat，以及他的维数nxm，请返回一个数组，其中元素依次为打印的数字。
测试样例：
[[1,2,3],[4,5,6],[7,8,9],[10,11,12]],4,3
返回：[1,2,3,6,5,4,7,8,9,12,11,10]

解答结果：占用内存732k，运行时间24ms
****************************************************************/
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

void showResult(const vector<int> & result) {
    std::cout<<"[";
    for(int i=0; i<result.size()-1; i++) {
        std::cout<<result[i]<<",";
    }
    std::cout<<result[result.size()-1]<<"]"<<endl;
}

vector<int> printMatrix(vector<vector<int>> mat, int n, int m) {
    int i = 0, j = 0;
    vector<int> result;
    while(i<n) {
        while(j<m) {
            result.push_back(mat[i][j]);
            j++;
        }
        i++;
        j--;
        if(i>=n) break;
        while(j>=0) {
            result.push_back(mat[i][j]);
            j--;
        }
        j++;
        i++;
    }
    return result;
}

int main(){
    int n, m;
    while(cin>>n>>m){
        if(n<=0) continue;
        vector<vector<int>> maze(n, vector<int>(m, 0));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin>>maze[i][j];
            }
        }
        vector<int> result = printMatrix(maze, n, m);
        // show result
        showResult(result);
    }    
    return 0;
}