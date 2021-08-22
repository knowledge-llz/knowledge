queue<int>q;
bool p[maxx];
bool SPFA(){
	For(i,0,n){ dis[i]=inf;  num[i]=p[i]=0; }
	while(!q.empty()) q.pop();
	dis[0]=0; p[0]=1; 
	q.push(0);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		p[now]=0;
		for(int i=be[now];i;i=ne[i]){
			int go=to[i];
			if(dis[go]>dis[now]+w[i]){
				dis[go]=dis[now]+w[i];
				if(!p[go]){
					if(num[go]>n) return 0;
					q.push(go);
					num[go]++;
					p[go]=1;
				}
			}
		}
	}
	return 1;
}


#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int mod=1e9+7; 
const int inf=0x7fffffff; 
int dis[2501],p[2501],begin[2501],to[2501*20],w[2501*20],next[2501*20],q[2501*5],ti[2501];
int u,v,e,c,ans;
void add(int u,int v,int c){
	to[++e]=v;
	next[e]=begin[u];
	begin[u]=e;
	w[e]=c;
}	
int main(){
	int i,j,k,m,n,T,f=0,l=1;
	scanf("%d%d%d",&n,&m,&T);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&c);
		add(u,v,c);	
		add(v,u,c);
	}
	for(i=2;i<=n;i++)dis[i]=inf;
	q[1]=1;p[1]=1;
	while(f<l){
		f++;
		k=q[f];p[k]=0;
		for(i=begin[k];i;i=next[i]){
			int go=to[i];
			if(dis[go]>dis[k]+w[i]){
				dis[go]=dis[k]+w[i];
				if(!p[go]){
					q[++l]=go;
					p[go]=1;
				}
			}
		}
	}
		for(i=2;i<=n;i++)ans=(ans+dis[i])%mod;
		printf("%d",ans);
	return 0;
}
/*
5 6 0
1 2 1
2 3 2
1 5 1
1 3 2
1 4 4
3 4 1
*/
