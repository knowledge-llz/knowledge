/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> https://www.luogu.com.cn/problem/SP10707
	> Created Time: 2020/9/18 22:35:50
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
const int maxx=3e5+10;
int n,m,tot,discrete[maxx],be[maxx],to[maxx],ne[maxx],e=0;
int ord[maxx],fir[maxx],lst[maxx],belong[maxx],discret[maxx],ncnt=0,now=0;
int fa[maxx],son[maxx],sz[maxx],jump[maxx],deep[maxx],cnt[maxx],val[maxx],ans[maxx];
bool vis[maxx];
struct node{
	int l,r,id,lca;
}q[maxx];
void add(int x,int y,bool type){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	if(type) add(y,x,0);
}
void Swap(int &x,int &y){x^=y;y^=x;x^=y;}
int dfs(int id){
	ord[++ncnt]=id;
	fir[id]=ncnt;
	sz[id]=1;
	for(int i=be[id];i;i=ne[i]){
		int go=to[i];
		if(go==fa[id]) continue;
		deep[go]=deep[id]+1;
		fa[go]=id;
		sz[id]+=dfs(go);
		if(!son[id] || sz[go]>sz[son[id]])
		    son[id]=go;
	}
	ord[++ncnt]=id;
	lst[id]=ncnt;
	return sz[id];
}
void get_jump(int id,int top){
	jump[id]=top;
	if(son[id]) get_jump(son[id],top);
	for(int i=be[id];i;i=ne[i]){
		int go=to[i];
		if(go==fa[id] || go==son[id]) continue;
		get_jump(go,go);
	}
}
int query(int x,int y){
	while(jump[x]!=jump[y]){
		if(deep[jump[x]]>deep[jump[y]]) Swap(x,y);
		y=fa[jump[y]];
	}
	return deep[x]>deep[y]?y:x;
}
bool cmp(node a,node b){
	return (belong[a.l]^belong[b.l]) ? (belong[a.l]<belong[b.l]) :((belong[a.l]&1) ? a.r<b.r : a.r>b.r);
}
void work(int x){
	vis[x] ? now -= !--cnt[val[x]] : now += !cnt[val[x]]++;
	vis[x] ^= 1;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int u=1,v=2;
	n=read(); m=read();
	For(i,1,n) val[i]=discret[i]=read();
	sort(discret+1,discret+n+1);
	int tot=unique(discret+1,discret+n+1)-discret-1;
	For(i,1,n) val[i]=lower_bound(discret+1,discret+tot+1,val[i])-discret;
	For(i,1,n-1) add(read(),read(),1);
	dfs(1);
	get_jump(1,1);
	v=sqrt(ncnt);
	For(i,1,ncnt) belong[i]=(i-1)/v+1;
	For(i,1,m){
		u=read(); v=read(); 
		int lca=query(u,v);
		if(fir[u]>fir[v]) Swap(u,v);
		if(u==lca){
			q[i].l=fir[u];
			q[i].r=fir[v];
		}
		else{
			q[i].l=lst[u];
			q[i].r=fir[v];
			q[i].lca=lca;
		}
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	For(i,1,m){
		int ql=q[i].l,qr=q[i].r,lca=q[i].lca;
		while(l < ql) work(ord[l++]);
		while(l > ql) work(ord[--l]);
		while(r < qr) work(ord[++r]);
		while(r > qr) work(ord[r--]);
		if(lca) work(lca);
		ans[q[i].id]=now;
		if(lca) work(lca);
	}
	For(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
