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
                Pri[ PriN++ ]=i; //将这句话放在下面的循环前以保证PriN和Pri值的完整性              
            }  
            for(int j=0;j<PriN;++j){  
                if( i*Pri[ j ] > MaxN )  
                    break; //当过大了就跳出  
                IsPrime[ i * Pri[ j ] ] = 0;  
                printf("sai:%d*%d=%d\n",i,Pri[j],i*Pri[j]);  
                //筛去素数  
                if( i % Pri[ j ] == 0 ) break;  
                //这里是关键,如果i是一个合数(这当然是允许的)而且i mod prime[j] = 0  
                //那么跳出,因为i*prime[ (- over -)j ]一定已经被筛去了,被一个素因子比i小的数  
                //比一个合数数大的——"质数和该合数的乘积"可用一个更大的合数和比其小的质数相乘得到。  
            }  
        }  
    }   
    int main(){  
        memset(IsPrime,true,sizeof(IsPrime));  
        FindPrime ( 30 );  
        for(int i=0;i<PriN;i++)printf("%d ",Pri[i]);  
        return 0;  
    }








