#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int maxx=100010;
int be[maxx],ne[maxx*2],to[maxx*2],e=0;
int fa[maxx],son[maxx],deep[maxx],size[maxx],jump[maxx],tot=0;
int x[maxx],y[maxx],a[maxx];
long long tree[maxx*4],lazy[maxx*4],val;
int n,q,root,mod;
void add(int x,int y){
    to[++e]=y;
    ne[e]=be[x];
    be[x]=e;
}
int read(){
    char x;
    while((x=getchar())<'0' || x>'9');
    int u=x-'0';
    while((x=getchar())>='0' && x<='9')u=u*10+x-'0';
    return u;
}
int dfs1(int id){
    size[id]=1;
    for(int i=be[id];i;i=ne[i]){
        int go=to[i];
        if(fa[id]==go)continue;
        fa[go]=id;
        deep[go]=deep[id]+1;
        size[id]+=dfs1(go);
        if(!son[id] || size[go]>size[son[id]])
            son[id]=go;
    }
    return size[id];
}
void dfs2(int id,int top){
    x[id]=++tot;
    y[tot]=id;
    jump[id]=top;
    if(son[id]) dfs2(son[id],top);
    for(int i=be[id];i;i=ne[i]){
        int go=to[i];
        if(fa[id]==go ||son[id]==go)continue;
        dfs2(go,go);
    }
}
void build(int id,int l,int r){
    if(l==r){
        tree[id]=a[y[l]]%mod;
//        if(l==4) printf("%d~%d\n",y[l],id);
        return ;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid),build(id<<1|1,mid+1,r);
    tree[id]=(tree[id*2]+tree[id*2+1])%mod;
}
void update(int l,int r,int xl,int xr,int id,int v){
    if(l>=xl && r<=xr)    lazy[id]+=v;
    else{
        int mid=(l+r)>>1;
        if(xl>mid)update(mid+1,r,xl,xr,id<<1|1,v);
        else if(xr<=mid)update(l,mid,xl,xr,id<<1,v);
        else update(l,mid,xl,mid,id<<1,v),update(mid+1,r,mid+1,xr,id<<1|1,v);
    }
    if(l<r)tree[id]=(tree[id<<1]+tree[id<<1|1])%mod;
    if(l==r)tree[id]+=v;
    else tree[id]=(tree[id]+lazy[id]*(r-l+1))%mod;
}
void pushdown(int id,int l,int r,int mid){
	lazy[id<<1]=(lazy[id<<1]+lazy[id])%mod;
	lazy[id<<1|1]=(lazy[id<<1|1]+lazy[id])%mod;
	tree[id<<1]=(tree[id<<1]+(mid-l+1)*lazy[id])%mod;
	tree[id<<1|1]=(tree[id<<1|1]+(r-mid)*lazy[id])%mod;
	lazy[id]=0;
}
long long query(int l,int r,int cl,int cr,int id){
    if(l>=cl && r<=cr){
		return tree[id]%mod;
    }
    else{
        int mid=(l+r)>>1;
		if(lazy[id])pushdown(id,l,r,mid);
        if(cl>mid) return query(mid+1,r,cl,cr,id<<1|1)%mod;
        else if(cr<=mid) return query(l,mid,cl,cr,id<<1)%mod;
        else return (query(l,mid,cl,mid,id<<1)+query(mid+1,r,mid+1,cr,id<<1|1))%mod;
    }
}
void change(int a,int b,int w){
    while(jump[a]!=jump[b]){
        if(deep[jump[a]]>deep[jump[b]]){a^=b;b^=a;a^=b;}
        update(1,tot,x[jump[b]],x[b],1,w);
//        printf("%d~%d\n",x[jump[b]],x[b]);
        b=fa[jump[b]];
    }
    if(deep[a]>deep[b]){a^=b;b^=a;a^=b;}
    update(1,tot,x[a],x[b],1,w);
//    printf("%d~%d\n",x[jump[b]],x[b]);
}
void ask(int a,int b){
    while(jump[a]!=jump[b]){
        if(deep[jump[a]]>deep[jump[b]]){a^=b;b^=a;a^=b;}
        val=(val+query(1,tot,x[jump[b]],x[b],1))%mod;
        b=fa[jump[b]];
    }
    if(deep[a]>deep[b]){a^=b;b^=a;a^=b;}
        val=(val+query(1,tot,x[a],x[b],1))%mod;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif 
    int i,j,k;
    n=read();
    q=read();
    root=read();
    mod=read();
    for(i=1;i<=n;i++){a[i]=read();a[i]%=mod;}
    for(i=1;i<n;i++){
        j=read();
        k=read();
        add(j,k);
        add(k,j);
    }
    fa[root]=root;
    dfs1(root);
    dfs2(root,root);
    build(1,1,tot);    
//    for(i=1;i<=n;i++)
//        printf("%d~%d\n",3,query(1,tot,x[3],x[3],1,0));
    while(q--){    
        int dog=read();        
//        printf("-------%d---------\n",dog);
        if(dog==1){
            i=read();
            j=read();
            val=read();
            val%=mod;
            change(i,j,val);
        }
        else if(dog==3){
            i=read();
            val=read();
            val%=mod;
            update(1,tot,x[i],x[i]+size[i]-1,1,val);
        }
        else if(dog==2){
            i=read();
            j=read();
            val=0;
            ask(i,j);
            printf("%d\n",val%mod);
        }
        else{
            i=read();
        //    printf("%d\n",x[i]);
            printf("%d\n",query(1,tot,x[i],x[i]+size[i]-1,1)%mod);
        }
//        printf("-------%d---------\n",q);
//        for(i=1;i<=n;i++)    printf("%d~%d\n",i,query(1,tot,x[i],x[i],1,0));
    }
    return 0;
}


