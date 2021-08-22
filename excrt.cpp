/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/P4777
	> Created Time: 2021/3/13 18:13:09
 ************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
LL read(){
	char x=getchar(); LL u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
LL n,m[maxx],a[maxx];
LL mul(LL x,LL y,LL mod){
	LL res=0;
	while(y){
		if(y&1) res=(res+x)%mod;
		x=(x+x)%mod;
		y>>=1;
	}
	return res;
}
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) { x = 1; y = 0; return a; }
	LL tmp=exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return tmp;
}
LL excrt(){
	LL ans=a[1],M=m[1];
	For(i,2,n){
		LL x,y,c=(a[i]-ans%m[i]+m[i])%m[i];
		LL gcd=exgcd(M,m[i],x,y);	//Mx+my=gcd(M,m)
		if(c%gcd) return -1;
		x=mul(x,c/gcd,m[i]/gcd);	//为防止爆LL
		ans+=x*M;
		M*=(m[i]/gcd);
		ans=(ans%M+M)%M;
	}
	return (ans%M+M)%M;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read();
	For(i,1,n) m[i]=read(),	a[i]=read();
	printf("%lld\n",excrt());
	return 0;
}
