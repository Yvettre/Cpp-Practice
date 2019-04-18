/***************************************************************
leetcode-hard-135:Candy

There are N children standing in a line. Each child is assigned a rating value.
You are giving candies to these children subjected to the following requirements:
- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

Input: [1,0,2]
Output: 5
Input: [1,2,2]
Output: 4
****************************************************************/

/*
分两边考虑：
1、拥有高rating的孩子比他的左边孩子多一块糖
2、拥有高rating的孩子比他的右边孩子多一块糖

   ratings: 1 2 3 0 6 6 5 4
left2right: 1 2 3 1 2 1 1 1
right2left: 1 1 2 1 1 3 2 1
       max: 1 2 3 1 2 3 2 1
       sum: 15
*/

#include<vector>
using namespace std;

int candy(vector<int>& ratings) {
    if (ratings.size()<=1) return ratings.size();
    
    vector<int> candy(ratings.size(), 1);
    for (int i=1;i<ratings.size();i++) {
        if (ratings[i-1]<ratings[i]) {
            candy[i] = candy[i-1] + 1;
        }
    }
    int res = candy[ratings.size()-1];
    for (int i=ratings.size()-2;i>=0;i--) {
        if (ratings[i]>ratings[i+1]) {
            if (candy[i]<candy[i+1]+1) {
                candy[i] = candy[i+1] + 1;
            }
        }
        res += candy[i];
    }
    return res;
}