const int maxx=1e5;	
bool is[maxx];
int pri[maxx],cnt=0;
void Findpri(int limit){
	memset(is,true,sizeof(is));
	for(int i=2;i<=limit;++i){
		if(is[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt;++j){
			if(i*pri[j]>limit) break;
			is[i*pri[j]]=0;
			if(i%pri[j]==0) break;
		}
	}
}








	#include<iostream>  
    #include<cstdio>  
    #include<cstring>  
    using namespace std;   
    bool IsPrime[10000001];  
    int Pri[2000001],PriN;  
    int FindPrime ( int MaxN ) {  
        for( int i = 2 ; i <= MaxN ; ++i ){  
            if( IsPrime[ i ] ){  
                Pri[ PriN++ ]=i; //����仰���������ѭ��ǰ�Ա�֤PriN��Priֵ��������              
            }  
            for(int j=0;j<PriN;++j){  
                if( i*Pri[ j ] > MaxN )  
                    break; //�������˾�����  
                IsPrime[ i * Pri[ j ] ] = 0;  
                printf("sai:%d*%d=%d\n",i,Pri[j],i*Pri[j]);  
                //ɸȥ����  
                if( i % Pri[ j ] == 0 ) break;  
                //�����ǹؼ�,���i��һ������(�⵱Ȼ�������)����i mod prime[j] = 0  
                //��ô����,��Ϊi*prime[ (- over -)j ]һ���Ѿ���ɸȥ��,��һ�������ӱ�iС����  
                //��һ����������ġ���"�����͸ú����ĳ˻�"����һ������ĺ����ͱ���С��������˵õ���  
            }  
        }  
    }   
    int main(){  
        memset(IsPrime,true,sizeof(IsPrime));  
        FindPrime ( 30 );  
        for(int i=0;i<PriN;i++)printf("%d ",Pri[i]);  
        return 0;  
    }








