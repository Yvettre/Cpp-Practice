/***************************************************************
牛客网2016校招真题在线编程
——美团：二维数组打印——

有一个二维数组(n*n),写程序实现从右上角到左下角沿主对角线方向打印。
给定一个二位数组arr及题目中的参数n，请返回结果数组。
测试样例：
[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]],4
返回：[4,3,8,2,7,12,1,6,11,16,5,10,15,9,14,13]

我的解答结果：占用内存5048k，运行时间232ms
理解别人的解答思路后重写的结果：占用内存8196k，运行时间328ms
****************************************************************/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

// 我的答案
vector<int> arrayPrint(vector<vector<int> > arr, int n) {
    queue<pair<int, int>> q;
    q.push({ 0, n-1 });
    vector<int> path;
    pair<int, int> back_node;
    while(!q.empty()){
        // 访问队列最后一个点的坐标
        back_node = { q.back().first, q.back().second };

        // 取出最先加入队列的坐标和值
        pair<int, int> node = q.front();
        q.pop();

        // 将当前访问点的值加入路径队列
        path.push_back(arr[node.first][node.second]);       
        // 将当前点左边的点加入队列
        if(node.second-1>=0){
            if(back_node.first!=node.first || back_node.second!=node.second-1){
                q.push({ node.first, node.second-1 });
            }            
                   
        }

        // 将当前点下边的点加入队列
        if(node.first+1<n){
            if(back_node.first!=node.first+1 || back_node.second!=node.second){
                q.push({ node.first+1, node.second });
            }                     
        }
    }
    return path;
}

// 理解别人的答案后重写的答案
vector<int> arrayPrint_other(vector<vector<int> > arr, int n) {
    vector<int> result;
    int startX=0, startY=n-1;
    while(startX<n && startY<n){
        int i=startX, j=startY;
        while(i<n && j<n){
            result.push_back(arr[i][j]);
            i++;
            j++;
        }
        if(startY>0) startY--;
        else startX++;
    }
    return result;
}

void showVector(const vector<int>& v){
    std::cout<<"[";
    for(int i=0; i<v.size()-1; i++){
        std::cout<<v[i]<<",";
    }
    std::cout<<v[v.size()-1]<<"]"<<endl;

}

int main(){
    int n;
    while(cin>>n){
        if(n<=0) continue;
        vector<vector<int>> maze(n, vector<int>(n, 0));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>maze[i][j];
            }
        }
        vector<int> path = arrayPrint(maze, n);  
        // 打印path
        showVector(path);
    }    
    return 0;
}
