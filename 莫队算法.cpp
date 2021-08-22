/*************************************************************************
	> File Name: 3.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/SP3267
	> Created Time: 2020/9/11 10:40:23
	> 对于一段序列，有q次询问，每次询问区间[l,r]有多少个不同的数字。
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
const int maxx=1e6+10;
int n,m,sz,num,a[maxx],c[maxx],cnt[maxx],ans[maxx];
struct node{
	int id,l,r;
	void get(int x){
		id=x;
		l=read();
		r=read();
	}
}q[maxx];
bool cmp(node x,node y){
	return (c[x.l]^c[y.l])? c[x.l]<c[y.l] : ((c[x.l]&1) ? x.r<y.r : x.r>y.r);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read();
	sz=sqrt(n);
	num=ceil((double)n/sz);
	For(i,1,n){
		a[i]=read();
		c[i]=(i-1)/sz+1;
	}
	m=read();
	For(i,1,m) q[i].get(i);
	sort(q+1,q+m+1,cmp);
	int l=1,r=0,now=0;
	For(i,1,m){
		int ql=q[i].l, qr=q[i].r;
		while(l<ql) now -= !--cnt[a[l++]];
		while(l>ql) now += !cnt[a[--l]]++;
		while(r<qr) now += !cnt[a[++r]]++;
		while(r>qr) now -= !--cnt[a[r--]];
		ans[q[i].id]=now;
	}
	For(i,1,m)	printf("%d\n",ans[i]);
	return 0;
}
