/*
 *	用数组存储：
 */
	struct Trie{
		int ch[maxx][sigma_size];
		int val[maxx];
		int sz;
		Trie(){	sz=1; memset(ch[0],0,sizeof(ch[0]));
		int idx(char c){ return c-'a'; }
		void insert(char *s,int v){
			int u=0, n=strlen(s);
			For(i,0,n-1){
				int c=idx(s[i]);
				if(!ch[u][c]){
					memset(ch[sz],0,sizeof(ch[sz]));
					ch[u][c]=sz++:
				}
				u=ch[u][c];
			}
			val[u]=v; 
		}
		int query(char *s){
			int u=0,n=strlen(s);
			For(i,0,n-1){
				int c=idx(s[i]);
				if(!ch[u][c]) return 0;
				u=ch[u][c];
			}
			if(!val[u]) return 0;
			else return 1;
		}		
	};

// 给一个不用指针，用链式前向星写的TRIE，当初只为省空间
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Rep(i,a,b) for(register int i=a;i>=b;--i)
const int maxx=5000001;
using namespace std;
int be[maxx],ne[maxx],to[maxx],e=0,cnt=0;	//cnt表示节点编号，e表示边的编号
void add(int x,int y){
	to[++e]=y;
	ne[e]=be[x];
	be[x]=e;
}
struct node{
	char x;					//x:当前节点所存的字符
	bool vis,end;			//vis 是否REPEAT  end是否为名字结尾
}trie[maxx];
char name[56];
void insert(char *s){			//插入操作
	int pos=0,len=strlen(s),i=0,flag;
	For(i,0,len-1){
		flag=0;
		for(int j=be[pos];j;j=ne[j]){
			int go=to[j];
			if(trie[go].x==s[i]){			//找到已有相同节点，就把位置赋给pos
				flag=1;
				pos=go;
				break;
			}
		}
		if(!flag) {add(pos,++cnt); pos=cnt; trie[pos].x=s[i];}//没有找到就新建节点，单向边！
		if(i==len-1) trie[pos].end=1;		//标记结束
	}
}
int query(char *s){
	int pos=0,len=strlen(s),i=0,flag;
	For(i,0,len-1){
		flag=0;
		for(int j=be[pos];j;j=ne[j]){
			int go=to[j];
			if(trie[go].x==s[i]){
				pos=go;
				flag=1;
				break;
			}
		}
		if(!flag) return 0;				//没找到就返回0
		if(i==len-1)
			if(trie[pos].end){			//判断是否REPERT
				if(!trie[pos].vis) {trie[pos].vis=1; return 1;}	
				else return 2;
			}
			else return 0;
	}
}
 
int main(){
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int n,m,k;
	scanf("%d",&n);
	For(i,1,n){
		scanf("%s",name);
		insert(name);
	}
	scanf("%d",&m);
	For(i,1,m){
		scanf("%s",name);
		k=query(name);
		if(k==1) puts("OK");
		else if(!k) puts("WRONG");
		else puts("REPEAT");
	}
	return 0;
}
