#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
using namespace std;
int map[5001][5001],dis[5001]; 
bool p[5001];
int main(){
#ifndef ONLINE_JUDGE
	freopen("prim.in","r",stdin);
	freopen("prim.out","w",stdout);
#endif	
	int i,j,k,m,n,a,b,c,flag;
	scanf("%d%d",&n,&m);
	memset(map,127,sizeof(map));
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		map[a][b]=min(map[a][b],c);
		map[b][a]=min(c,map[b][a]);
	}
	memset(dis,127,sizeof(dis));
	dis[1]=0;
	for(int _=1;_<=n;_++){
		k=0;
		for(j=1;j<=n;j++)
			if(!p[j] && dis[j]<dis[k])
				k=j;
		if(!k)flag=1;
		p[k]=1;
		for(j=1;j<=n;j++)
			if(!p[j] && map[k][j]<dis[j] )
				dis[j]=map[k][j];
	}
	if(!flag){
		for(i=1;i<=n;i++)
			flag+=dis[i];
		printf("%d\n",flag);
	}
	else printf("orz\n");
		return 0;
}
