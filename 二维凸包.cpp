#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<cstdio>
#include<algorithm>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Rep(i,a,b) for(register int i=a;i>=b;--i)
const int oo=1e9+7,maxx=10010;
using namespace std;
int n,top,k;
double ans=0;
double pf(double a){return a*a;}
struct node{
    double x,y;
    void read(){scanf("%lf%lf",&x,&y);}
    bool operator < (const node dog) const{
        if(x==dog.x) return y<dog.y;
        return x<dog.x; 
    }
    node operator - (const node dog) const{
        return (node){x-dog.x,y-dog.y};
    }
    double operator * (const node dog) const{
        return x*dog.y-y*dog.x;
    }
    friend double dis(node a,node b){
        return sqrt(pf(a.x-b.x)+pf(a.y-b.y));
    }
}dot[maxx],q[maxx];

void into(node now){
    while((now-q[top-1])*(q[top]-q[top-1])>0 && top>k) top--;
    q[++top]=now;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    cin>>n;
    For(i,1,n) dot[i].read();
    sort(dot+1,dot+n+1);
    q[++top]=dot[1]; q[++top]=dot[2];
    k=1;
    For(i,3,n) into(dot[i]);
    k=top;
    Rep(i,n-1,1) into(dot[i]);
    For(i,1,top-1)
        ans+=dis(q[i],q[i+1]);
    printf("%.2lf\n",ans);
    return 0;
}
