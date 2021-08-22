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
	int key[maxx],sz[maxx],rd[maxx],son[maxx][2],num,rt;
	TREAP(){
		num=rt=0;
		memset(sz,0,sizeof(sz));
		memset(son,0,sizeof(son));
	}
	void push_up(int x){
		sz[x]=sz[son[x][0]]+sz[son[x][1]]+1;
	}
	int add(int val){
		sz[++num]=1;
		key[num]=val;
		rd[num]=rand();
		return num;
	}
	void split(int p,int &l,int &r,int val){
		if(!p){
			l=r=0;
			return ;
		}
		if(key[p]<=val){
			l=p;
			split(son[l][1],son[l][1],r,val);
		}
		else{
			r=p;
			split(son[r][0],l,son[r][0],val);
		}
		push_up(p);
	}
	void merge(int &p,int l,int r){ //前提:l子树中所有节点权值小于r子树的权值
		if(!l || !r){
			p=l+r;
			return ;
		}
		if(rd[l]<rd[r]){
			p=l;
			merge(son[p][1],son[p][1],r);
		}
		else{
			p=r;
			merge(son[p][0],l,son[p][0]);
		}
		push_up(p);
	}
	void ins(int &p,int val){
		int l=0,r=0,new_node=add(val);
		split(p,l,r,val);
		merge(l,l,new_node);
		merge(p,l,r);
	}
	void del(int &p,int val){
		int l=0,r=0,del_node=0;
		split(p,l,r,val);
		split(l,l,del_node,val-1);
		merge(del_node,son[del_node][0],son[del_node][1]);
		merge(l,l,del_node);
		merge(p,l,r);
	}
	int get_rank(int &p,int val){
		int l=0,r=0,ans=0;
		split(p,l,r,val-1);
		ans=sz[l]+1;
		merge(p,l,r);
		return ans;
	}
	int get_kth(int p,int k){
		if(!p) return 0;
		if(sz[son[p][0]]+1>k) return get_kth(son[p][0],k);
		else if(sz[son[p][0]]+1<k) return get_kth(son[p][1],k-sz[son[p][0]]-1);
		else return key[p];
	}
	int pre(int &p,int val){
		int l=0,r=0,ans;
		split(p,l,r,val-1);
		ans=get_kth(l,sz[l]);
		merge(p,l,r);
		return ans;
	}
	int suf(int &p,int val){
		int l=0,r=0,ans;
		split(p,l,r,val);
		ans=get_kth(r,1);
		merge(p,l,r);
		return ans;
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
