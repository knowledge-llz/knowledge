/*************************************************************************
	> File Name: 3.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/P1903
	> Created Time: 2020/9/11 22:12:18
	> 对于一个序列，有两种操作：Q:询问[l,r]的不同数的个数；R:改变a[l]为x
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
const int maxx=3e6+10;
int n,m,cntq=0,cntc=0,cnt[maxx],a[maxx],id[maxx],ans[maxx];
struct Q{
	int l,r,t,id;
	void get(){
		l=read();
		r=read();
		id=cntq; t=cntc;
	}
}q[maxx];
struct C{
	int pos,val;
	void get(){ pos=read(); val=read(); }
}c[maxx];
bool cmp(Q x,Q y){
	return (id[x.l]^id[y.l]) ? id[x.l]<id[y.l] : ((id[x.r]^id[y.r]) ? id[x.r]<id[y.r] : x.t<y.t);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); m=read();
	For(i,1,n) a[i]=read();
	For(i,1,m){
		char tmp[10];
		scanf("%s",tmp);
		if(tmp[0]=='Q'){ ++cntq; q[cntq].get(); }
		else if(tmp[0]=='R') c[++cntc].get();
	}
	int sz=pow(n,2.0/3.0);
	For(i,1,n) id[i]=(i-1)/sz+1;
	sort(q+1,q+cntq+1,cmp);
	int l=1,r=0,t=0,now=0;
	For(i,1,cntq){
		int ql = q[i].l, qr = q[i].r, qt = q[i].t;
//		printf("%d %d %d\n",ql,qr,qt);
		while(l < ql) now -= !--cnt[a[l++]];
		while(l > ql) now += !cnt[a[--l]]++;
		while(r < qr) now += !cnt[a[++r]]++;
		while(r > qr) now -= !--cnt[a[r--]];
		while(t < qt){
			++t;
			if(ql<=c[t].pos && c[t].pos<=qr) now-=!--cnt[a[c[t].pos]] - !cnt[c[t].val]++;
			swap(c[t].val,a[c[t].pos]);
		}
		while(t > qt){
			if(ql<=c[t].pos && c[t].pos<=qr) now-=!--cnt[a[c[t].pos]] - !cnt[c[t].val]++;
			swap(c[t].val,a[c[t].pos]);
			--t;
		}
		ans[q[i].id]=now;
	}
	For(i,1,cntq) printf("%d\n",ans[i]);
	return 0;
}
