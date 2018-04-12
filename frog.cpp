/***************************************************************
牛客网-2017校招真题在线编程
——滴滴出行：地下迷宫——
链接：https://www.nowcoder.com/practice/571cfbe764824f03b5c0bfd2eb0a8ddf?tpId=85&tqId=29860&tPage=2&rp=2&ru=/ta/2017test&qru=/ta/2017test/question-ranking

本解答结果：占用内存480k，运行时间4ms
****************************************************************/
#include<iostream>
#include<queue>
#include<vector>
#include<string>

using namespace std;

void ShowPath(const vector<pair<int, int>>& path)
{
    int len=path.size();
    for(int i=0; i<len-1; i++){
        cout<<"["<<path[i].first<<","<<path[i].second<<"],";
    }
    cout<<"["<<path[len-1].first<<","<<path[len-1].second<<"]";
}

int up=3;
int down=0;
int horizon=1;

int main()
{
    int n,m,P;
    while(cin>>n>>m>>P){
        vector<vector<int>> maze(n, vector<int>(m, 0));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin>>maze[i][j];
            }
        }

        vector<pair<int, int>> best_path;
        int minP = P+1;
        queue<vector<int>> q;
        queue<vector<pair<int, int>>> path_q;
        // {x, y, p, from_direction}
        // from_direction:up-0, left-1, right-2, down-3
        q.push({0, 0, 0, 0});
        path_q.push({ {0, 0} });

        while(!q.empty()){
            // 取出最先加到队列的坐标
            vector<int> node = q.front();
            vector<pair<int, int>> current_path = path_q.front();
            q.pop();
            path_q.pop();

            // 判断当前点是否是终点，记录最佳路径
            if(node[0]==0 && node[1]==m-1 && node[2]<=P){
                if(node[2]<minP){
                    best_path = current_path;
                    minP = node[2];
                }
                continue;
            }
            // 判断当前是否还有体力
            if(node[2]>=P) continue;

            // 向下走一步
            if(node[0]+1<n && node[3]!=3){
                if(maze[node[0]+1][node[1]]==1){
                    q.push({node[0]+1, node[1], node[2]+down, 0});
                    current_path.push_back({node[0]+1, node[1]});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向右走一步
            if(node[1]+1<m && node[3]!=2){
                if(maze[node[0]][node[1]+1]==1){
                    q.push({node[0], node[1]+1, node[2]+horizon, 1});
                    current_path.push_back({node[0], node[1]+1});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向左走一步
            if(node[1]-1>=0 && node[3]!=1){
                if(maze[node[0]][node[1]-1]==1){
                    q.push({node[0], node[1]-1, node[2]+horizon, 2});
                    current_path.push_back({node[0], node[1]-1});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向上走一步
            if(node[0]-1>=0 && node[3]!=0){
                if(maze[node[0]-1][node[1]]==1){
                    q.push({node[0]-1, node[1], node[2]+up, 3});
                    current_path.push_back({node[0]-1, node[1]});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
        }
        if(best_path.empty()){
            cout<<"Can not escape!"<<endl;
        }
        else{
            ShowPath(best_path);
        }
    }
    return 0;
}