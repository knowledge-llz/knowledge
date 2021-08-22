#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<cstdlib>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define oo 1061109567
using namespace std;
const int maxx=50010;
int w[maxx<<1],f[maxx<<1],c[maxx<<1],be[maxx/10],ne[maxx<<1],to[maxx<<1],e=0,s,t,m,n;
int pre[maxx/10],dis[maxx/10],flag[maxx/10],money=0,flow=0;
bool vis[maxx/10];
void add(int x,int y,int z,int cost){
	to[e]=y;
	ne[e]=be[x];
	be[x]=e;
	c[e]=z;
	w[e]=cost;
	e++;
}
void work(){
	while(1){
		queue<int> q;
		memset(vis,0,sizeof(vis));
		memset(dis,63,sizeof(dis));
		q.push(s);
		dis[s]=0;
		vis[s]=1;
		while(!q.empty()){
			int now=q.front();
			q.pop();
			vis[now]=0;
			for(int i=be[now];i!=-1;i=ne[i]){
				int go=to[i];
				if(c[i]>f[i] && dis[go]>dis[now]+w[i]){
					dis[go]=dis[now]+w[i];
					flag[go]=i;
					pre[go]=now;
					if(!vis[go])vis[go]=1, q.push(go);
				}
			}
		}
		if(dis[t]==oo)break;
		int get=oo;
		for(int i=t;i!=s;i=pre[i]){
			get=min(get,c[flag[i]]-f[flag[i]]);
		}
		for(int i=t;i!=s;i=pre[i]){
			f[flag[i]]+=get;
			f[flag[i]^1]-=get;
		}
//		printf("%d %d\n",dis[t],a[t]);
		money+=dis[t]*get;
		flow+=get;
	}
	return;
}
int read(){
	char x;
	while((x=getchar())<'0' || x>'9');
	int u=x-'0';
	while((x=getchar())>='0' && x<='9') u=u*10+x-'0';
	return u;
	}
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
#endif
	int i,j,k,u,v;
	memset(be,-1,sizeof(be));
	n=read(); m=read(); s=read(); t=read();
	For(u,1,m){
		i=read(); j=read(); k=read(); v=read();
		add(i,j,k,v);
		add(j,i,0,-v);
	}
	work();
	printf("%d %d\n",flow,money);
//	cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
