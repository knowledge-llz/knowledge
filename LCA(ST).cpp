#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
using namespace std;
const int maxx=1000010;			//双向边数组要开点数的两倍
int n,q,root,be[maxx/2],to[maxx],ne[maxx],e=0;
int dp[maxx][20],fir[maxx],deep[maxx/2],cnt=0;
bool p[maxx/2];
void add(int x,int y){			//用链式前向星存图
    to[++e]=y;
    ne[e]=be[x];
    be[x]=e;
}
int read(){						//读入优化
    char x;
    while((x=getchar())<'0' || x>'9');
    int u=x-'0';
    while((x=getchar())>='0' && x<='9')u=u*10+x-'0';
    return u;
    }
void dfs(int id){						//p记录是否到过				
    p[id]=1;							//cnt记录访问的顺序
    dp[++cnt][0]=id;					//dp记录第CNT个访问的点编号
    fir[id]=cnt;						//fir记录每个点第一次出现的位置
    for(int i=be[id];i;i=ne[i]){
        int go=to[i];
        if(!p[go]){
            deep[go]=deep[id]+1;		//点的深度
            dfs(go);
            dp[++cnt][0]=id;			//回溯时也要记录访问的点
        }
    }
}
void rmq(){					//rmq算法，dp存储dfs访问序列每一段的最小深度的点
    int len=log(cnt)/log(2.0);
    for(int j=1;j<=len;j++)
        for(int i=1;i<=cnt;i++){
            if(i+(1<<j)-1>cnt)break;
            if(deep[dp[i][j-1]]<deep[dp[i+(1<<(j-1))][j-1]])
                dp[i][j]=dp[i][j-1];
            else dp[i][j]=dp[i+(1<<(j-1))][j-1];
//    printf("%d~%d~%d\n",i,j,dp[i][j]);
        }
}
void ask(int x,int y){		//rmq算法的查询
    if(x>y)swap(x,y);
    int len=log(y-x+1)/log(2);
    int a=dp[x][len],b=dp[y-(1<<len)+1][len];	
    if(deep[a]>deep[b])printf("%d\n",b);
    else printf("%d\n",a);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,m,n;
    n=read();
    q=read();
    root=read();
    for(i=1;i<n;i++){
        j=read();
        k=read();
        add(j,k);
        add(k,j);
    }
    dfs(root);
    rmq();
//    for(i=1;i<=cnt;i++)        printf("%d\n",dp[i][0]);
    while(q--){
        i=read();
        j=read();
        i=fir[i];  j=fir[j]; ask(i,j);		
    }
    return 0;
}
