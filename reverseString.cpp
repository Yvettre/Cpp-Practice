/***************************************************************
对于一个字符串，和字符串中的某一位置，请设计一个算法，将包括i位置在内的左侧部分移动到右边，将右侧部分移动到左边。
给定字符串A和它的长度n以及特定位置p，请返回旋转后的结果。

测试样例：
"ABCDEFGH",8,4
返回："FGHABCDE"

我的解答结果：占用内存476k，运行时间5ms
剑指offer的解答：占用内存460k，运行时间4ms
****************************************************************/
#include<iostream>
#include<string>
using namespace std;

//我的解答
string rotateString(string A, int n, int p) {
  return A.substr(p+1) + A.substr(0, p+1);
}

//剑指offer上的解答
string rotateString2(string A, int n, int p) {
  //对p位置前面部分进行翻转
  int i=0, j=p;
  while(i<j) {
    swap(A[i++], A[j--]);
  }

  //对p位置后面部分进行翻转
  i = p+1;
  j = n-1;
  while(i<j) {
    swap(A[i++], A[j--]);
  }

  //对进行了两次局部翻转的整体进行翻转
  i = 0;
  j = n-1;
  while(i<j) {
    swap(A[i++], A[j--]);
  }

  return A;
}

int main(){
  string A="PQWIVLQQ";
  std::cout << rotateString2(A, 8, 5) << std::endl;
  return 0;
}