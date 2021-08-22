#include<bits/stdc++.h>
#define M 100005
#define INF 19260817
using namespace std;

struct edge{int u,next;}e[M*2]={0}; int head[M]={0},Use=0;
void add(int x,int y){Use++;e[Use].u=y;e[Use].next=head[x];head[x]=Use;}

int num[M]={0},vis[M]={0};

int siz[M]={0};

void dfssiz(int x,int fa){
    siz[x]=1;
    for(int i=head[x];i;i=e[i].next)
    if(e[i].u!=fa&&vis[e[i].u]==0){
        dfssiz(e[i].u,x);
        siz[x]+=siz[e[i].u];
    }
}
int minn,minid;
void dfsmax(int x,int fa,int fasiz){
    int maxn=fasiz-siz[x];
    for(int i=head[x];i;i=e[i].next)
    if(e[i].u!=fa&&vis[e[i].u]==0){
        dfsmax(e[i].u,x,fasiz);
        maxn=max(maxn,siz[e[i].u]);
    }
    if(maxn<minn) minn=maxn,minid=x;
}

int makeroot(int x){
    dfssiz(x,0);
    minn=INF; minid=0;
    dfsmax(x,0,siz[x]);
    return minid;
}

struct trie{
    int a[2];
}a[M*20]={0};int root[M]={0},use=0;

void add(int &x,int zhi,int wei){
    a[++use]=a[x]; x=use; int hh=0;
    if(wei<0) return;
    if((1<<wei)&zhi) hh=1;
    add(a[x].a[hh],zhi,wei-1);
}
int query(int x,int zhi,int wei){
    if(wei<0||x==0) return 0; 
    int hh=1,ans=0;
    if((1<<wei)&zhi) hh=0;
    if(!a[x].a[hh]) return query(a[x].a[hh^1],zhi,wei-1);
    else return (1<<wei)+query(a[x].a[hh],zhi,wei-1);
}

void dfsdis(int x,int fa,int hh,int cnt){
    hh^=num[x];
    add(root[cnt],hh,30);
    for(int i=head[x];i;i=e[i].next)
    if(e[i].u!=fa&&vis[e[i].u]==0){
        dfsdis(e[i].u,x,hh,cnt);
    }
}

int ans=0;

void query(int x,int fa,int hh,int cnt){
    hh^=num[x];
    int now=query(root[cnt-1],hh,30);
    ans=max(ans,now);
    ans=max(ans,hh);
    for(int i=head[x];i;i=e[i].next)
    if(e[i].u!=fa&&vis[e[i].u]==0){
        query(e[i].u,x,hh,cnt);
    }
}

void calc(int x){
    int cnt=0;
    for(int i=head[x];i;i=e[i].next)
    if(vis[e[i].u]==0){
        cnt++; root[cnt]=root[cnt-1];
        dfsdis(e[i].u,x,0,cnt);
    }
    cnt=0;
    for(int i=head[x];i;i=e[i].next)
    if(vis[e[i].u]==0){
        cnt++;
        ans=max(ans,num[x]);
        query(e[i].u,x,num[x],cnt);
    }
    use=0; memset(root,0,(cnt+1)<<2);
}

void dfs(int x){
    x=makeroot(x); vis[x]=1; 
    calc(x);
    for(int i=head[x];i;i=e[i].next)
    if(vis[e[i].u]==0) dfs(e[i].u);
}

int main(){
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n; scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",num+i);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        add(x,y); add(y,x);
    }
    dfs(1);
    cout<<ans<<endl;
}
