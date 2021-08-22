/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/6/10 15:32:28
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=1e3+10,mod=1e9+7;
char s[maxx],t[maxx];
int m,f[maxx],nxt[maxx][30],lens;
LL dp[maxx][2],ans=0,len[2000010],sum[2000010];
void init(){
	for(int i=1, fail=0; i<=lens; ++i){
			fail=nxt[fail][s[i-1]-'a'];
			nxt[i-1][s[i-1]-'a']=i;
			for(int j=0;j<=25;++j)
				nxt[i][j]=nxt[fail][j];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	bool sw=0;
	scanf("%s",s);
	lens=strlen(s);
	m=read();
	For(i,1,m) len[i]=read();
	sum[m+1]=1;
	for(int i=m;i>=1;--i) sum[i]=sum[i+1]*len[i]%mod;
	init();
	dp[0][sw]=1;
	For(_,1,m){
		scanf("%s",t);
		sw^=1;
		For(i,0,lens)
			if(dp[i][sw^1]){
				For(j,0,len[_]-1)
					(dp[nxt[i][t[j]-'a']][sw]+=dp[i][sw^1])%=mod;
				dp[i][sw^1]=0;
			}
		ans+=dp[lens][sw]*sum[_+1]%mod;
		ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
