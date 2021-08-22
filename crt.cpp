/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/P1495
	> Created Time: 2021/3/13 18:13:09
 ************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
LL read(){
	char x=getchar(); LL u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=2e5+10;
LL n,m[maxx],a[maxx],M=1,ans=0;
void exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) { x = 1; y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read();
	For(i,1,n){
		m[i]=read();
		a[i]=read();
		M*=m[i];
	}
	For(i,1,n){
		LL Mi=M/m[i],x,y;
		exgcd(Mi,m[i],x,y);
		ans+=a[i]*Mi*(x<0?x+m[i]:x);
	}
	printf("%lld\n",ans%M);
	return 0;
}
