#include<cstdio>
#include<algorithm>
#include<climits>
#include<stack>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define maxn (100000+5)
#define inf (INT_MAX)
using namespace std;
stack <int> s;
int tree[maxn][3],father[maxn],key[maxn],num[maxn],size[maxn],add[maxn];
int i,j,k,l,r,mid,t,n,m,tot,root,x,y;
int pd(int x){
    if (tree[father[x]][0]==x) return 0;else return 1;
}
void updata(int x){
    num[x]=max(key[x],max(num[tree[x][0]],num[tree[x][1]]));
    size[x]=size[tree[x][0]]+size[tree[x][1]]+1;
}
void rotate(int x){
    int y=father[x],z=pd(x);
    tree[y][z]=tree[x][1-z];
    if (tree[x][1-z]) father[tree[y][z]]=y;
    father[x]=father[y];
    if (father[y]) tree[father[y]][pd(y)]=x;
    father[y]=x;
    tree[x][1-z]=y;
    updata(y);
    updata(x);
}
void clear(int x){
    if (add[x]){
        if (tree[x][0]){
            if (tree[x][0]<=n||(tree[x][0]>n&&size[tree[x][0]]>1))
                num[tree[x][0]]+=add[x];
            if (tree[x][0]<=n)
                key[tree[x][0]]+=add[x];
            add[tree[x][0]]+=add[x];
        }
        if (tree[x][1]){
            if (tree[x][1]<=n||(tree[x][1]>n&&size[tree[x][1]]>1))
                num[tree[x][1]]+=add[x];
            if (tree[x][1]<=n)
                key[tree[x][1]]+=add[x];
            add[tree[x][1]]+=add[x];
        }
        add[x]=0;
    }
}
void remove(int x,int y){
    do{
        s.push(x);
        x=father[x];
    }while (x!=y);
    while (!s.empty()){
        x=s.top();
        clear(x);
        s.pop();
    }
}
void splay(int x,int y){
    remove(x,y);
    while (father[x]!=y){
        if (father[father[x]]!=y)
            if (pd(x)==pd(father[x])) rotate(x);else rotate(father[x]);
        rotate(x);
    }
}
int kth(int x,int y){
    if (size[tree[x][0]]+1==y) return x;
    else if (size[tree[x][0]]+1>y) return kth(tree[x][0],y);
    else return kth(tree[x][1],y-size[tree[x][0]]-1);
}
void split(int x,int y,int &l,int &r){
    int j=kth(x,y);
    splay(j,0);
    int k=tree[j][1];
    tree[j][1]=0;
    father[k]=0;
    l=j;
    r=k;
    updata(j);
}
void merge(int l,int r,int &x){
    int j=kth(l,size[l]);
    splay(j,0);
    tree[j][1]=r;
    father[r]=j;
    x=j;
    updata(j);
}
int main(){
    scanf("%d",&n);
    key[0]=key[n+2]=key[n+1]=-inf;
    num[n+1]=num[0]=-inf;
    size[0]=0;
    size[n+1]=size[n+2]=1;
    fo(i,1,n){
        scanf("%d",&key[i]);
        if (i>1){
            tree[i][0]=i-1;
            father[i-1]=i;
            updata(i);
        }
        else{
            tree[1][0]=n+1;
            father[n+1]=1;
            updata(1);
        }
    }
    tree[n+2][0]=n;
    father[n]=n+2;
    updata(n+2);
    root=n+2;
    splay(n+1,0);
    root=n+1;
    scanf("%d",&m);
    fo(i,1,m){
        scanf("%d%d%d",&t,&x,&y);
        if (t==1){
            scanf("%d",&t);
            split(root,y+1,l,r);
            split(l,x,l,mid);
            num[mid]+=t;
            key[mid]+=t;
            add[mid]+=t;
            merge(l,mid,l);
            merge(l,r,root);
        }
        else{
            split(root,y+1,l,r);
            split(l,x,l,mid);
            printf("%d\n",num[mid]);
            merge(l,mid,l);
            merge(l,r,root);
        }
    }
}
