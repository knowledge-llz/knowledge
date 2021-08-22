/*************************************************************************
	> File Name: 1.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://blog.csdn.net/Pig_cfbsl 
	> Created Time: 2020/6/10 15:32:28
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define LL long long
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
const int maxx=1e6+10;
char s[maxx],t[maxx];
int nxt[maxx],lens,lent;
void init(){
	nxt[0]=nxt[1]=0;
	For(i,1,lent-1){
		int j=nxt[i-1];
		while(j && t[j]!=t[i]) j=nxt[j-1];
		if(t[j]==t[i]) ++j;
		nxt[i]=j;
	}
}
void Find(){
	int j=0;
	For(i,0,lens-1){
		while(j && s[i]!=t[j]) j=nxt[j-1];
		if(s[i]==t[j]) ++j;
		if(j==lent) printf("%d\n",i-lent+2);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	scanf("%s%s",s,t);
	lens=strlen(s); lent=strlen(t);
	init();
	Find();
	return 0;
}
