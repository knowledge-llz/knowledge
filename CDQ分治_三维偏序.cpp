/*************************************************************************
	> File Name: 三维偏序.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/P3810
	> Created Time: 2020/7/30 9:00:29
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
#define lowbit(x) (x&(-x))
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
int n,k,c[maxx],cnt=0,Ans[maxx];
struct node{
	int x,y,z,num,ans;
	void scan(){
		x=read(); y=read(); z=read();
	}
	bool operator ==(const node &A)const{
		if(A.x==x && A.y==y && A.z==z) return 1;
		return 0;
	}
}a[maxx],b[maxx];
void add(int x,int v){
	for(int i=x;i<=k;i+=lowbit(i)) c[i]+=v;
}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)) ans+=c[i];
	return ans;
}
bool cmp(node A,node B){
	if(A.x<B.x) return 1;
	if(A.x>B.x) return 0;
	if(A.y<B.y) return 1;
	if(A.y>B.y) return 0;
	if(A.z<B.z) return 1;
	return 0;
}
bool CMP(node A,node B){
	if(A.y<B.y) return 1;
	if(A.y>B.y) return 0;
	if(A.z<B.z) return 1;
	return 0;
}
void cdq(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	cdq(l,mid); cdq(mid+1,r);
	sort(b+l,b+mid+1,CMP);
	sort(b+mid+1,b+r+1,CMP);
	int i=l,j=mid+1;
	while(i<=mid && j<=r){
		if(b[i].y<=b[j].y) add(b[i].z,b[i].num), i++;
		else b[j].ans+=query(b[j].z), j++;
	}
	while(j<=r) b[j].ans+=query(b[j].z), j++;
	for(int u=l;u<i;++u) add(b[u].z,-b[u].num);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); k=read();
	For(i,1,n) a[i].scan();
	sort(a+1,a+n+1,cmp);
	For(i,1,n){
		int j=1;
		while(i<n && a[i]==a[i+1]){
			++i; ++j;
		}
		b[++cnt]=a[i];
		b[cnt].num=j;
	}
	cdq(1,cnt);
	For(i,1,cnt)
		Ans[b[i].ans+b[i].num-1]+=b[i].num;
	For(i,0,n-1) printf("%d\n",Ans[i]);
	return 0;
}
