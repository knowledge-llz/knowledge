#include <iostream>
#include <cstdio>
using namespace std;
const int MAX = 20000010;
struct Persistable_Segment_tree
{
	int ls,rs,v;//分别是该位置代表的节点或区间的左儿子右儿子和权值
} tr[MAX];
int edit[1 << 20] = {1},w[1 << 20],tot;//edit储存节点版本 注意第一个(下标0)赋值为1表第一个版本 w储存点初始权值
int build(int l,int r)
{//此处不能直接用++tot代替pos 因为跳转到子程序中继续搜索下去 tot值会增加 而此处值代表当前节点编号 应不变
	int pos = ++tot;//tot是当前数组末尾的位置 ++tot则是在末尾处新建储存节点或区间的相关信息 充分利用空间OwO真是太厉害了
	if (l == r)//区间左右相等 即只包括一个点 则只存点权
	{
		tr[pos].v = w[l];//记录初始点权
		return pos;//pos是当前节点的编号 需返回 用以让其父亲节点记录他
	}
	int mid = (l + r) >> 1;//二分存中点
	tr[pos].ls = build(l,mid);//记录当前节点的左儿子编号
	tr[pos].rs = build(++mid,r);//记录当前节点的右儿子编号
	return pos;//返回当前节点编号 需返回 用以让其父亲节点记录他
}
int update(int ed,int l,int r,int p,int k)//在ed版本的基础上 修改p点权值为k 记录当前区间最左&&最右端的点l&&r 
{//此处不能直接++tot代替pos 因为跳转到子程序中继续搜索下去 tot值会增加 而此处值代表当前节点编号 应不变
	int pos = ++tot;//记录当前节点编号 充分利用空间OwO真是太奇妙了
	if (l == r)//当搜索到单个节点了
	{
		tr[pos].v = k;//记录修改后节点权值
		return pos;//返回当前节点编号 让当前版本的父亲记录他
	}
	tr[pos].ls = tr[ed].ls;//将之前的该节点左儿子复制 (引用-->「把子节点指向前驱节点以备复用」)
	tr[pos].rs = tr[ed].rs;//将之前的该节点右儿子复制 因为之后只会改变两儿子之一的值 这样子可以确定该节点位置
	int mid = (l + r) >> 1;//二分存中点
	if (p <= mid) tr[pos].ls = update(tr[ed].ls,l,mid,p,k);//向下寻找 逼近p点 更改pos点的左儿子
	else tr[pos].rs = update(tr[ed].rs,++mid,r,p,k);//向下寻找 逼近p点 更改pos点的右儿子 用tr[ed]的原因是此时tr[pos]只有1深度的孩子的值
	return pos;//返回pos pos作为该点父亲的某个儿子的位置 用以记录
}
int found(int ed,int l,int r,int p)
{//ed是 某版本 储存区间1~n的值 的位置
	if (l == r) return tr[ed].v;//找到该点 此时ed已经变为 记录当前版本的p点的位置了 其v则是当前版本的p点的权值 返回
	int mid = (l + r) >> 1;
	if (p <= mid) return found(tr[ed].ls,l,mid,p);//向下寻找 逼近p点 ed变为ed的左儿子
	else return found(tr[ed].rs,++mid,r,p);//向下寻找 逼近p点 ed变为ed的右儿子
}
int main()
{
	int n,m,edition,mode,node,weight;//恪尽职守的变量定义
	scanf("%d%d",&n,&m);//发人深省的范围输入
	for (int a = 1 ; a <= n ; a ++) scanf("%d",&w[a]);//循规蹈矩的节点输入
	build(1,n);//建树 从区间 1 ~ n 开始递归 找左右儿子
	for (int a = 1 ; a <= m ; a ++)//循序渐进的命令处理
	{
		scanf("%d%d%d",&edition,&mode,&node);//五花八门的命令输入
		if (mode % 2)//巧妙绝伦的判断
		{
			scanf("%d",&weight);//扑朔迷离的补充输入
			edit[a] = update(edit[edition],1,n,node,weight);//update解释见子程序
		}//以update此时求出tr数组的末尾 edit[a]意为在第a个版本时修改的点为edit[a-1]到edit[a]的点(上面那行程序让本人想了很久很久)
		else//机智无比的转折
		{
			edit[a] = edit[edition];//因为复制没有创建新节点 因此当前版本的所有点等于当前版本(不是第a-1的版本)之前的所有点
			printf("%d\n",found(edit[edition],1,n,node));//输出查询某edition的某node的值
		}
	}
	return 0;//逢考必备的结尾
}
