/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Source: 	https://www.luogu.com.cn/problem/P3835
	> Created Time: 2021/2/17 10:09:50
	您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
	1 插入 xx 数
	2 删除 xx 数(若有多个相同的数，因只删除一个)
	3 查询 xx 数的排名(排名定义为比当前数小的数的个数 +1 )
	4 查询排名为 xx 的数
	5 求 xx 的前驱(前驱定义为小于 xx，且最大的数)
	6 求 xx 的后继(后继定义为大于 xx，且最小的数)

	和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本。（操作3, 4, 5, 6即保持原版本无变化）

	每个版本的编号即为操作的序号（版本0即为初始状态，空树）
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
const int maxx=5e5+10,inf=2147483647;
struct node{
	int key,l,r,sz,rd;
}tr[maxx*50];
int num,rt[maxx];
void push_up(int x){
	tr[x].sz=tr[tr[x].l].sz+tr[tr[x].r].sz+1;
}
int add(int val){
	tr[++num].sz=1;
	tr[num].key=val;
	tr[num].rd=rand();
	return num;
}
void split(int p,int &x,int &y,int val){
	if(!p){
		x=y=0;
		return ;
	}
	if(tr[p].key<=val){
		x=++num;  tr[x]=tr[p];
		split(tr[x].r,tr[x].r,y,val);
		push_up(x);
	}
	else{
		y=++num; tr[y]=tr[p];
		split(tr[y].l,x,tr[y].l,val);
		push_up(y);
	}
}
void merge(int &p,int x,int y){ //前提:l子树中所有节点权值小于r子树的权值
	if(!x || !y){
		p=x+y;
		return ;
	}
	if(tr[x].rd<tr[y].rd){
		p=++num; tr[p]=tr[x];
		merge(tr[p].r,tr[p].r,y);
	}
	else{
		p=++num; tr[p]=tr[y];
		merge(tr[p].l,x,tr[p].l);
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
	merge(del_node,tr[del_node].l,tr[del_node].r);
	merge(l,l,del_node);
	merge(p,l,r);
}
int get_rank(int &p,int val){
	int l=0,r=0,ans=0;
	split(p,l,r,val-1);
	ans=tr[l].sz+1;
	merge(p,l,r);
	return ans;
}	
int get_kth(int p,int k){
	if(!p) return 0;
	if(tr[tr[p].l].sz+1>k) return get_kth(tr[p].l,k);
	else if(tr[tr[p].l].sz+1<k) return get_kth(tr[p].r,k-tr[tr[p].l].sz-1);
	else return tr[p].key;
}
int pre(int &p,int val){
	int l=0,r=0,ans;
	split(p,l,r,val-1);
	ans=get_kth(l,tr[l].sz);
	if(!ans) return -inf;
	merge(p,l,r);
	return ans;
}
int suf(int &p,int val){
	int l=0,r=0,ans;
	split(p,l,r,val);
	ans=get_kth(r,1);
	if(!ans) return inf;
	merge(p,l,r);
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int q=read();
	For(i,1,q){
		int v=read(),u=read(),x=read();
		rt[i]=rt[v];
		if(u==1) ins(rt[i],x);
		else if(u==2) del(rt[i],x);
		else if(u==3) printf("%d\n",get_rank(rt[i],x));
		else if(u==4) printf("%d\n",get_kth(rt[i],x));
		else if(u==5) printf("%d\n",pre(rt[i],x));
		else if(u==6) printf("%d\n",suf(rt[i],x));
	}
	return 0;
}
