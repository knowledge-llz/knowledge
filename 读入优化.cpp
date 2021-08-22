#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>

#define For(a, b, c) for(a = b; a <= c; ++a)
#define Forr(a, b, c) for(a = b; a >= c; --a)
#define set(a, b) memset(a, b, sizeof(a))
using namespace std;

int read(){
	char x;
	while((x = getchar()) > '9' || x < '0') ;
	int u = x - '0';
	while((x = getchar()) <= '9' && x >= '0') u = u * 10 + x - '0';
	return u;
}

int read()
{
	char c = getchar();register int fg = 1, sum =0;
	while(c < '0' || c > '9')
	{
		if(c == '-')fg = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		sum = sum * 10 + c - '0';
		c = getchar();
	}
	return fg * sum;
}

int main(){

	return 0;
}
