#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=2*1e6+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
    double x,y;
    complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[MAXN],b[MAXN];
complex operator + (complex a,complex b){ return complex(a.x+b.x , a.y+b.y);}
complex operator - (complex a,complex b){ return complex(a.x-b.x , a.y-b.y);}
complex operator * (complex a,complex b){ return complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//�����Ŀ������������ǲ��� 
void fast_fast_tle(int limit,complex *a,int type)
{
    if(limit==1) return ;//ֻ��һ��������
    complex a1[limit>>1],a2[limit>>1];
    for(int i=0;i<=limit;i+=2)//�����±����ż�Է���
        a1[i>>1]=a[i],a2[i>>1]=a[i+1];
    fast_fast_tle(limit>>1,a1,type);
    fast_fast_tle(limit>>1,a2,type);
    complex Wn=complex(cos(2.0*Pi/limit) , type*sin(2.0*Pi/limit)),w=complex(1,0);
    //WnΪ��λ����w��ʾ��
    for(int i=0;i<(limit>>1);i++,w=w*Wn)//�����w�൱�ڹ�ʽ�е�k 
        a[i]=a1[i]+w*a2[i],
        a[i+(limit>>1)]=a1[i]-w*a2[i];//���õ�λ�������ʣ�O(1)�õ���һ���� 
}
int main()
{
    int N=read(),M=read();
    for(int i=0;i<=N;i++) a[i].x=read();
    for(int i=0;i<=M;i++) b[i].x=read();
    int limit=1;while(limit<=N+M) limit<<=1;
    fast_fast_tle(limit,a,1);
    fast_fast_tle(limit,b,1);
    //�����1��ʾҪ���еı任��ʲô����
    //1��ʾ��ϵ����Ϊ��ֵ
    //-1��ʾ�ӵ�ֵ��Ϊϵ�� 
    //����Ϊʲô�����ǶԵģ����Բο�һ��c�������Ƶ����̣� 
    for(int i=0;i<=limit;i++)
        a[i]=a[i]*b[i];
    fast_fast_tle(limit,a,-1);
    for(int i=0;i<=N+M;i++) printf("%d ",(int)(a[i].x/limit+0.5));//���������Ƶ��Ĺ�ʽ�����ﻹҪ����n 
    return 0;
}
