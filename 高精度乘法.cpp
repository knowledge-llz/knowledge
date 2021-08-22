    #include<cstdio>  
    #include<cstdlib>  
    #include<cstring>  
    #include<iostream>  
    using namespace std;  
    int a[100],b[100],c[200];    
    char s[100];  
    int main(){    
        int i,j,k,m,n;    
        gets(s);  
        int alen=strlen(s);     
        for(i=1;i<=alen;i++)    
            a[i]=s[alen-i]-'0';    
        gets(s);    
        int blen=strlen(s);     
        for(i=1;i<=blen;i++)    
            b[i]=s[blen-i]-'0';         
        for(i=1;i<=alen;i++)    
            for(j=1;j<=blen;j++)    
                c[i+j-1]+=a[i]*b[j];    
        int clen=alen+blen;            
        for(i=1;i<=clen;i++)    
            if(c[i]>=10){    
                c[i+1]+=c[i]/10;    
                c[i]%=10;    
            }    
        for(i=clen;i>=1;i--)    
        cout<<c[i];  
        return 0;  
    }  
