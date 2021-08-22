#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<cstdio>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define LL long long
const int mod=1e9+7;
using namespace std;
LL read(){
    char x=getchar(); LL u=0,fg=0;
    while(!isdigit(x)){if(x=='-') fg=1; x=getchar();}
    while(isdigit(x)) u=(u<<3)+(u<<1)+(x^'0'), x=getchar();
    return !fg?u:-u;
}
struct Matrix{
    LL n,k,a[110][110];
    void work(bool type){
        if(!type){ n=read(); k=read();}
        For(i,1,n){
            if(i >1 && type)printf("\n");
            For(j,1,n) if(!type) a[i][j]=read(); else printf("%d ",a[i][j]);
        }
    }
    Matrix operator *(const Matrix &b) const{
        Matrix res=b;
        For(i,1,n) For(j,1,n){
            res.a[i][j]=0;
            For(k,1,n) res.a[i][j]=(res.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        }
        return res;
    }
}x;
int main(){
    x.work(0); 
	Matrix res=x;
        For(i,1,res.n)
            For(j,1,res.n)
            if(i==j) res.a[i][j]=1;
            else res.a[i][j]=0;
	while(x.k){
		if(x.k&1) res=res*x;
        x=x*x;
        x.k>>=1;
	}
	res.work(1);
    return 0;
}
