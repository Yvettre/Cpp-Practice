/***************************************************************
网易17年校招：地牢逃脱（广搜）

给定一个n行m列的地牢，其中'.'表示可以通行的位置，'X'表示不可通行的障碍，牛牛从(x0,y0)位置出发，
遍历这个地牢，和一般的游戏所不同的是，他每一步只能按照一些指定的步长遍历地牢，
要求每一步都不可以超过地牢的边界，也不能到达障碍上。地牢的出口可能在任意某个可以通行的位置上。
牛牛想知道最坏情况下，他需要多少步才可以离开这个地牢。

- 输入描述：
  每个输入包含1个测试用例。
  每个测试用例的第一行包含两个整数n和m（1 <= n, m <= 50），表示地牢的长和宽。
  接下来的n行，每行m个字符，描述地牢，地牢将至少包含两个'.'。
  接下来的一行，包含两个整数x0, y0，表示牛牛的出发位置（0<=x0<n, 0<=y0<m，左上角的坐标为（0, 0），出发位置一定是'.'）。
  之后的一行包含一个整数k（0<k<=50）表示牛牛合法的步长数，
  接下来的k行，每行两个整数dx, dy表示每次可选择移动的行和列步长（-50<=dx, dy<=50）
- 输出描述：
  输出一行一个数字表示最坏情况下需要多少次移动可以离开地牢，如果永远无法离开，输出-1。
  以下测试用例中，牛牛可以上下左右移动。
  在所有可通行的位置.上，地牢出口如果被设置在右下角，牛牛想离开需要移动的次数最多，为3次。

输入：
3 3
...
...
...
0 1
4
1 0
0 1
-1 0
0 -1
输出：
3
****************************************************************/

/*
我能想到广搜，觉得答案应该是牛牛能到达的最远点（最坏情况是这个最远点到不了）所需的最少步数，
但是想不到用怎样的数据结构防止走回头路（剪枝）。。。
所以看别人的思路，我想不到的数据结构也就是关键，即下面代码中的steps，存储的是：
从起始点出发，到达[i][j]这个点所需要的最少步数为steps[i][j]。
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<limits.h>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> maze(n, vector<char>(m));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>maze[i][j];
        }
    }
    // 起始点坐标
    pair<int,int> start_node = {0,0};
    cin>>start_node.first>>start_node.second;
    // 可以走的方向，就是类似常规广搜的四个方向，只是现在是d_cnt种方向
    int d_cnt = 0;
    cin>>d_cnt;
    vector<pair<int,int>> next_diff(d_cnt);
    for (int i=0;i<d_cnt;i++){
        cin>>next_diff[i].first>>next_diff[i].second;
    }
    
    queue<pair<int,int>> q;
    vector<vector<int>> steps(n,vector<int>(m, INT_MAX));//初始化为所需步数为无限大
    steps[start_node.first][start_node.second] = 0; //起始点所需步数为0
    q.push(start_node);
    while(!q.empty()){
        pair<int,int> cur_node = q.front();
        q.pop();
        
        pair<int,int> next_node;
        for (int i=0;i<d_cnt;i++){
            next_node.first = cur_node.first + next_diff[i].first;
            next_node.second = cur_node.second + next_diff[i].second;
            // 如果下一个点有效
            if (next_node.first>=0 && next_node.first<n 
                && next_node.second>=0 && next_node.second<m 
                && maze[next_node.first][next_node.second]=='.'){
                // 如果从当前点到达下一个点所需步数比下一个点已记录的所需步数要少，
                // 则更新下一个点的所需步数，并将下一个点推入队列
                if (steps[next_node.first][next_node.second]
                    >steps[cur_node.first][cur_node.second]+1){
                    steps[next_node.first][next_node.second] = steps[cur_node.first][cur_node.second]+1;
                    q.push(next_node);
                }
            }
        }
    }
    int res = 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            // 遍历所有的可达点.的位置所需的最少步数，求出最大的那个（即最远点，即最坏情况）
            if (maze[i][j]=='.') res = max(res, steps[i][j]);
        }
    }
    // 如果到达最远点（最坏情况）所需步数是无限大，即最坏情况下无法逃脱，更新res为-1
    res = res==INT_MAX?-1:res;
    cout<<res<<endl;

    return 0;
}