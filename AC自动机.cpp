/*************************************************************************
	> File Name: AC自动机模板
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/9/1 16:59:08
	> 题意：给n个匹配串和一个文本串，判断文本串中出现多少匹配串.
 ************************************************************************/
#include<queue>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
using namespace std;
const int maxx=1e6+10;
char s[maxx],t[maxx];
int n,ans=0,a[maxx];
struct Trie{
	int ch[maxx][30],val[maxx],f[maxx],last[maxx],sz;
	Trie(){ sz=1; memset(ch[0],0,sizeof(ch[0])); }
	int idx(char c){ return c-'a'; }
	void insert(char *T){			//建立trie
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
		val[u]++;
	}
	void getfail(){				//找失配边
		queue<int>q;		
		f[0]=0;
		For(c,0,25){
			int u=ch[0][c];
			if(u){
				q.push(u);
				f[u]=0;
			}
		}
		while(!q.empty()){
			int r=q.front(); q.pop();
			For(c,0,25){
				int u=ch[r][c];
				if(!u)  ch[r][c]=ch[f[r]][c];
				else{
					q.push(u);
					f[u]=ch[f[r]][c];
					last[u]=val[f[u]]?f[u]:last[f[u]];
				}
			}
		}
	}
	void Find(char *T){			
		int len=strlen(T);
		int j=0;
		For(i,0,len-1){
			int c=idx(T[i]);
			j=ch[j][c];
			for(int x=j;x;x=last[x]) ans+=val[x], val[x]=0;
		}
	}
}trie;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	scanf("%d",&n);
	For(i,1,n){
		scanf("%s",t);		//匹配串
		trie.insert(t);
	}
	trie.getfail();
	scanf("%s",s);
	trie.Find(s);		//文本串
	cout<<ans<<endl;
	return 0;
}
