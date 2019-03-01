/***************************************************************
剑指offer：数组中出现次数超过一半的数字

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}，由于数字2在数组中出现了5次，
超过数组长度的一半，因此输出2。
如果不存在则输出0。
****************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/* 解法1：利用数组的特点 */
int MoreThanHalfNum1(vector<int> numbers) {
    if (numbers.size()==0) return 0;
    
    int res = numbers[0];   //当前出现次数最多的数字
    int cnt = 1;   //当前res与其他数字出现的次数抵消后的出现次数
    for (size_t i=1;i<numbers.size();i++){
        if (cnt==0) {
            //如果被抵消了，则重新设当前数字为出现次数最多的数字
            res = numbers[i];
            cnt = 1;
        }
        //cnt不等于0证明此前出现次数最多的数字还有次数可以继续抵消
        else if (res!=numbers[i]) {
            //抵消一次
            cnt--;
        }
        else cnt++;  //增加一次
    }
    //遍历完毕一次后，res记录的就是整个数组出现次数最多的数字
    //但它不一定出现次数超过数组的一半，因此需要先判断
    size_t times = 0;
    for (auto d:numbers){
        if (res==d) times++;
    }
    if (2*times>numbers.size()) return res;
    else return 0;
}


/* 解法2 */
// 排序之后超过数组一半的数字就是统计学意义上的中位数
int MoreThanHalfNum2(vector<int> numbers) {
    if (numbers.size()==0) return 0;
    
    sort(numbers.begin(),numbers.end());
    int res = numbers[numbers.size()>>1];
    
    size_t times = 0;
    for (auto d:numbers){
        if (res==d) times++;
    }
    if (2*times>numbers.size()) return res;
    else return 0;
}