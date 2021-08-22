//https://www.luogu.com.cn/problem/P3834
//求区间第k小
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxx=2000010;
int a[maxx], s[maxx], len, cnt=0;
int ls[maxx<<1], rs[maxx<<1], rt[maxx<<1], w[maxx<<1];
int read(){
    char x;
    while((x=getchar())<'0' || x>'9');
    int u=x-'0';
    while((x=getchar())>='0' && x<='9') u= u*10+x-'0';
    return u;
}
void insert(int &q, int pre, int l, int r, int x){
    q=++cnt; ls[q]=ls[pre]; rs[q]=rs[pre]; w[q]=w[pre]+1;
    if(l!=r){
        int mid = (l + r) >> 1;
        if(x <= mid) insert(ls[q], ls[pre], l, mid, x);
        else insert(rs[q], rs[pre], mid+1, r, x);
    }
}
int query(int ll, int rr, int l, int  r, int k){
    if(l == r) return l;
    int mid= (l+r) >> 1;
    int num = w[ls[rr]] - w[ls[ll]];
    if(num >= k) query(ls[ll], ls[rr], l ,mid, k);
    else query(rs[ll], rs[rr], mid + 1, r, k-num);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,n,m,l,r;
    n=read(); m=read();
    For(i,1,n) a[i] = s[i] = read();
    sort(s + 1,s + n + 1);
    For(i,1,n)
        insert(rt[i],rt[i-1],1,n,lower_bound(s+1,s+1+n,a[i])-s);
    For(i,1,m){
        l=read(); r=read(); k=read();
        printf("%d\n",s[query(rt[l-1], rt[r], 1, n, k)]);
    }
    return 0;
}
