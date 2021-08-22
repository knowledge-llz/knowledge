#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
const int maxx=500010;
int be[maxx],ne[maxx*2],to[maxx*2],e=0;
int deep[maxx],f[maxx][19],n,q,root,lim;
bool p[maxx];
void add(int x,int y){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
}
int read(){
	char c;
	while((c=getchar())<'0' || c>'9');
	int u=c-'0';
	while((c=getchar())>='0' && c<='9')u=u*10+c-'0';
	return u;
}
void build(int x){
	for(int i=be[x];i;i=ne[i]){
		int go=to[i];
		if(!p[go]){
			p[go]=1;
			deep[go]=deep[x]+1;
			lim=max(lim,deep[go]);
			f[go][0]=x;
			build(go);
		}
	}
}
void work(){
	for(int i=1;i<=lim;i++)
		for(int j=1;j<=n;j++){
			f[j][i]=f[f[j][i-1]][i-1];
//	printf("%d~%d~%d\n",j,i,f[j][i]);
		}
}
void lca(int x,int y){
	if(deep[x]>deep[y])swap(x,y);
	for(int i=lim;i>=0;i--)
		if(deep[f[y][i]]>=deep[x])
			y=f[y][i];
	if(x==y)printf("%d\n",x);
	else{
//		printf("x=%d~y=%d\n",x,y);
		for(int i=lim;i>=0;i--)
			if(f[x][i]!=f[y][i])
				x=f[x][i],y=f[y][i];
	printf("%d\n",f[x][0]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
#endif
	int i,j,k,m;
	n=read();
	q=read();
	root=read();
	for(i=1;i<n;i++){
		j=read();
		k=read();
		add(j,k);
		add(k,j);
	}
	deep[root]=1;
	p[root]=1;
	build(root);
//	for(i=1;i<=n;i++)	printf("%d~0~%d\n",i,f[i][0]);
	lim=log(lim)/log(2);
//	cout<<lim<<"$"<<endl;
	work();
	while(q--){
		j=read();
		k=read();
		lca(j,k);
	}
return 0;
}
