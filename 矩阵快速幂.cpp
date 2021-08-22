#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int i,j,k,n,mod;
struct Matrix{
    int matrix[50][50];
    Matrix (int a=0){
        memset(matrix,0,sizeof(matrix));
        if(a==1){
            for(int i=0;i<50;i++)
                matrix[i][i]=1;
            }
        }
    }m;
    Matrix operator * (Matrix a,Matrix b){ //???¨®¨®¨°
        Matrix res;  
        memset(res.matrix,0,sizeof(res.matrix));  
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=n;j++)  
                for(int k=1;k<=n;k++)  
                    res.matrix[i][j]=(res.matrix[i][j]+(a.matrix[i][k]*b.matrix[k][j])%mod)%mod;  
        return res;  
    }  
    Matrix operator + (Matrix a,Matrix b){ //???
        Matrix res;  
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=n;j++)  
                res.matrix[i][j]=(a.matrix[i][j]+b.matrix[i][j])%mod;   
        return res;  
    }  
    Matrix operator ^ (Matrix a,int k){ //???¨®¨®¨°???Y
        bool flag=false;  
        Matrix ans=1;  
        while(k){  
            if(k&1){  
                if(flag)ans=ans*a;  
                else ans=a;  
                flag=true;  
            }  
            a=a*a;  
            k>>=1;  
        }  
        return ans;  
    }  
    
Matrix sum(int k){
    if(k==1)return m;
    else{
        Matrix tmp=sum(k>>1);
        if(k&1){
            Matrix tmp2=m^(k>>1|1);
            return tmp2+tmp+tmp*tmp2;//tmp=s[i]
        }
        else{
            Matrix tmp2=m^(k>>1);
            return tmp+tmp*tmp2;
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&k,&mod);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++){
        scanf("%d",&m.matrix[i][j]);
        m.matrix[i][j]%=mod;
        }
    Matrix ans;
    ans=sum(k);                
    for(i=1;i<=n;i++,puts(""))
        for(j=1;j<=n;j++)        
        printf("%d ",ans.matrix[i][j]);
    return 0;
}

————————————————
版权声明：本文为CSDN博主「罗旅洲」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Pig_cfbsl/article/details/52551196
