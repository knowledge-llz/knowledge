/*************************************************************************
	> 这不是纯模板，但能启发主席树区间操作的一些写法
	> Link: https://ac.nowcoder.com/acm/contest/11258/F 
	> Created Time: 2021/8/8 17:34:42
 ************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=3e5+10;
int n,L[maxx],R[maxx],dep[maxx],rt[maxx],tot,cnt,ans;
int ls[maxx*30],rs[maxx*30],mx[maxx*30],lazy[maxx*30];
vector<int>g[maxx],h[maxx];
void getdfn(int x,int fa){
	if(fa && h[x].size()==1){
		L[x]=R[x]=++tot;
		return;
	}
	for(auto u:h[x]){
		if(u==fa) continue;
		getdfn(u,x);
		if(!L[x]) L[x]=L[u];
		R[x]=R[u];
	}
}
void push_down(int x){
	if(!ls[x]) ls[x]=++cnt;
	if(!rs[x]) rs[x]=++cnt;
	if(!lazy[x]) return;
	mx[ls[x]]=lazy[x];
	mx[rs[x]]=lazy[x];
	lazy[ls[x]]=lazy[x];
	lazy[rs[x]]=lazy[x];
	lazy[x]=0;
}
//查询、修改二合一
//查询[ql,qr]区间最大值，修改[ql,qr]区间最大值
int add(int &q,int pre,int l,int r,int ql,int qr,int v){
	q=++cnt; mx[q]=v;
	if(ql<=l && qr>=r){
		ls[q]=rs[q]=0;
		lazy[q]=v;
	 	return v-mx[pre];
	}
	push_down(pre);
	int mid=(l+r)>>1;
	if(qr<=mid){ rs[q]=rs[pre]; return add(ls[q],ls[pre],l,mid,ql,qr,v); }
	else if(ql>mid){ ls[q]=ls[pre]; return add(rs[q],rs[pre],mid+1,r,ql,qr,v); }
	else return min( add(ls[q],ls[pre],l,mid,ql,mid,v), add(rs[q],rs[pre],mid+1,r,mid+1,qr,v) );
}

void dfs(int x,int fa,int pre){
//	cout<<x<<" "<<fa<<" "<<pre<<endl;
	dep[x]=dep[fa]+1;
	pre=min(pre+1,add(rt[x],rt[fa],1,tot,L[x],R[x],dep[x]));
	ans=max(ans,pre);
	for(auto u:g[x]) if(u!=fa) dfs(u,x,pre);
}

void in(vector<int>vec[]){
	For(i,1,n) vec[i].clear();
	For(i,1,n-1){
		int u=read(),v=read();
		vec[u].pb(v); vec[v].pb(u);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T=read();
	while(T--){
		n=read(); cnt=tot=ans=0;
		in(g); in(h);
		getdfn(1,0);
//		For(i,1,n) cout<<L[i]<<" "<<R[i]<<endl;
		dfs(1,0,0);
		printf("%d\n",ans);
		For(i,0,n) L[i]=0;
		For(i,0,cnt) mx[i]=lazy[i]=ls[i]=rs[i]=rt[i]=0;
	}
	return 0;
}
