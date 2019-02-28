/***************************************************************
剑指offer：和为S的连续正数序列

小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。
但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。
没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。
现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!

输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
****************************************************************/
#include<iostream>
#include<vector>
using namespace std;

void saveRes(vector<vector<int>>& res, int small, int big){
    vector<int> tmp;
    for (int i=small;i<=big;i++){
        tmp.push_back(i);
    }
    res.push_back(tmp);
}
vector<vector<int> > FindContinuousSequence(int sum) {
    if (sum<=2) return  vector<vector<int>>();
    
    int small = 1, big = 2;
    vector<vector<int>> res;
    int cur_sum = small+big;
    while(2*small<=sum){
        if (cur_sum == sum) saveRes(res, small, big);
        
        // 固定big，先调small
        while(cur_sum>sum && 2*small<=sum){
            cur_sum = cur_sum - small;
            small++;
            if (cur_sum == sum) saveRes(res, small, big);
        }
        
        big++;
        cur_sum = cur_sum + big;
    }
    return res;
}