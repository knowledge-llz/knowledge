/*************************************************************************
	> File Name: 3.cpp
	> Blog: http://121.48.165.90/problem/sui-ji-shu-zhang-wo-zai-wo-shou-zhong/description
	> Created Time: 2021/5/25 16:48:20
	> [L,R]包含135，42的数的个数。
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
const int mod=998244353;
char l[2021],r[2021],c[2021];
int len;
LL L,R,dp[2021][5];
LL calc(char *s){
	int slen=strlen(s); LL tmp=0;
	for(int i=0;i<slen;++i) tmp=(tmp*10%mod+(s[i]^'0'))%mod;
	return tmp;
}
LL dfs(int pos,int pre1,int pre2,bool lim){
	if(pos==len) return 1;
	int st=0;
	if(pre1==1 && pre2==3) st=1;
	if(pre2==1) st=2;
	if(pre2==4) st=3;
	if(!lim && dp[pos][st]!=-1) return dp[pos][st];
	int up= lim ? (c[pos]^48) : 9;
	LL tmp=0;
	for(int i=0;i<=up;++i){
		if(pre1==1 && pre2==3 && i==5) continue;
		if(pre2==4 && i==2) continue;
		tmp=(tmp+dfs(pos+1,pre2,i,lim & (i==c[pos]-'0')))%mod;
	}
	if(!lim) dp[pos][st]=tmp;
	return tmp;
}
LL solve(char *s){
	memset(dp,-1,sizeof(dp));
	len=strlen(s);
	strcpy(c,s);
	return dfs(0,-1,-1,1);
}
bool check(char *s){
	int len=strlen(s);
	for(int i=1;i<len;++i){
		if(s[i-1]=='4' && s[i]=='2') return 0;
		if(i>=2 && s[i-2]=='1' && s[i-1]=='3' && s[i]=='5') return 0;
	}
	return 1;
}
int main()
{
	int T=read();
	while(T--){
		scanf("%s%s",l,r);
		L=calc(l); R=calc(r);
		LL ans=(R-L+1)-(solve(r)-solve(l)+check(l));
		printf("%lld\n",(ans%mod+mod)%mod);
	}
	return 0;
}
