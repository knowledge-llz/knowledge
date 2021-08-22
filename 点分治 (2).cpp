#include <cstdio>
#include <algorithm>
#define rep(i,l,r) for (int i=l;i<=r;++i)
#define per(i,r,l) for (int i=r;i>=l;--i)
bool upmax(int &a,const int &b){return a<b?a=b,1:0;}
const int MAX_N=30050;
int getx(){
	char c;int x;
	for (c=getchar();c<'0'||c>'9';c=getchar());
	for (x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
	return x;
}
int n;
int first[MAX_N],next[MAX_N<<2],to[MAX_N<<2];
bool can[MAX_N<<2];
int w[MAX_N],tal=1;
void add(int x,int y){
	next[++tal]=first[x];
	first[x]=tal;
	to[tal]=y;
	can[tal]=true;
}
int ch[MAX_N*32][2],num[MAX_N*32],tot=1;
void insert(int v,int x,int p){
	num[v]++;
	if (p<0) return;
	int i=(x>>p)&1;
	if (!ch[v][i]) ch[v][i]=++tot,ch[tot][0]=ch[tot][1]=0,num[tot]=0;
	insert(ch[v][i],x,p-1);
}
int query(int v,int x,int p){
	if (!num[v]||p<0) return 0;
	int i=(x>>p)&1;
	if (num[ch[v][!i]]) return (1<<p)+query(ch[v][!i],x,p-1);
	else return query(ch[v][i],x,p-1);
}
int que[MAX_N],pre[MAX_N];
int bfs(int S){
	int t=0,h=0,u,v;
	que[t]=S;pre[S]=0;
	while (t<=h){
		u=que[t++];
		for (int k=first[u];k;k=next[k]){
			if (can[k]&&(v=to[k])!=pre[u]){
				pre[v]=u;que[++h]=v;
				}
			}
		}
	return que[h];
}
int findg(int x){
	int v=bfs(bfs(x)),p=v;
	int len=0;
	do len++;while((p=pre[p])!=0);
	len/=2;
	while (len-->0) v=pre[v];
	return v;
}
int ans=0;
int xors[MAX_N];
void work(int v,int lcaw){
	int t=0,h=0,u;
	que[t]=v;xors[v]=w[v];pre[v]=0;
	while (t<=h){
		u=que[t++];
		upmax(ans,query(1,xors[u],31));
		for (int k=first[u];k;k=next[k]){
			if (can[k]&&(v=to[k])!=pre[u]){
				xors[v]=xors[u]^w[v];
				pre[v]=u,que[++h]=v;
				}
			}
		}
	rep(i,0,h) insert(1,xors[que[i]]^lcaw,31);
}
void dfs(int v){
	int g=findg(v);
	tot=1;ch[1][0]=ch[1][1]=0;
	insert(1,0,31);insert(1,w[g],31);
	for (int k=first[g];k;k=next[k])
		if (can[k]) {can[k^1]=false;work(to[k],w[g]);can[k^1]=true;}
	for (int k=first[g];k;k=next[k])
		if (can[k]) {can[k^1]=false;dfs(to[k]);can[k^1]=true;}
}
int main(){
	n=getx();
	rep(i,1,n) w[i]=getx();
	rep(i,2,n){
		int x=getx(),y=getx();
		add(x,y),add(y,x);
		}
	dfs(1);
	printf("%d\n",ans);
}
