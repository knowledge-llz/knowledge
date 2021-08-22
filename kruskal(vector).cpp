/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/10/2 11:09:17
 ************************************************************************/
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define pb push_back
#define pr pair<int,int>
#define LL long long
#define fi first
#define se second
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
int n,m,ans=0,f[maxx];
int Find(int x){
	return f[x]==x? x : f[x]=Find(f[x]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); m=read();
	vector<pair<int,pr>> e(m);
	for(auto &x:e){
		x.se.fi=read();
		x.se.se=read();
		x.fi=read();
	}
	For(i,1,n) f[i]=i;
	sort(e.begin(),e.end());
	for(auto x:e){
		int u=x.se.fi,v=x.se.se;
		u=Find(u); v=Find(v);
		if(u!=v) f[u]=v, ans+=x.fi;
	}
	printf("%d\n",ans);
	return 0;
}
