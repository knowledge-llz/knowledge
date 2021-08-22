/*************************************************************************
	> File Name: 5.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> http://acm.hdu.edu.cn/showproblem.php?pid=6889
	> Created Time: 2020/9/26 15:38:44
	> min25函数求n以内的所有质数的和
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register LL i=(a);i<=(b);++i)
#define LL long long
using namespace std;
LL read(){
	char x=getchar(); LL u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
LL mod,pri[maxx],a[maxx],sum[maxx],g[maxx],id1[maxx],id2[maxx],cnt=0;
bool flag[maxx];
LL qpow(LL x,LL y){
	LL res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void init(){
	LL x=maxx>>1;
	For(i,2,x){
		if(!flag[i]){ pri[++cnt]=i; sum[cnt]=sum[cnt-1]+pri[cnt]; }
		For(j,1,cnt){
			if(i*pri[j]>x) break;
			flag[i*pri[j]]=1;
			if(!(i%pri[j])) break;
		}
	}
}
#define id(x) ((x<=sq) ? id1[x] : id2[n/x])
LL min25(LL n){
	sum[0]=0;
	LL sq=sqrt(n+0.5),ncnt,m=0;
	ncnt=upper_bound(pri+1,pri+cnt+1,sq)-pri;
	for(LL i=1;i<=n;i=n/a[m]+1){
		a[++m]=n/i;
		if(a[m]<=sq) id1[a[m]]=m;
		else id2[n/a[m]]=m;
		g[m]=(a[m]*(a[m]+1)/2-1)%mod;
	}
	For(i,1,ncnt)
		For(j,1,m){
			if(pri[i]*pri[i]>a[j]) break;
			g[j]=g[j]-pri[i]*(g[id((a[j]/pri[i]))]-sum[i-1]);
		}
	return g[id(n)];
}
			

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read();
	init();
	while(T--){
		LL n,ans;
		n=read()+1; mod=read();
		ans=(n-1)%mod*(n+2)%mod*qpow(2,mod-2)%mod-4;
		ans=(ans+min25(n)%mod)%mod;
		printf("%lld\n",(ans+mod)%mod);
	}
	return 0;
}
