/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/9/1 16:59:08
	> 这是AC自动机的优化，只有在特殊题型才能这么做，主要是在Find查询的时候不是直接跳fail，而是打上标记，最后在fail树上将标记通过拓扑排序传递下去。
	> 见洛谷AC自动机（二次加强版），题意给N个模式串和一个文本串，输出各个串在文本串中出现的次数。
	此题不能直接跳fail指针一个个修改次数，应该先在对应节点加值，最后拓扑一遍fail树求解。
	在跳fail指针时，其实我们关心的是作为字符串结尾的节点，我用一个last数组表示在fail树上上一个字符结尾的节点，相当于是fail指针的一个路径压缩。
 ************************************************************************/
#include<queue>
#include<unordered_map>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
using namespace std;
const int maxx=2e6+10;
char s[maxx],t[maxx];
int n,cnt[maxx],ans[maxx];
unordered_map<int,int>Map;
struct Trie{
	int ch[maxx][30],val[maxx],f[maxx],last[maxx],d[maxx],sz;
	void init(){ sz=1; memset(ch[0],0,sizeof(ch[0])); }
	int idx(char c){ return c-'a'; }
	void insert(char *T,int v){
		int u=0,len=strlen(T);
		for(int i=0;i<len;++i){
			int c=idx(T[i]);
			if(!ch[u][c]){
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
				ch[u][c]=sz++;
			}
			u=ch[u][c];
		}
		if(!val[u]) val[u]=v;
		else Map[v]=val[u];
	}
	void getfail(){
		queue<int>q;
		f[0]=last[0]=0;
		For(c,0,25) if(ch[0][c]){ q.push(ch[0][c]); f[ch[0][c]]=last[ch[0][c]]=0; }
		while(!q.empty()){
			int r=q.front(); q.pop();
			For(c,0,25){
				int u=ch[r][c];
				if(!u) ch[r][c]=ch[f[r]][c];
				else{
					q.push(u);
					f[u]=ch[f[r]][c];
					last[u]=val[f[u]]?f[u]:last[f[u]];
					if(val[u]) d[last[u]]++;
				}
			}
		}
	}
	void getans(){
		queue<int>q;
		For(i,1,sz-1)
			if(val[i] && !d[i]) q.push(i); 
		while(!q.empty()){
			int r=q.front(),u=last[r]; q.pop();
			if(!u) continue;
			cnt[val[u]]+=cnt[val[r]];
			d[u]--;
			if(!d[u]) q.push(u);
		}
	}

	void Find(char *T){
		int len=strlen(T),j=0;
		For(i,0,len-1){
			int c=idx(T[i]);
			j=ch[j][c];
			if(val[j]) ++cnt[val[j]];
			else ++cnt[val[last[j]]];
		}
		getans();
	}

}trie;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	while(~scanf("%d",&n) && n){
		trie.init();
		For(i,1,n){
			scanf("%s",t);
			trie.insert(t,i);
		}
		trie.getfail();
		scanf("%s",s);
		trie.Find(s);
		For(i,1,n)
			if(Map[i]) printf("%d\n",cnt[Map[i]]);
			else printf("%d\n",cnt[i]);
	}
	return 0;
}
