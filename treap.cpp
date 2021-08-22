/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Source: https://www.luogu.com.cn/problem/P3369
	> Created Time: 2021/2/17 10:09:50
	您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
	1 插入 xx 数
	2 删除 xx 数(若有多个相同的数，因只删除一个)
	3 查询 xx 数的排名(排名定义为比当前数小的数的个数 +1 )
	4 查询排名为 xx 的数
	5 求 xx 的前驱(前驱定义为小于 xx，且最大的数)
	6 求 xx 的后继(后继定义为大于 xx，且最小的数)
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
const int maxx=2e5+10;
struct TREAP{
	int key[maxx],sz[maxx],cnt[maxx],rd[maxx],son[maxx][2],num,rt;
	TREAP(){ 
		num=rt=0;
		memset(sz,0,sizeof(sz));
		memset(cnt,0,sizeof(cnt));
		memset(son,0,sizeof(son));
	}
	void push_up(int x){
		sz[x]=sz[son[x][0]]+sz[son[x][1]]+cnt[x];
	}
	void rotate(int &p,bool d){	//d=0 左旋，d=1 右旋
		int ii=son[p][d^1];
		son[p][d^1]=son[ii][d];
		son[ii][d]=p;
		push_up(p);
		push_up(ii);
		p=ii;
	}
	void ins(int &p,int x){
		if(!p){
			p=++num;
			sz[p]=cnt[p]=1;
			key[p]=x;
			rd[p]=rand();
			return ;
		}
		if(key[p]==x){
			++cnt[p];
			++sz[p];
			return ;
		}
		int d=x>key[p];
		ins(son[p][d],x);
		if(rd[p]<rd[son[p][d]]) rotate(p,d^1);
		push_up(p);
	}
	void del(int &p,int x){
		if(!p) return;
		if(key[p]!=x){
			int d=x>key[p];
			del(son[p][d],x);
		}
		else{
			if(!son[p][0] && !son[p][1]){
				--cnt[p];
				--sz[p];
				if(!cnt[p]) p=0;
			}
			else if(!son[p][0] && son[p][1]){
				rotate(p,0);
				del(son[p][0],x);
			}
			else if(son[p][0] && !son[p][1]){
				rotate(p,1);
				del(son[p][1],x);
			}
			else{
				int d=rd[son[p][0]]>rd[son[p][1]];
				rotate(p,d);
				del(son[p][d],x);
			}
		}
		push_up(p);
	}
	int get_rank(int p,int x){
		if(!p) return 0;
		if(key[p]==x) return sz[son[p][0]]+1;
		if(key[p]<x) return sz[son[p][0]]+cnt[p]+get_rank(son[p][1],x);
		else return get_rank(son[p][0],x);
	}
	int get_kth(int p,int k){
		if(!p) return 0;
		int tmp=sz[son[p][0]]+cnt[p];
		if(tmp<k) return get_kth(son[p][1],k-tmp);
		else if(sz[son[p][0]]>=k) return get_kth(son[p][0],k);
		else return key[p];
	}
	int pre(int p,int x){
		if(!p) return -1e9;
		if(key[p]>=x) return pre(son[p][0],x);
		else return max(key[p],pre(son[p][1],x));
	}
	int suf(int p,int x){
		if(!p) return 1e9;
		if(key[p]<=x) return suf(son[p][1],x);
		else return min(key[p],suf(son[p][0],x));
	}
}treap;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int q=read();
	while(q--){
		int u=read(),x=read();
		if(u==1) treap.ins(treap.rt,x);
		else if(u==2) treap.del(treap.rt,x);
		else if(u==3) printf("%d\n",treap.get_rank(treap.rt,x));
		else if(u==4) printf("%d\n",treap.get_kth(treap.rt,x));
		else if(u==5) printf("%d\n",treap.pre(treap.rt,x));
		else if(u==6) printf("%d\n",treap.suf(treap.rt,x));
	}
	return 0;
}
