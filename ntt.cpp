//多项式相乘：https://www.luogu.com.cn/problem/P3803
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
using namespace std;
const double pi=acos(-1);
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int mod=998244353;
LL f[1<<22|1],g[1<<22|1];
int n,m,dp[1<<22|1];
LL qpow(LL x,LL y){
	LL res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res%mod;
}
void ntt(LL *x,bool idft){
	For(i,1,n-1)
		if(i<dp[i])
			swap(x[i],x[dp[i]]);
	
	for(int i=2;i<=n;i<<=1){
		LL w=qpow(3,(mod-1)/i);
		int len=(i>>1);
		if(idft) w=qpow(w,mod-2);
		for(int k=0;k<n;k+=i){
			LL p=1;
			for(int l=k;l<k+len;l++){
				LL tmp=p*x[len+l]%mod;
				x[len+l]=(x[l]-tmp+mod)%mod;
				x[l]=(x[l]+tmp)%mod;
				p=p*w%mod;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(),m=read();
	For(i,0,n) f[i]=(read()+mod)%mod;
	For(i,0,m) g[i]=(read()+mod)%mod;
	for(m+=n,n=1;n<=m;n<<=1);
	For(i,1,n-1)
		dp[i]=(dp[i>>1]>>1)|((i&1)?n>>1:0);
	
	ntt(f,0); ntt(g,0);
	For(i,0,n-1) f[i]=f[i]*g[i]%mod;
	ntt(f,1);
	LL inv=qpow(n,mod-2);
	For(i,0,m) printf("%lld ",f[i]*inv%mod);
	return 0;
}
