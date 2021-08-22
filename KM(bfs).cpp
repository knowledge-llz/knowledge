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
int n,m,matchy[520],pre[520],matchx[520];
LL g[520][520],lx[520],ly[520],slack[520];
bool visx[520],visy[520];
queue<int>q;
bool ok(int y){
	visy[y]=1;
	if(matchy[y]){ q.push(matchy[y]); return 0; }
	while(y){ matchy[y]=pre[y]; swap(matchx[pre[y]],y); }
	return 1;
}
bool bfs(){
	while(!q.empty()){
		int x=q.front(); q.pop();
		if(visx[x]) continue;
		visx[x]=1;
		for(int y=1;y<=n;++y){
			if(visy[y]) continue;
			LL tmp=lx[x]+ly[y]-g[x][y];
			if(tmp<slack[y]){
				slack[y]=tmp;
				pre[y]=x;
				if(!tmp && ok(y)) return true;
			}
		}
	}
	LL delta=inf;
	for(int y=1;y<=n;++y) if(!visy[y]) delta=min(delta,slack[y]);
	for(int i=1;i<=n;++i){
		if(visx[i]) lx[i]-=delta;
		if(visy[i]) ly[i]+=delta;
		else slack[i]-=delta;
	}
	for(int y=1;y<=n;++y)
		if(!visy[y] && !slack[y] && ok(y))
			return true;
	return false;
}

LL KM(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){ slack[j]=inf; visx[j]=visy[j]=0; }
		while(!q.empty()) q.pop();
		q.push(i);
		while(!bfs());
	}
	LL ans=0;
	for(int y=1;y<=n;++y) ans+=g[matchy[y]][y];
	return ans;
}
			
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	scanf("%d%d",&n,&m);
	For(i,1,n) For(j,1,n) g[i][j]=-inf;
	for(int i=1;i<=n;++i) lx[i]=-inf;
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		g[u][v]=read();
		lx[u]=max(g[u][v],lx[u]);
	}
	printf("%lld\n",KM());
	for(int i=1;i<=n;++i) printf("%d ",matchy[i]);
	return 0;
}
