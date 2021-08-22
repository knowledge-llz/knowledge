/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/7/30 20:32:25
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
const int maxx=5e5+10;
struct node{
	int id,dis;
	bool operator <(const node &A)const{
		return A.dis<dis;
	}
};
priority_queue<node>q;
int n,m,s,e=0,be[maxx],to[maxx],ne[maxx],w[maxx],dis[maxx];
bool vis[maxx];
void add(int x,int y,int c){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
	w[e]=c;
}
void dijsktra(){
	q.push((node){s,0});
	while(!q.empty()){
		int x=q.top().id;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=be[x];i;i=ne[i]){
			int go=to[i];
			if(!vis[go] && dis[go]>dis[x]+w[i]){
				dis[go]=dis[x]+w[i];
				q.push((node){go,dis[go]});
			}
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int u,v,c;
	n=read(); m=read(); s=read();
	For(i,1,m){
		u=read(); v=read(); c=read();
		add(u,v,c);
	}
	memset(dis,127,sizeof(dis));
	dis[s]=0;
	dijsktra();
	For(i,1,n) printf("%d ",dis[i]);
	return 0;
}
