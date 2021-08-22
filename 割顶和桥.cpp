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
const int maxx=2e6+10;
int n,m,cnt,to[maxx],be[2020],ne[maxx],e=1,w[maxx],dfn[2020],ans;
bool vis[maxx];
void add(int x,int y,int z){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	w[e]=z;
}
//求权值最小的桥
int dfs(int u){
	dfn[u]=++cnt;
	int lowu=cnt;
	for(int i=be[u];i;i=ne[i]){
		if(vis[i]) continue;
		vis[i]=vis[i^1]=1;
		int v=to[i];
		if(!dfn[v]){
			int lowv=dfs(v);
			lowu=min(lowu,lowv);
			if(lowv>dfn[u]) ans=min(ans,w[i]);
		}
		else lowu=min(lowu,dfn[v]);
	}
	return lowu;
}
//求割顶
bool iscut[maxx]
int dfs(int u,int fa){
	dfn[u]=++cnt;
	int lowu=cnt,ch=0;
	for(int i=be[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa) continue;
		if(!dfn[v]){
			++ch;
			int lowv=dfs(v,u);
			lowu=min(lowu,lowv);
			if(lowv>=dfn[u]) iscut[u]=1;
		}
		else lowu=min(lowu,dfn[v]);
	}
	if(fa<0 && ch==1) iscut[u]=0;
	low[u]=lowu;
	return lowu;
}

