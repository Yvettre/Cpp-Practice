/***************************************************************
剑指offer：数组中只出现一次的数字

一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。请写程序找出这两个只出现一次的数字。

拓展A：一个整型数组里除了一个数字之外，其他的数字都出现了三次。找出只出现了一次的数字。
拓展B：一个整型数组里除了三个数字之外，其他数字都出现了偶数次。找出这三个只出现了一次的数字。
****************************************************************/
#include<vector>
#include<iostream>
using namespace std;

/*
遍历数组，将每一个数组进行异或，得到的结果就是两个只出现了一次的数字的异或的结果，
因为其他数字都出现了偶数次，在异或中全部抵消了。
由于这两个数字肯定不一样，那么异或的结果肯定不为0，即存在至少一个位是1。
我们在这个结果中找到第一个1的位的位置，记作第firstBit1位。
然后我们以第firstBit1位是不是1为标准，把原来数组的数字分为两个部分，
这两个部分必然能将只出现了一次的两个数字分开。
最后，分别对两个子部分遍历进行异或，即得到两个数字，即所求。
*/
size_t get_first_idx(int num){
    // 从低位到高位，找出第一次出现的1的位置
    int indexBit = 0;
    while((num&1)==0 && indexBit<8*sizeof(int)){
        num = num>>1;
        indexBit++;
    }
    return indexBit;
}
bool is_bit1(int num, size_t idx){
    // 判断num的二进制形式中的第idx位（从低位到高位，0开始）是否是1
    num = num>>idx;
    return (num&1);
}
void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
    if (data.size()<=1) return;
    
    int yihuo = 0;
    for (auto d:data){
        yihuo ^= d;
    }
    size_t firstBit1 = get_first_idx(yihuo);
    
    for (auto d:data){
        if (is_bit1(d, firstBit1)){
            *num1 ^= d;
        }
        else {
            *num2 ^= d;
        }
    }
}


/* 拓展A：一个整型数组里除了一个数字之外，其他的数字都出现了三次。找出只出现了一次的数字。 */
/*
解法1: 整数一共8*sizeof(int)=32位，如果第i位出现了cnt次1，
那么cnt%3即为只出现了一次的数字的第i位。
*/
int findNum1(vector<int>& nums) {
	int res = 0;
	for (int i = 0; i < 8 * sizeof(int); i++) {
		// 从低位到高位开始
		int cnt_1_curbit = 0;
		for (auto d : nums) {
			// 统计第i位中出现1的数量
			cnt_1_curbit += (d >> i) & 1;
		}
		res |= (cnt_1_curbit % 3) << i;
	}
	return res;
}

/*
解法2: 其实都是O(n)啦，比较巧妙，纯位运算实现，不容易理解
*/
int findNum2(vector<int>& nums) {
	int one = 0; //记录只出现过1次1的位
	int two = 0; //记录只出现过2次1的位
	int three = 0;  //记录出现了3次1的位
	for (auto d : nums) {
		two = two | (one&d);
		one = one ^ d;
		three = one & two; //one和two中都为1的位即出现了3次
		one = one & (~three); //抹去出现了3次的位
		two = two & (~three); //抹去出现了3次的位
	}
	return one;
}


/* 拓展B：一个整型数组里除了三个数字之外，其他数字都出现了偶数次。找出这三个只出现了一次的数字。 */
/*
将这三个只出现了一次的数字记作a、b、c。将f(x)记作x中由低位到高位数起第一次出现1的位置（该位为1，其余为0）。
最后记g(x,a,b,c)=f(x^a)^f(x^b)^f(x^c)。
（1）将数组中的数字全部异或，得到的结果记作x=a^b^c。由于abc不相等，所以x肯定不等于abc中任何一个。
（2）由于x不等于abc中任何一个，因此x^a、x^b、x^c也都不等于0，因此f(x^a)、f(x^b)、f(x^c)也都不等于0。
（3）f(x^a)^f(x^b)的结果有可能为0（即x^a跟x^b第一次出现1的位置相同），
    也有可能有两个位为1（即x^a跟x^b第一次出现1的位置不同），因此，g(x,a,b,c)的结果要么只有一个1，要么就有三个1。
（4）也就是说：g(x,a,b,c)的结果至少有一个1，将第一个1的位置记作第m位（从低位到高位数起）。
    考虑8种情况的三个单位异或运算，易知，要使得结果为1，那么原来的三个单位的分布只有两种情况：要么只有一个1，要么有三个1；
    因此，仅考虑第m位，f(x^a)、f(x^b)、f(x^c)这三者中的第m位要么只有一个是1，要么三个都是1；
    因此，x^a、x^b、x^c这三者中的第m位也是要么只有一个1，要么三个都是1。
（5）最后，需要证明x^a、x^b、x^c这三者中只有一个的第m位是1，也就是推翻上一点的最后一个结论的后半段。反证法。
    假设x^a、x^b、x^c这三者的第m位都是1，那么a、b、c的第m位就是相同的，那么x的第m位就是0，
    但是由于a、b、c的第m位都是相同的，那么就有两种情况：
    如果a、b、c的第m位都是1，那么x=a^b^c的第m位就是1，与上面的x的第m位是0就矛盾了，所以不成立；
    如果a、b、c的第m位都是0，那么x=a^b^c的第m位就是0，那么x^a、x^b、x^c这三者的第m位都是0，与上面的假设又矛盾了，所以不成立。
    综上，x^a、x^b、x^c这三者中只有一个的第m位是1。 
所以，先遍历数组得到x=a^b^c，然后再遍历数组得到g(x,a,b,c)=f(x^a)^f(x^b)^f(x^c)，
然后将满足f(x^num)==f(g)条件的子数组部分全部异或，就能得到第一个只出现了一次的数字，
最后在剩下的数组中按照剑指offer中题目找出剩下的两个只出现了一次的数字就OK了。

最后：记录一个不同的版本的获得只出现一次的两个数字的简洁方法，思路一样，但是辅助函数的实现不一样
*/
int get_first_bit(int num) {
	return num & (~(num - 1));
}

void find2Num(vector<int>& nums, size_t start, size_t end) {
	int one = 0;
	int two = 0;
	int yihuo = 0;
	for (size_t i = start; i < end; i++) {
		yihuo ^= nums[i];
	}
	int flag_m = get_first_bit(yihuo);
	for (size_t i = start; i < end; i++) {
		if (nums[i] & flag_m) {
			one ^= nums[i];
		}
		else two ^= nums[i];
	}
	cout << one << " " << two << endl;
}

void find3Num(vector<int>& nums) {
	if (nums.size() < 5) return;

  // 得到x=a^b^c
	int one = 0;
	int x = 0;
	for (auto d : nums) {
		x ^= d;
	}

  // 得到g(x,a,b,c)=f(x^a)^f(x^b)^f(x^c)
	int g_xabc = 0;
	for (auto d : nums) {
		g_xabc ^= get_first_bit(x^d);
	}

  // 得到f(g)
	int flag_m = get_first_bit(g_xabc);

  // 得到第一个只出现了一次的数字one
	for (auto d : nums) {
		if (get_first_bit(x^d) == flag_m) one ^= d;
	}
	cout << one << " ";

  // 将one调到数组的最后
	for (size_t i = 0; i < nums.size(); i++) {
		if (nums[i] == one) {
			int tmp = nums[nums.size()-1];
			nums[nums.size() - 1] = one;
			nums[i] = tmp;
			break;
		}
	}

  // 除开one，在剩下的部分中找剩下的两个只出现了一次的数字
	find2Num(nums, 0, nums.size() - 1);
}

