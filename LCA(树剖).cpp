#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int maxx=500010;
int be[maxx],ne[maxx*2],to[maxx*2],e=0;
int fa[maxx],son[maxx],deep[maxx],size[maxx],jump[maxx];
void add(int x,int y){
    to[++e]=y;
    ne[e]=be[x];
    be[x]=e;
}
template <class T>
T read(T sum = 0, T fg = 0)
{
    char c = getchar();
    while(c < '0' || c > '9') { fg |= c == '-'; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return fg ? -sum : sum;
}
int dfs(int id){
    size[id]=1;
    for(int i=be[id];i;i=ne[i]){
        int go=to[i];
        if(fa[id]==go)continue;
//        printf("%d\n",go);
        fa[go]=id;
        deep[go]=deep[id]+1;
        size[id]+=dfs(go);
        if(son[id]==-1 || size[go]>size[son[id]])
            son[id]=go;
    }
    return size[id];
}
void work(int id,int top){
    jump[id]=top;
    if(son[id]!=-1) work(son[id],top);
    for(int i=be[id];i;i=ne[i]){
        int go=to[i];
        if(fa[id]==go ||son[id]==go)continue;
        work(go,go);
    }
}
int query(int x,int y){
    while(jump[x]!=jump[y]){
        if(deep[jump[x]]>deep[jump[y]]){x^=y;y^=x;x^=y;}
        y=fa[jump[y]];
    }
//    printf("%d~%d\n",x,y);
    return deep[x]>deep[y]?y:x;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif 
    int n = read<int>(),m = read<int>(),root = read<int>();
    int i,j,k;
    for(i=1;i<n;i++){
        j= read<int>();
        k= read<int>();
        add(j,k);
        add(k,j);
    }
    fa[root]=root;
    memset(son,-1,sizeof(son));
    dfs(root);
    work(root,root);
//    for(i=1;i<=n;i++)        printf("%d\n",son[i]);
    for(i=1;i<=m;i++){
        j= read<int>();
        k= read<int>();
        printf("%d\n",query(j,k));
    }
 
    return 0;
}
