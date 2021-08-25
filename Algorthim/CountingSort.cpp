#include <iostream>
#include <vector>
using namespace std;

//cout runing time == O(k) + O(n) + O(k) + O(n) ==>  O(k+n)
//if k is smaller is good, such as k <= n, else is not good 
void countingsort(vector<int> &arr, vector<int> &ret, int k) {
	//cost runing time O(k)
	vector<int> new_arr(k,0);
	//O(n)
	for (size_t i = 0; i < arr.size()-1; i++) { 
		new_arr[arr[i]]++;//O(1)
	}
	//O(k)
	for (int j = 1; j < k; j++) {
		new_arr[j] = new_arr[j] + new_arr[j-1];//O(1)
	}
	//O(n)
	for (size_t m = 0; m < arr.size()-1; m++) {
		ret[new_arr[arr[m]]] = arr[m];//O(1)
		new_arr[arr[m]]--;//O(1)
	}
}

int main(void) {
	vector<int> arr1 = {6,1,4,2,4,2,0};
	vector<int> arr2(arr1.size(),0);
	countingsort(arr1, arr2, 7);
	for (int i : arr2) {
		cout << i << " ";
	}
}
