#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int x,n,t;
bool ans,f[4010][4010];

void updatey(int p,int q,int l,int r,int y1,int y2){
	if(y1==l&&y2==r){
		f[p][q]^=1;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=y2)
		updatey(p,q<<1,l,mid,y1,y2);
	else if(mid<y1)
		updatey(p,q<<1|1,mid+1,r,y1,y2);
	else{
		updatey(p,q<<1,l,mid,y1,mid);
		updatey(p,q<<1|1,mid+1,r,mid+1,y2);
	}
}
void updatex(int p,int l,int r,int x1,int y1,int x2,int y2){
	if(x1==l&&x2==r){
		updatey(p,1,1,n,y1,y2);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=x2)
		updatex(p<<1,l,mid,x1,y1,x2,y2);
	else if(mid<x1)
		updatex(p<<1|1,mid+1,r,x1,y1,x2,y2);
	else{
		updatex(p<<1,l,mid,x1,y1,mid,y2);
		updatex(p<<1|1,mid+1,r,mid+1,y1,x2,y2);
	}
}
void queryy(int p,int q,int l,int r,int y){
	ans^=f[p][q];
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(y<=mid)
		queryy(p,q<<1,l,mid,y);
	else
		queryy(p,q<<1|1,mid+1,r,y);
}
void queryx(int p,int l,int r,int x,int y){
	queryy(p,1,1,n,y);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
		queryx(p<<1,l,mid,x,y);
	else
		queryx(p<<1|1,mid+1,r,x,y);
}

int main(){
	scanf("%d",&x);
	while(x--){
		memset(f,0,sizeof(f));
		scanf("%d%d",&n,&t);
		char s[2];
		int x,y,xx,yy;
		for(int tt=t;tt;--tt){
			scanf("%s",s);
			if(s[0]=='C'){
				scanf("%d%d%d%d",&x,&y,&xx,&yy);
				updatex(1,1,n,x,y,xx,yy);
			}
			else{
				ans=0;
				scanf("%d%d",&x,&y);
				queryx(1,1,n,x,y);
				printf("%d\n",ans);
			}
		}
		if(x)puts("");
	}
	return 0;
}
