/*************************************************************************
    > Author: LLZ-cnyali
    > Created Time: 2017/4/28 20:35:56
 ************************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int fa[5010],size[5010],ans;
struct node{
	int x,y,z;
}road[200001];
bool cmp(node a,node b){
	return a.z<b.z;
}
int find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
void mix(int a,int b){
	int x=find(a),y=find(b);
	if(size[x]<size[y]){
		fa[x]=y;
		size[y]+=size[x];
	}
	else {
		fa[y]=x;
		size[x]+=size[y];
	}
}
int main(){
	int i,j,k=0,m,n;
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)fa[i]=i;
	for(i=1;i<=m;i++)
		scanf("%d%d%d",&road[i].x,&road[i].y,&road[i].z);
	
	sort(road+1,road+m+1,cmp);
	for(i=1;i<=m,k<n-1;i++){
		if( find(road[i].x)!=find(road[i].y) ){
			printf("%d %d %d\n",road[i].x,road[i].y,road[i].z);
			mix( road[i].x , road[i].y);
			ans+=road[i].z;
			k++;
		}
	}
	printf("%d",ans);
    return 0;
}
