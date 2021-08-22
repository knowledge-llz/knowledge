
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<cmath>  
#include<cstring>  
#include<algorithm>  
using namespace std;
int g[1010][1010],d[1010],n,m;
bool p[1010];
int read(){
	char x;
	while((x=getchar())<'0' || x>'9');
	int u=x-'0';
	while((x=getchar())>='0'&& x<='9')	u=u*10+x-'0';
	return u;
}
bool dfs(int x){
	for(int u=1;u<=m;u++)
		if(g[x][u] && !p[u]){
			p[u]=1;
			if(!d[u] ||dfs(d[u])){
				d[u]= x;
				return 1;
		}
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
freopen("input.in","r",stdin);
freopen("output.out","w",stdout);
#endif
	int i,j,k,e;
	n=read();
	m=read();
	e=read();
	for(int u=1;u<=e;u++){
		i=read();
		j=read();
		if(j<=m)g[i][j]=1;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)p[j]=0;
		dfs(i);
	}
	int ans=0;
	for(i=1;i<=m;i++)
		if(d[i])ans++;
	printf("%d\n",ans);

return 0;
}
			
