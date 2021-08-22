/*************************************************************************
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Link: https://www.luogu.com.cn/problem/P2257
	> Created Time: 2021/8/1 16:26:15
	> 求1<=i<=N,1<=j<=M,gcd(i,j)为质数的(i,j)有多少对? 
 ************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=1e7+10;
int mu[maxx],cnt=0;
bool vis[maxx];
LL pri[maxx],sum[maxx];
void get_mu(){
	mu[1]=1;
	for(int i=2;i<=maxx-10;++i){
		if(!vis[i]){
			mu[i]=-1;
			pri[++cnt]=i;
		}
		for(int j=1;j<=cnt && i*pri[j]<maxx;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break;
			else mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=cnt;++i)
		for(int j=pri[i];j<maxx;j+=pri[i])
			sum[j]+=mu[j/pri[i]];
	for(int i=1;i<=maxx-10;++i) sum[i]+=sum[i-1];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read();
	get_mu();
	while(T--){
		int n=read(),m=read();
		LL ans=0;
		if(n>m) swap(n,m);
		for(int l=1,r;l<=n;l=r+1){
			r=min((n/(n/l)),m/(m/l));
			ans+=(sum[r]-sum[l-1])*(m/l)*(n/l);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
