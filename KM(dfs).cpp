
/*************************************************************************
    > File Name: 2.cpp
    > Author: Knowledge-Pig
    > Mail: 925538513@qq.com
    > Blog: https://www.cnblogs.com/Knowledge-Pig/
    > Created Time: 2021年08月07日 星期六 22时43分20秒
************************************************************************/

#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const LL inf=1e16+7;
int n,m,match[520],fa[2021];
LL g[520][520],lx[520],ly[520],slack[520];
bool visx[520],visy[520];
int findpath(int x){
	visx[x]=1;
	for(int y=1;y<=n;++y){
		if(visy[y]) continue;
		LL tmp=(lx[x]+ly[y]-g[x][y]);
		if(!tmp){
			visy[y]=1;
			fa[y+n]=x;
			if(!match[y]) return y+n;
			fa[match[y]]=y+n;
			int leaf=findpath(match[y]);
			if(leaf) return leaf;
		}
		else slack[x]=min(slack[x],tmp);
	}
	return 0;
}
void solve(){
	LL delta=inf;
	for(int i=1;i<=n;++i) delta=min(delta,slack[i]);
	for(int i=1;i<=n;++i){
		if(visx[i]) lx[i]-=delta, slack[i]-=delta;
		if(visy[i]) ly[i]+=delta;
	}
}

LL KM(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) slack[j]=inf, visx[j]=visy[j]=0;
		for(int j=1;j<=n+n;++j) fa[j]=0;
		int leaf=findpath(i);
		if(leaf>0){ match[leaf-n]=i; continue; }
		else solve();
		while(1){
			for(int j=1;j<=n;++j){
				if(!slack[j]){
					slack[j]=inf;
					leaf=findpath(j);
					if(leaf>0) break;
				}
			}
			if(leaf>0){
				while(leaf){
					match[leaf-n]=fa[leaf];
					leaf=fa[fa[leaf]];
				}
				break;
			}
			else solve();
		}
	}
	LL ans=0;
	for(int y=1;y<=n;++y) ans+=g[match[y]][y];
	return ans;
}
			
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); m=read();
	For(i,1,n) For(j,1,n) g[i][j]=-inf;
	for(int i=1;i<=n;++i) lx[i]=-inf;
	for(int i=1;i<=m;++i){
		int u=read(), v=read();
		g[u][v]=read();
		lx[u]=max(g[u][v],lx[u]);
	}
	printf("%lld\n",KM());
	for(int i=1;i<=n;++i) printf("%d ",match[i]);
	return 0;
}
