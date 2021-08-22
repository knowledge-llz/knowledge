#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int a[1000][1000];
int main(){
	int i,j,k,m,n,x,y;
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y,&k);
		a[x][y]=k;
		a[y][x]=k;
	}
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(a[i][j]>a[i][k]+a[k][j])
					a[i][j]=a[i][k]+a[k][j];
	
	return 0;
}

