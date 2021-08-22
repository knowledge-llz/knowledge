
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
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
const int maxx=2e5+10;
int n,p[maxx];
LL ans,a[maxx],tr[maxx<<2],sum[maxx],lazy[maxx<<2];
void push_up(int node){
	tr[node]=min(tr[ls],tr[rs]);
}
void push_down(int node){
	if(!lazy[node]) return;
	tr[ls]+=lazy[node];
	tr[rs]+=lazy[node];
	lazy[ls]+=lazy[node];
	lazy[rs]+=lazy[node];
	lazy[node]=0;
}
void build(int node,int l,int r){
	if(l>=r){
		if(l<p[1]) tr[node]=sum[l]+a[1];
		else tr[node]=sum[l]-a[1];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(node);
}
void update(int node,int l,int r,int ul,int ur,LL x){
	if(ul<=l && ur>=r){
		tr[node]+=x;
		lazy[node]+=x;
		return;
	}
	push_down(node);
	int mid=(l+r)>>1;
	if(ur<=mid) update(ls,l,mid,ul,ur,x);
	else if(ul>mid) update(rs,mid+1,r,ul,ur,x);
	else{
		update(ls,l,mid,ul,mid,x);
		update(rs,mid+1,r,mid+1,ur,x);
	}
	push_up(node);
}
LL query(int node,int l,int r,int ul,int ur){
	if(ul<=l && ur>=r)  return tr[node];
	push_down(node);
	int mid=(l+r)>>1;
	if(ur<=mid) return query(ls,l,mid,ul,ur);
	else if(ul>mid) return query(rs,mid+1,r,ul,ur);
	else return min(query(ls,l,mid,ul,mid),query(rs,mid+1,r,mid+1,ur));
}

