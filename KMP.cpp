#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;
char s1[1000010],s2[1010];
int ne[1010],len1,len2;
void Find(char s[]){
    int t;
    ne[0]=-1;
    for(int i=1;i<len2;i++){
        t=ne[i-1];
        while(t>=0 && s[t+1]!=s[i]) t=ne[t];
        if(s[t+1]==s[i])ne[i]=t+1;
        else ne[i]=-1;
    }

}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,m,n;
    scanf("%s%s",s1,s2);
    len1=strlen(s1);
    len2=strlen(s2);
    Find(s2);
    i=j=0;
    while(i<len1){
        if(s1[i]==s2[j]){
            ++i;++j;
            if(j==len2){
                j=ne[j-1]+1;
                printf("%d\n",i-len2+1);
            }
        }
        else{
            if(j==0)++i;
            else
                j=ne[j-1]+1;
        }
    }
    for(i=0;i<len2;i++)
        printf("%d ",ne[i]+1);
    return 0;
}
