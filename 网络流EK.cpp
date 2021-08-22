    #include<iostream>  
    #include<cstdio>  
    #include<cstdlib>  
    #include<algorithm>   
    using namespace std;  
      
    int c[201][201],f[201][201];  
    int d[1000][2],p[201];  
      
    int main(){  
        int i,j,k,m,n;  
        int x,y,z,s,t,min;  
        scanf("%d%d",&m,&n);  
        for(i=1;i<=m;i++){  
            scanf("%d%d%d",&x,&y,&z);  
            c[x][y]+=z;  
        }  
        int flag=1;  
        while(flag){  
            flag=0;  
            for(i=1;i<=n;i++)  
                p[i]=1;  
            s=0; t=1;  
            d[1][0]=1; d[1][1]=0;  
            p[1]=0;  
            while(s<t){  
                s++;  
                x=d[s][0];  
                for(i=1;i<=n;i++)  
                    if(p[i] && (c[x][i]>f[x][i] || f[i][x]>0)){  
                        p[i]=0;  
                        d[++t][0]=i;  
                        d[t][1]=s;  
                        if(i==n){  
                            flag=1;  
                            break;  
                        }  
                    }  
                if(flag==1) break;  
            }  
            if(!flag) break;  
            int min=1000000000;  
            i=t;  
            while(d[i][1]){  
                y=d[i][0];  
                x=d[d[i][1]][0];  
                if(c[x][y]>f[x][y] && c[x][y]-f[x][y]<min)  
                    min=c[x][y]-f[x][y];  
                if(f[y][x]>0 && f[y][x]<min)  
                    min=f[y][x];  
                i=d[i][1];  
            }  
            i=t;  
            while(d[i][1]){  
                y=d[i][0];  
                x=d[d[i][1]][0];  
                if(c[x][y]>f[x][y])  
                    f[x][y]+=min;  
                else  
                    f[y][x]-=min;  
                i=d[i][1];  
            }  
        }  
        int ans=0;  
        for(i=2;i<=n;i++)  
            ans+=f[1][i];  
        printf("%d\n",ans);  
      
        return 0;  
    }  
