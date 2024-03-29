#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define h1 9905411//hash1值
#define h2 9900589//hash2值
#define h3 8599951//hash3值
#define h4 1000000007//hash4值
#define Size 2000000
#define ull unsigned long long//用unsigned long long 自然溢出
using namespace std;
struct node{
    ull ha1,ha2,ha3,ha4;
}tree[Size];
int cnt;
char s[10000];
//4个hash,防止蜜汁碰对
ull hash1(char *s,int len){ull ans=0;for(int i=0;i<len;i++)ans=ans*h1+s[i];return ans;}
ull hash2(char *s,int len){ull ans=0;for(int i=0;i<len;i++)ans=ans*h2+s[i];return ans;}
ull hash3(char *s,int len){ull ans=0;for(int i=0;i<len;i++)ans=ans*h3+s[i];return ans;}
ull hash4(char *s,int len){ull ans=0;for(int i=0;i<len;i++)ans=ans*h4+s[i];return ans;}
inline bool cmp(node a,node b){return a.ha1<b.ha1;}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        int    len=strlen(s);
        tree[++cnt].ha1=hash1(s,len);
        tree[cnt].ha2=hash2(s,len);
        tree[cnt].ha3=hash3(s,len);
        tree[cnt].ha4=hash4(s,len);
    }
//给hash1值排序就可以了
    sort(tree+1,tree+cnt+1,cmp);
    int ans=0;
    for(int i=1;i<=cnt;i++){
                //全部相同才会i++
        while(tree[i].ha1==tree[i+1].ha1){
            if(tree[i].ha2==tree[i+1].ha2){
                if(tree[i].ha3==tree[i+1].ha3){
                    if(tree[i].ha4==tree[i+1].ha4){
                        i++;
                    }
                }
            }
        }
        ans++;//全部不相同就ans++
    }
    printf("%d\n",ans);
    return 0;
}
