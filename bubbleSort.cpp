/***************************************************************
冒泡排序

对n个元素的数组a的元素按升序排序的方法是，首先将a[0]和a[1]进行比较，
如果为逆序（即a[0]>a[1]），则交换a[0]和a[1]，然后比较a[1]和a[2]，
以此类推，直到a[n-2]和a[n-1]进行过比较为止。这一过程称为一次冒泡，
其结果是a[0]~a[n-1]的最大元素将被放在a[n-1]的位置，所以也可以叫做一次沉底。
然后对a[0]~a[n-2]进行同样的一次冒泡（沉底），以此类推。

所以，冒泡的次数是数组长度减去1，即n-1次（即下面代码的第一层循环），
第i次（1<=i<=n）对数组中进行冒泡，参与比较的数组范围应是a[0]~a[n-i]，
而下面的代码的第二层循环中0<=j<=n-i-1的原因是，1<=j+1<=n-i。

isSwap的作用是：假如在某一次冒泡过程中没有发生交换，则排序可以提前结束了。
****************************************************************/
#include<iostream>
#include<vector>
using namespace std;

void bubble(vector<int>& nums) {
	//bubble sort
	size_t cnt = nums.size();
	if (cnt == 1) return;

	for (size_t i = 1; i < cnt; i++) {
		bool isSwap = false;
		for (size_t j = 0; j < cnt - i; j++) {
			if (nums[j] > nums[j + 1]) {
				int tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
				isSwap = true;
			}	
		}
		if (!isSwap) break;
	}
}

int main() {
	int n;
	while (cin >> n) {
		vector<int> nums(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> nums[i];
		}

		bubble(nums);

		for (auto num : nums) {
			cout << num;
		}
		cout << endl;
	}
}