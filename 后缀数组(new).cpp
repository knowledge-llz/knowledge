/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> https://www.luogu.com.cn/problem/P3809
	> Created Time: 2022/4/3 22:09:18
 ************************************************************************/

#include<bits/stdc++.h>
#define LL long long
#define endl '\n'
using namespace std;
const int maxx = 2e6 + 10;
int n, m, sa[maxx], x[maxx], y[maxx], c[maxx];
char s[maxx];
void build_sa(){
	for(int i = 1; i <= n; ++i) ++c[x[i] = s[i]];
	for(int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for(int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1){
		int num = 0;
		for(int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for(int i = 1; i <= n; ++i) if(sa[i] > k) y[++num] = sa[i] - k;
		for(int i = 1; i <= m; ++i) c[i] = 0;
		for(int i = 1; i <= n; ++i) ++c[x[i]];
		for(int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for(int i = n; i >= 1; --i){ sa[c[x[y[i]]]--] = y[i]; y[i] = 0; }
		swap(x, y);
		x[sa[1]] = num = 1;
		for(int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if(num == n) break;
		m = num;
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	cin >> s + 1;
	n = strlen(s + 1);
	m = 122;
	build_sa();
	for(int i = 1; i <= n; ++i) cout << sa[i] << " ";
	return 0;
}
