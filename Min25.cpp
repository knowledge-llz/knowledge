/*************************************************************************
	> File Name: Min25模板.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> https://www.luogu.com.cn/problem/P5325
	> Created Time: 2020/9/26 15:38:44
	> 求f(x)是积性函数,f(x^k)=(x^k-1)x^k (When x is prime)，求1到n所有f(x)的值.
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
const int maxx=2e5+10,mod=1e9+7;
LL pri[maxx],a[maxx],sum[maxx],g1[maxx],g2[maxx],id1[maxx],id2[maxx];
LL pri2[maxx],sum2[maxx];
LL inv2,inv3,cnt=0,sq,n;
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
#define id(x) ((x<=sq) ? id1[x] : id2[n/x])
void init(LL x){
	For(i,2,x){
		if(!flag[i]){ 
			pri[++cnt]=i;
			sum[cnt]=(sum[cnt-1]+pri[cnt])%mod;
			pri2[cnt]=i*i%mod;
			sum2[cnt]=(sum2[cnt-1]+pri2[cnt])%mod;
		}
		For(j,1,cnt){
			if(i*pri[j]>x) break;
			flag[i*pri[j]]=1;
			if(!(i%pri[j])) break;
		}
	}
}
LL S(LL x,LL y){
	if(pri[y]>=x) return 0;
	LL k=id(x);
	LL ans=(g2[k]-g1[k]-sum2[y]+sum[y])%mod;
	for(int i=y+1;i<=cnt && pri[i]*pri[i]<=x;++i){
		LL pe=pri[i];
		for(int e=1;pe<=x;pe*=pri[i],++e){
			LL xk=pe%mod;
			ans+=(S(x/pe,i)+(e!=1))*(xk)%mod*(xk-1)%mod;
			ans%=mod;
		}
	}
	return ans;
}

void min25(LL n){
	sum[0]=0;
	LL m=0;
	for(LL i=1;i<=n;i=n/a[m]+1){
		a[++m]=n/i;
		if(a[m]<=sq) id1[a[m]]=m;
		else id2[n/a[m]]=m;
		LL tmp=a[m]%mod;
		g1[m]=tmp*(tmp+1)%mod*inv2%mod;
		g2[m]=g1[m]*(2*tmp+1)%mod*inv3%mod;
		--g1[m]; --g2[m];
	}
	For(i,1,cnt)
		For(j,1,m){
			if(pri[i]*pri[i]>a[j]) break;
			g1[j]=(g1[j]-pri[i]*(g1[id((a[j]/pri[i]))]-sum[i-1])%mod)%mod;
			g2[j]=(g2[j]-pri2[i]*(g2[id((a[j]/pri[i]))]-sum2[i-1])%mod)%mod;
		}
//	printf("%lld %lld\n",g1[id(n)],g2[id(n)]);
}
			

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); sq=sqrt(n+0.5);
	inv2=qpow(2,mod-2);
	inv3=qpow(3,mod-2);
	init(sq);
	min25(n);
	printf("%lld\n",(S(n,0)+1+mod)%mod);
	return 0;
}
