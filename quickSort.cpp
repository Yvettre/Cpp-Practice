#include<iostream>
using namespace std;

void show(const int arr[], int size) {
    for (int i = 0; i<size; i++) {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<endl;
}

void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        // sort
        int i = left, j = right, center = arr[left];
        while (i < j) {
            // 从右像向左找第一个小于center的数
            while (i < j && center<=arr[j]) j--;
            if (i < j) {
                arr[i] = arr[j];
                i++;
            }
            // 从左向右找第一个大于center的数
            while (i < j && center>arr[i]) i++;
            if (i < j) {
                arr[j] = arr[i];
                j--;
            }
        }
        arr[i] = center;
        // 递归
        quick_sort(arr, left, i-1);
        quick_sort(arr, j+1, right);
    }
}

int main() {
    int arr[] = {72,6,57,88,60,42,83,73,6,85};
    std::cout<<"before sort:"<<endl;
    show(arr, 10);
    quick_sort(arr, 0, 10);
    std::cout<<"after sort:"<<endl;
    show(arr, 10);
}