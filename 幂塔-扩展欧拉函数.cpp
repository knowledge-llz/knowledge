/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/9/7 23:05:10
	> 每次询问给定l和r，计算从w_l^w_{l+1}^w_{l+2}...^w_{r}
 ************************************************************************/
#include<unordered_map>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
#define Mod(a,b) (a<b?a:a%b+b)
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
unordered_map<LL,LL>Map;
LL n,m,q,a[maxx];
LL phi(LL x){
	if(Map[x]) return Map[x];
	LL ans=x,tmp=x;
	for(LL i=2;i*i<=x;++i){
		if(x%i==0) ans=ans/i*(i-1);
		while(x%i==0) x/=i;
	}
	if(x>1) ans=ans/x*(x-1);
	Map[tmp]=ans;
	return ans;
}
LL qpow(LL x,LL y,LL mod){
	LL res=1;
	while(y){
		if(y&1) res=Mod(res*x,mod);
		x=Mod(x*x,mod);
		y>>=1;
	}
	return res;
}

LL solve(LL l,LL r,LL mod){
	if(l==r || mod==1) return Mod(a[l],mod);
	return qpow(a[l],solve(l+1,r,phi(mod)),mod);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); m=read();
	For(i,1,n) a[i]=read();
	q=read();
	while(q--){
		LL l=read(),r=read();
		printf("%lld\n",solve(l,r,m)%m);
	}
	return 0;
}
