/*************************************************************************
    > File Name: 3.cpp
    > Author: Knowledge-Pig
    > Mail: 925538513@qq.com
    > Link: https://www.luogu.com.cn/problem/P4782
    > 有n个布尔变量，m个限制条件，第i个限制条件形如(u,x,v,y)表示第u个布尔变量为x或第v个布尔变量为y。
	  判断是否存在一种合法的布尔变量赋值方案。
************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
#define endl '\n'
using namespace std;
const int maxx = 2e6 + 10;
int n, m, cnt = 0, scc_cnt = 0, dfn[maxx], low[maxx], scc[maxx], ans[maxx];
vector<int> vec[maxx];
stack<int> s;
void tarjan(int id){
	dfn[id] = low[id] = ++cnt;
	s.push(id);
	for(auto u : vec[id]){
		if(!dfn[u]){
			tarjan(u);
			low[id] = min(low[u], low[id]);
		}
		else if(!scc[u]) low[id] = min(dfn[u], low[id]);
	}
	if(low[id] == dfn[id]){
		++scc_cnt;
		while(1){
			int u = s.top(); s.pop();
			scc[u] = scc_cnt;
			if(u == id) break;
		}
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	cin >> n >> m;
	for(int i = 1; i <= m; ++i){
		int u, v, x, y;
		cin >> u >> x >> v >> y;
		vec[u + (x ^ 1) * n].pb(v + y * n);
		vec[v + (y ^ 1) * n].pb(u + x * n);
	}
	for(int i = 1; i <= n * 2; ++i) if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; ++i){
		if(scc[i] < scc[i + n]) ans[i] = 0;
		else if(scc[i] > scc[i + n]) ans[i] = 1;
		else { cout << "IMPOSSIBLE" << endl; return 0; }
	}
	cout << "POSSIBLE" << endl;
	for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
	return 0;
}
