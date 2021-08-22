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
int m,f[maxx],nxt[maxx][30],len[2000010],lens;
LL dp[maxx][2],ans=0,sum[2000010];
void init(){
	f[0]=f[1]=0;
	For(i,1,lens-1){
		int j=f[i-1];
		while(j && s[j]!=s[i]) j=f[j-1];
		if(s[j]==s[i]) ++j;
		f[i]=j;
		nxt[i-1][s[i-1]-'a']=i;
	}
	nxt[lens-1][s[lens-1]-'a']=lens;
}
void build(){
	For(i,1,lens){
		int u=f[i-1];
		For(j,0,25){
			if(nxt[i][j]) continue;
			nxt[i][j]=nxt[u][j];
		}
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
	for(int i=m;i>=1;--i) sum[i]=sum[i+1]*(LL)len[i]%mod;
	init(); build();
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
