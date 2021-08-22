#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
using namespace std;
const double pi=acos(-1);
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
struct node{
	double x,y;
	node(double X=0,double Y=0){x=X,y=Y;}
	node operator +(node const  &b){
		return node(x+b.x,y+b.y);
	}
	node operator -(node const &b){
		return node(x-b.x,y-b.y);
	}
	node operator *(node const &b){
		return node(x*b.x-y*b.y,x*b.y+y*b.x);
	}
}f[1<<22|1],g[1<<22|1];
int n,m,dp[1<<22|1];
void fft(node *f,bool idft){
	For(i,1,n-1)
		if(i<dp[i])
			swap(f[i],f[dp[i]]);
	
	for(int i=2;i<=n;i<<=1){
		node w(cos(2*pi/i),sin(2*pi/i));//p(1,0);
		int len=i>>1;
		if(idft) w.y=-w.y;
		for(int k=0;k<n;k+=i){
			node p(1,0);
			for(int l=k;l<k+len;l++){
				node tmp=p*f[len+l];
				f[len+l]=f[l]-tmp;
				f[l]=f[l]+tmp;
				p=p*w;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	n=read(),m=read();
	For(i,0,n) f[i].x=read();
	For(i,0,m) g[i].x=read();
	for(m+=n,n=1;n<=m;n<<=1);
	For(i,1,n-1)
		dp[i]=(dp[i>>1]>>1)|((i&1)?n>>1:0);
	
	fft(f,0);	fft(g,0);
	For(i,0,n-1) f[i]=f[i]*g[i];
	fft(f,1);
	For(i,0,m) printf("%d ",(int)(f[i].x/n+0.5));
	return 0;
}
