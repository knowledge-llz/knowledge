/*************************************************************************
    > Author: Knowledge-Pig
    > Blog: https://www.luogu.com.cn/problem/P4717
************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
#define endl '\n'
using namespace std;
const int maxx = (1 << 17 | 1), mod = 998244353, inv_2 = 499122177;
LL n, A[maxx], B[maxx], a[maxx], b[maxx];
void FWT_or(LL *f, int t){
	for(int i = 2; i <= n; i <<= 1){
		int len = i >> 1;
		for(int j = 0; j < n; j += i)
			for(int k = j; k < j + len; ++k)
				f[k + len] = (f[k + len] + f[k] * t) % mod;
	}
}
void FWT_and(LL *f, int t){
	for(int i = 2; i <= n; i <<= 1){
		int len = i >> 1;
		for(int j = 0; j < n; j += i)
			for(int k = j; k < j + len; ++k)
				f[k] = (f[k] + f[k + len] * t) % mod;
	}
}
void FWT_xor(LL *f, int t){
	for(int i = 2; i <= n; i <<= 1){
		int len = i >> 1;
		for(int j = 0; j < n; j += i)
			for(int k = j; k < j + len; ++k){
				LL x = f[k], y = f[k + len];
				f[k] = (x + y) % mod;
				f[k + len] = (x - y) % mod;
				if(t == -1){
					f[k] = f[k] * inv_2 % mod;
					f[k + len] = f[k + len] * inv_2 % mod;
				}
			}
	}
}
void work(void (*FWT)(LL *f, int t)){
	for(int i = 0; i < n; ++i) a[i] = A[i], b[i] = B[i];
	FWT(a, 1); FWT(b, 1);
	for(int i = 0; i < n; ++i) a[i] = a[i] * b[i] % mod;
	FWT(a, -1);
	for(int i = 0; i < n; ++i) cout << (a[i] + mod) % mod << " ";
	cout << endl;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	cin >> n; n = 1 << n;
	for(int i = 0; i < n; ++i) cin >> A[i];
	for(int i = 0; i < n; ++i) cin >> B[i];
	work(FWT_or); work(FWT_and); work(FWT_xor);
	return 0;
}
