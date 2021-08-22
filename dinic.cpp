/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/7/18 10:40:17
 ************************************************************************/
#include<queue>
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
const int maxx=2020,inf=1e9+7;
int be[250],now[250],to[maxx],ne[maxx],w[maxx],dep[250],e=1,n,m,s,t;
void add(int x,int y,int z){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	w[e]=z;
}
void init(){
	For(i,1,e) to[i]=ne[i]=w[i]=0;
	For(i,1,n) be[i]=0;
	e=1;
}
bool bfs(){
	queue<int>q;
	q.push(s);
	For(i,1,n) dep[i]=0;
	dep[s]=1; now[s]=be[s];
	while(!q.empty()){
		int id=q.front();
		q.pop();
		for(int i=be[id];i;i=ne[i]){
			int go=to[i];
			if(!dep[go] && w[i]>0){
				dep[go]=dep[id]+1;
				now[go]=be[go];
				q.push(go);
			}
		}
	}
	return !dep[t]?0:1;
}
int dfs(int id,int mini){
	if(id==t || !mini) return mini;
	int flow,ret=0;
	for(int &i=now[id];i;i=ne[i]){			//&当前弧优化：已经增广的路径之后不走了
		int go=to[i];
		if(w[i]>0 && dep[go]==dep[id]+1 && (flow=dfs(go,min(w[i],mini))) ){
			if(!flow) dep[go]=inf;			//已经满流的点删除，之后不走了
			w[i]-=flow;
			w[i^1]+=flow;
			ret+=flow;
			mini-=flow;
		}
		if(!mini) return ret;
	}
	return ret;
}

int dinic(){
	int ans=0,tmp;
	while(bfs()){
		tmp=dfs(s,inf);
		if(!tmp) break;
		ans+=tmp;
	}
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read(),u,v,c;
	while(T--){
		n=read(); m=read();
		s=read(); t=read();
		init();
		For(i,1,m){
			u=read(); v=read(); c=read();
			add(u,v,c);  add(v,u,0);
		}
		printf("%d\n",dinic());
	}
	return 0;
}
