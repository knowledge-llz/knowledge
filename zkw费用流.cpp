#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdlib>
#define pb push_back
#define pf push_front
#define popf pop_front
#define For(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
const int oo=1061109567;
const int maxx=50010;
int w[maxx<<1],c[maxx<<1],be[maxx/10],ne[maxx<<1],to[maxx<<1],e=0,s,t,m,n;
int dis[maxx/10],money=0,flow=0;
bool vis[maxx/10];
void add(int x,int y,int z,int cost){
	to[e]=y;
	ne[e]=be[x];
	be[x]=e;
	c[e]=z;
	w[e]=cost;
	e++;
}
bool bfs(){
		deque<int> q;
		int sum=0,cnt=1;
		memset(dis,63,sizeof(dis));
		memset(vis,0,sizeof(vis));
		q.pb(t);
		dis[t]=0;	vis[t]=1;
		while(!q.empty()){
			int now=q.front();
			printf("%d\n",now);
			q.popf();
			//lll优化
			if(dis[now]*cnt>sum){
				q.pb(now);
				continue;
			}
			sum-=dis[now]; cnt--;
			for(int i=be[now];i!=-1;i=ne[i]){
				int go=to[i];
				if(c[i^1]  && dis[go]>dis[now]-w[i]){
					dis[go]=dis[now]-w[i];
					if(!vis[go]){
						vis[go]=1;
						//slf优化
						if(!q.empty() && dis[go]<dis[q.front()]) q.pf(go);
						else q.pb(go);
						sum+=dis[go]; cnt++;
					}
				}
			}
			vis[now]=0;
		}
		printf("%d\n",dis[s]);
		return dis[s]<oo;
	}
int dfs(int id,int flow){
	if(!flow || id==t) return flow;
	int ret=0;
	for(int i=be[id];i!=-1;i=ne[i]){
		int go=to[i],k;
		if(c[i] && dis[go]==dis[id]-w[i] && (k=dfs(go,min(flow,c[i])))){
			c[i]-=k;
			c[i^1]+=k;
			money+=k*w[i];
			ret+=k;
			flow-=k;
		}
		if(!flow) return ret;
	}
	return ret;
}
void zkw(){
	while(bfs()){
//		printf("1\n");
		while(1){
			int tmp=dfs(s,oo);
			if(!tmp) break;
			flow+=tmp;
		}
	}
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
	memset(be,-1,sizeof(be));
	int u,v,i,j;
	n=read(); m=read(); s=read(); t=read();
	For(_,1,m){
		u=read(); v=read(); i=read(); j=read();
		add(u,v,i,j);
		add(v,u,0,-j);
	}
	zkw();
	printf("%d %d\n",money,flow);
	return 0;
}
