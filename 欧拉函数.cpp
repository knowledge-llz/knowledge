/*************************************************************************
	> File Name: 3.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/9/6 16:48:19
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
const int maxx=1e6+10;
LL phi[maxx],pri[maxx],e[maxx],cnt=0;
unordered_map<LL,LL>Map;
bool vis[maxx];
//求单个欧拉函数 O(sqrt(n))
LL Phi(LL x){
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

//埃氏筛O(nlogn)
void getphi(LL maxn){
	phi[1]=1;
	for(LL i=2;i<=maxn;++i)
		if(!phi[i])
			for(LL j=i;j<=maxn;j+=i){
				if(!phi[j]) phi[j]=j;
				phi[j]=phi[j]/i*(i-1);
			}
}
//线性筛O(n)
void get_phi(LL maxn){
	e[1]=1;
	for(LL i=2;i<=maxn;++i){
		if(!vis[i]){
			pri[++cnt]=i;
			e[i]=i-1;
		}
		for(LL j=1;pri[j]<=maxn/i;++j){
			LL t=i*pri[j];
			vis[t]=1;
			if(i%pri[j]==0){
				e[t]=e[i]*pri[j];
				break;
			}
			e[t]=e[i]*(pri[j]-1);
		}
	}
}
//求a^a^a^a^a^a b个幂，模数为m
LL qpow(LL x,LL y,LL m){
	LL res=1;
	while(y){
		if(y&1) res=Mod(res*x,m);
		x=Mod(x*x,m);
		y>>=1;
	}
	return res;
}
LL solve(LL a,LL b,LL m){
	if(b==1 || m==1) return Mod(a,m);
	return qpow(a,solve(a,b-1,e[m]),m);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read();
	get_phi(maxx-10);
	while(T--){
		LL a=read(), b=read(), m=read();
		if(!b) printf("%lld\n",1%m);
		else printf("%lld\n",solve(a,b,m)%m);
	}
	return 0;
}
