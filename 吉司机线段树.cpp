/*************************************************************************
	> File Name: 吉司机线段树.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: hdu5306
	> Created Time: 2020/10/14 17:22:39
	> Summery:
	操作0：区间[x,y]对z求min
	操作1：问区间[x,y]的最大值
	操作2：问区间[x,y]的和
 ************************************************************************/
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define pb push_back
#define pr pair<int,int>
#define fi first
#define se second
#define LL long long
#define ls (node<<1)
#define rs (node<<1|1)
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=1e6+10;
int n,m,a[maxx<<2],mx[maxx<<2],se[maxx<<2],cnt[maxx<<2];
LL sum[maxx<<2];
void push_up(int node){
	sum[node]=sum[ls]+sum[rs];
	if(mx[ls]<mx[rs]){
		mx[node]=mx[rs];
		se[node]=max(se[rs],mx[ls]);
		cnt[node]=cnt[rs];
	}
	else if(mx[ls]>mx[rs]){
		mx[node]=mx[ls];
		se[node]=max(se[ls],mx[rs]);
		cnt[node]=cnt[ls];
	}
	else{
		mx[node]=mx[ls];
		cnt[node]=cnt[ls]+cnt[rs];
		se[node]=max(se[ls],se[rs]);
	}
}
void build(int node ,int l, int r){
	if(l>=r){
		se[node]=-1;
		cnt[node]=1;
		sum[node]=mx[node]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid); build(rs,mid+1,r);
	push_up(node);
}
void cals(int node,int v){
	if(v>=mx[node]) return ;
	sum[node]-=1ll*(mx[node]-v)*cnt[node];
	mx[node]=v;
}
void push_down(int node){
	cals(ls,mx[node]);
	cals(rs,mx[node]);
}
void update(int node,int l,int r,int ul,int ur,int v){
	if(mx[node]<=v) return;
	if(l==ul && r==ur && v>se[node]){
		cals(node,v);
		return ;
	}
	push_down(node);
	int mid=(l+r)>>1;
	if(ur<=mid) update(ls,l,mid,ul,ur,v);
	else if(ul>mid) update(rs,mid+1,r,ul,ur,v);
	else update(ls,l,mid,ul,mid,v), update(rs,mid+1,r,mid+1,ur,v);
	push_up(node);
}
LL query(int node,int l,int r,int ul,int ur,bool op){
	if(l==ul && r==ur) return op?sum[node]:mx[node];
	push_down(node);
	int mid=(l+r)>>1;
	if(ur<=mid) return query(ls,l,mid,ul,ur,op);
	else if(ul>mid) return query(rs,mid+1,r,ul,ur,op);
	else{
		if(op) return query(ls,l,mid,ul,mid,op)+query(rs,mid+1,r,mid+1,ur,op);
		else return max(query(ls,l,mid,ul,mid,op),query(rs,mid+1,r,mid+1,ur,op));
	}
}

void solve(){
	int u,x,y,z;
	n=read(); m=read();
	For(i,1,n) a[i]=read();
	build(1,1,n);
	For(i,1,m){
		u=read(); x=read(); y=read();
		if(!u) z=read(), update(1,1,n,x,y,z);
		else printf("%lld\n",query(1,1,n,x,y,u-1));
	}
		
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read();
	while(T--) solve();
	return 0;
}
