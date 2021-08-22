#include<stack>
int n,cnt,scc_cnt,dfn[2020],low[2020],scc[2020];
bool vis[2020];
//dfn表示时间戳，low表示能到达的最小祖先，scc表示新集合的编号
//用结构体表示两个图
struct MAP{
	int e,be[2020],to[maxx],ne[maxx],d[maxx];
	MAP(){e=0;}
	void init(){
		For(i,0,e) to[i]=ne[i]=0;
		For(i,0,n) be[i]=d[i]=0;
		e=0;
	}
	void add(int x,int y){
		to[++e]=y;
		ne[e]=be[x];
		be[x]=e;
		d[y]++;
	}
}New,Old;

//初始化
void init(){
	ans=cnt=scc_cnt=0;
	For(i,0,n){
		dfn[i]=low[i]=scc[i]=vis[i]=0;
		c[i]=oo;
	}
	Old.init(); New.init();
}
//tarjan
stack<int>s;
void tarjan(int id){
	s.push(id);
	dfn[id]=low[id]=++cnt;
	for(int i=Old.be[id];i;i=Old.ne[i]){
		int go=Old.to[i];
		if(!dfn[go]){
			tarjan(go);
			low[id]=min(low[id],low[go]);
		}
		else if(!scc[go]) low[id]=min(low[id],dfn[go]);
	}
	if(low[id]==dfn[id]){
		scc_cnt++;
		while(1){
			int x=s.top(); s.pop();
			scc[x]=scc_cnt;
			if(x==id) break;
		}
	}
}
//建新图
void build(){
	For(id,1,n){
		vis[scc[id]]=1;
		for(int i=Old.be[id];i;i=Old.ne[i]){
			int go=Old.to[i];
			if(!vis[scc[go]]){
				New.add(scc[id],scc[go]);
				vis[scc[go]]=1;
			}
		}
		for(int i=Old.be[id];i;i=Old.ne[i])	vis[Old.to[i]]=0;
		vis[scc[id]]=0;
	}
}
int main()
{
	init();
	For(i,1,n) if(!dfn[i]) tarjan(i);
	build();
	return 0;
}
