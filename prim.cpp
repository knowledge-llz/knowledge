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
int n,m,to[maxx<<1],ne[maxx<<1],be[maxx<<1],w[maxx<<1],dis[maxx],e=0,ans=0,cnt=0;
bool vis[maxx];
priority_queue<pr,vector<pr>,greater<pr> >q;
void add(int x,int y,int z){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	w[e]=z;
}
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
		add(u,v,c); add(v,u,c);
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
		for(int i=be[k];i;i=ne[i]){
			int go=to[i];
			if(!vis[go] && dis[go]>w[i]){
				dis[go]=w[i];
				q.push(make_pair(dis[go],go));
			}
		}
	}
	if(cnt==n) printf("%d\n",ans);
	else printf("orz\n");
	return 0;
}
