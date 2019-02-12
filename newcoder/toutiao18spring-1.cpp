/***************************************************************
头条2018年校招：编程题1

有三只球队，每只球队编号分别为球队1，球队2，球队3，这三只球队一共需要进行 n 场比赛。
现在已经踢完了k场比赛，每场比赛不能打平，踢赢一场比赛得一分，输了不得分不减分。
已知球队1和球队2的比分相差d1分，球队2和球队3的比分相差d2分，每场比赛可以任意选择两只队伍进行。
求如果打完最后的 (n-k) 场比赛，有没有可能三只球队的分数打平。

- 输入描述：
    第一行包含一个数字 t (1 <= t <= 10)
    接下来的t行每行包括四个数字 n, k, d1, d2(1 <= n <= 10^12; 0 <= k <= n, 0 <= d1, d2 <= k)
- 输出描述：
    每行的比分数据，最终三只球队若能够打平，则输出“yes”，否则输出“no”

示例：
- 输入：
2
3 3 0 0
3 3 3 3
- 输出：
yes
no
- 分析：
case1: 球队1和球队2差0分，球队2和球队3也差0分，所以可能的赛得分是三只球队各得1分
case2: 球队1和球队2差3分，球队2和球队3差3分，所以可能的得分是球队1得0分，球队2得3分, 球队3得0分，
比赛已经全部结束因此最终不能打平。
****************************************************************/

/*
思路是参考了讨论的，主要是为了记录<limits.h>里面的几个最大最小值的用法(结尾处注释)
思路：
比赛场次能被3整除且当前球队最高分小于等于n/3，则有可能踢平，步骤：
1、n是否能被3整除，否输出no，是进行2
2、求满足(k,d1,d2)的所有最大得分的最小值
    有4种情况，即大大、小小、大小、小大，即从这四种情况的最高得分选最小那个
3、如果这个最小值≤n/3，输出yes，否则输出no
*/

#include<iostream>
#include<string>
#include<algorithm>
#include<limits.h>
using namespace std;

string helper(long long& n,long long& k,long long& d1,long long& d2){
    if (n%3!=0) return "no";
    
    long long tmp;   //3*f1

    // limits.h中的宏定义（其实climits里面就是include了limits.h和yvals.h）
    // 然而网上也有人用LONG_LONG_MAX，虽然牛客网通过了，但是本地IDE会报错找不到宏
    long long maxf = LLONG_MAX;   
    
    //f1<f2<f3
    tmp = k-d1-d1-d2;
    if(tmp>=0 && tmp%3==0) maxf = min(maxf, tmp/3+d1+d2);
    
    //f1>f2>f3
    tmp = k+d1+d1+d2;
    if(tmp>=0 && tmp%3==0) maxf = min(maxf, tmp/3);
    
    //f1<f2>f3
    tmp = k-d1-d1+d2;
    if(tmp>=0 && tmp%3==0) maxf = min(maxf, tmp/3+d1);
    
    //f1>f2<f3
    tmp = k+d1+d1-d2;
    if(tmp>=0 && tmp%3==0){
        if(d1>=d2) maxf = min(maxf, tmp/3);
        else maxf = min(maxf, tmp/3-d1+d2);
    }
    
    if(3*maxf<=n) return "yes";
    else return "no";
}

int main(){
    size_t t;
    while(cin>>t){
        while(t!=0){
            long long n,k,d1,d2;
            cin>>n>>k>>d1>>d2;
            cout<<helper(n,k,d1,d2)<<endl;
            t--;
        }
    }
    return 0;
}

/*
#define MB_LEN_MAX    5             // max. # bytes in multibyte char
#define SHRT_MIN    (-32768)        // minimum (signed) short value
#define SHRT_MAX      32767         // maximum (signed) short value
#define USHRT_MAX     0xffff        // maximum unsigned short value
#define INT_MIN     (-2147483647 - 1) // minimum (signed) int value
#define INT_MAX       2147483647    // maximum (signed) int value
#define UINT_MAX      0xffffffff    // maximum unsigned int value
#define LONG_MIN    (-2147483647L - 1) // minimum (signed) long value
#define LONG_MAX      2147483647L   // maximum (signed) long value
#define ULONG_MAX     0xffffffffUL  // maximum unsigned long value
#define LLONG_MAX     9223372036854775807i64       // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807i64 - 1)  // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffui64       // maximum unsigned long long int value
*/