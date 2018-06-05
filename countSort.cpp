#include<iostream>
#include<vector>
using namespace std;

void show(const int arr[], int size) {
    for (int i = 0; i<size; i++) {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<endl;
}

void showVector(const vector<int>& v) {
    for (int i=0; i<v.size(); i++) {
        std::cout<<v[i]<<" ";
    }
}

vector<int> count_sort(const int arr[], int size) {
    int min_value = arr[0];
    int max_value = arr[0];
    for (int i=1; i < size; i++) {
        if (min_value > arr[i]) min_value = arr[i];
        if (max_value < arr[i]) max_value = arr[i];
    }
    vector<int> tmp_arr(max_value - min_value + 1, 0);
    for (int i=0; i< size; i++) {
        tmp_arr[arr[i] - min_value] += 1;
    }
    vector<int> result;
    for (int i=0; i< max_value - min_value + 1; i++) {
        while (tmp_arr[i]!=0) {
            tmp_arr[i] -= 1;
            result.push_back(i + min_value);
        }
    }
    return result;
}

int main() {
    int arr[] = {72,6,57,88,60,42,83,73,6,85};
    std::cout<<"before sort:"<<endl;
    show(arr, 10);
    vector<int> result;
    result = count_sort(arr, 10);    
    std::cout<<"after sort:"<<endl;
    showVector(result);
}