    #include<iostream>  
    #include<cstdio>  
    #include<cstdlib>  
    #include<cstring>  
    using namespace std;  
    const int inf=1e7;  
    int a[100][100],d[100],p[100];  
    int main(){  
        int i,j,k,m,n,x,y,w;  
        scanf("%d%d",&n,&m);  
        for(i=1;i<=m;i++){  
            scanf("%d%d%d",&x,&y,&w);  
            a[x][y]=w;  
            a[y][x]=w;  
        }  
        for(i=1;i<=n;i++){p[i]=0;d[i]=inf;}  
        d[1]=1;  
        for(i=1;i<=n;i++){  
            int tmp=inf;  
            for(j=1;j<=n;j++)  
                if(!p[i]&&d[i]<inf){  
                    tmp=d[i];  
                    k=j;  
                }  
            p[k]=1;  
            for(j=1;j<=n;j++){  
                if(!p[i]&&a[k][j]&&d[j]>d[k]+a[k][j])  
                    d[j]=d[k]+a[i][j];  
                }  
            }  
            for(i=1;i<n;i++)printf("%d",d[i]);  
          
          
        return 0;  
    }  
