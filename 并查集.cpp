#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int fa[200010],size[200010];
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void mix(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return ;
	if(size[x] < size[y]) fa[x] = y, size[y] += size[x];
	else fa[y] = x, size[x] += size[y];
}

int main(){
	int i,j,k,m,n,a,b,p;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) fa[i]=i,size[i]=1;
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&p,&a,&b);
		if(p==1)mix(a,b);
		else cout<<((find(a) == find(b)) ? 'Y' : 'N')<<endl;
	}
	return 0;
}

