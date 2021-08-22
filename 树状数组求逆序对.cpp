#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=99999997;
struct node{
    long long num;
    int id;
};
node a[100010],b[100010];
int match[100010],c[100010],n,ans=0;
int lowbit(int x){
	return x&(-x);
}
void add(int x){
	while(x<=n){
		c[x]++;
		x+=lowbit(x);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",c[i]);
	printf("\n");
}
void sum(int x){
	int tmp=x;
	while(x>0){
		ans=(ans+c[x])%mod;
		x-=lowbit(x);
	}
		printf("%d~%d\n",tmp,ans);
	add(tmp);
}


bool cmp(node a,node b){
    return a.num<b.num;
}
long long read(){
    char x;
    while((x=getchar())>'9' || x<'0');
    int u=x-'0';
    while((x=getchar())<= '9' && x>= '0')u=u*10+x-'0';
    return u;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,m,x;
    n=read();
    for(i=1;i<=n;i++){
        a[i].num=read();
        a[i].id=i;
    }
    for(i=1;i<=n;i++){
        b[i].num=read();
        b[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    for(i=1;i<=n;i++)
        match[a[i].id]=b[i].id;	
    for(i=n;i>=1;i--){
		printf("%d\n",match[i]);
		sum(match[i]);
	}
    printf("%d",ans); 
return 0;
}
