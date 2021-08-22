//x^y
LL qpow(LL x,LL y){
	LL res=1;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}

