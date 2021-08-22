/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/10/2 11:26:04
 ************************************************************************/
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define pb push_back
#define pr pair<int,int> 
#define LL long long
#define mk(a,b) make_pair(a,b)
#define fi first
#define se second
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10,oo=1e9+7;
int n,m,dis[maxx],ans=0,cnt=0;
bool vis[maxx];
priority_queue<pr,vector<pr>,greater<pr> >q;
vector<pr> e[maxx];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int u,v,c;
	n=read(); m=read();
	For(i,1,m){
		u=read(); v=read(); c=read();
		e[u].pb(mk(v,c));
		e[v].pb(mk(u,c));
	}
	For(i,1,n) dis[i]=oo;
	dis[1]=0;
	q.push(make_pair(dis[1],1));
	while(!q.empty() && cnt<n){
		int k=q.top().se,tmp=q.top().fi;
		q.pop();
		if(vis[k]) continue;
		vis[k]=1;
		ans+=tmp;
		++cnt;
		for(auto x:e[k]){
			int go=x.fi,w=x.se;
			if(!vis[go] && dis[go]>w){
				dis[go]=w;
				q.push(mk(dis[go],go));
			}
		}
	}
	if(cnt==n) printf("%d\n",ans);
	else printf("orz\n");
	return 0;
}
