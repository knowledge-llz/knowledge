/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Problem Source: http://poj.org/problem?id=2987
	> Created Time: 2021/2/4 22:09:21
	> 题目要求最大权闭合子图，输出达到最大权以及达到最大权时最少的点数。
 ************************************************************************/

#include<iostream>
#include<queue>
#include<cstdio>
#include<cstdlib>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
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
const LL maxx=2e5,oo=1e17;
LL n,m,e=1,s,t,ne[maxx],be[maxx],to[maxx];
LL a[maxx],w[maxx],now[maxx],dep[maxx];
bool vis[maxx];
void add(LL x,LL y,LL z){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	w[e]=z;
}
bool bfs(){
	queue<LL>q;
	q.push(s);
	For(i,1,t) dep[i]=0;
	dep[s]=1; now[s]=be[s];
	while(!q.empty()){
		LL u=q.front(); q.pop();
		for(LL i=be[u];i;i=ne[i]){
			LL go=to[i];
			if(!dep[go] && w[i]>0){
				now[go]=be[go];
				dep[go]=dep[u]+1;
				q.push(go);
			}
		}
	}
	return !dep[t]?0:1;
}

LL dfs(LL id, LL mini){
	if(id==t || !mini) return mini;
	LL flow,ret=0;
	for(LL &i=now[id];i;i=ne[i]){
		LL go=to[i];
		if(w[i]>0 && dep[go]==dep[id]+1 && (flow=dfs(go,min(mini,w[i])))){
			if(!flow) dep[go]=maxx;
			w[i]-=flow;
			w[i^1]+=flow;
			mini-=flow;
			ret+=flow;
		}
		if(!mini) return ret;
	}
	return ret;
}


LL dinic(){
	LL ans=0,tmp;
	while(bfs()){
		tmp=dfs(s,oo);
		if(!tmp) return ans;
		ans+=tmp;
	}
	return ans;
}

void dfs(LL id){
	vis[id]=1;
	for(LL i=be[id];i;i=ne[i]){
		LL go=to[i];
		if(w[i]>0 && !vis[go]) dfs(go);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(); m=read();
	s=n+1, t=n+2; LL sum=0;
	For(i,1,n){
		a[i]=read();
		if(a[i]>=0){ add(s,i,a[i]); add(i,s,0); sum+=a[i]; }
		else { add(i,t,-a[i]); add(t,i,0); }
	}
	For(i,1,m){
		LL u=read(),v=read();
		add(u,v,oo); add(v,u,0);
	}
	LL ans=dinic(),num=0;
	dfs(s);
	For(i,1,n)
		if(vis[i]==1)  ++num;
	printf("%lld %lld\n",num,sum-ans);
	return 0;
}
