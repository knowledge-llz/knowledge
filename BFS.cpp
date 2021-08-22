#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int num[1000001],go[1000001],p[1000001];
double lmy;
int main(){
	int i,j,k,m,n,s,f=0,l=1;
	scanf("%d%d",&n,&s);
	lmy=abs(n-s)*0.5;
	go[1]=n;p[n]=1;
	while(f<l){
		f++;
		int now=go[f];
		if(now==s){break;}
		if(!p[now+1]&&now<s){
			go[++l]=now+1;
			num[now+1]=num[now]+1;
			p[now+1]=1;
			if(now+1==s){break;}
		}
		if(!p[now-1]&&now>1){
			go[++l]=now-1;
			num[now-1]=num[now]+1;
			p[now-1]=1;
			if(now-1==s){break;}
		}
		if(!p[now*2]&&now<s){
			go[++l]=now*2;
			num[now*2]=num[now]+1;
			p[now*2]=1;
			if(now*2==s){break;}
		}
	}
	printf("%d\n",num[s]);
	if(num[s]<lmy)printf("hh\n");
	else if(num[s]>lmy)printf("ljf\n");
	else printf("draw\n");
	return 0;
}
