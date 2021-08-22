void exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) { x = 1; y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

LL inv(LL a)
{
	LL x, y;
	exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}

void init(){
	inv[1]=1;
	For(i,2,n)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}

//y=mod-2
LL qpow(LL x,LL y){
	LL res=1;
	while(y>1){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return x*res%mod;
}
