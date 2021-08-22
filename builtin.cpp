#include<bits/stdc++.h>
using namespace std;
int main(){
	int x = 8;
	cout << __builtin_ffs(x) << endl;//返回最后一个为1的位是从后向前的第几位
	cout << __builtin_popcount(x) << endl;//返回1的个数
	cout << __builtin_ctz(x) << endl; //x末尾0的个数
	cout << __builtin_clz(x) << endl; //x前导0的个数
	cout << __builtin_parity(x) << endl; //x中1的奇偶性
	return 0;
}
