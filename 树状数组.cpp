#define lowbit(x) (x&(-x))
//单点修改，区间查询
void add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=y;
}
int query(int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)) tmp+=c[i];
	return tmp;
}
int main(){
	add(x,y);
	query(x);
}
//区间修改，单点查询
//采用差分的形式
void add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=y;
}
int query(int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)) tmp+=c[i];
	return tmp;
}
int main(){
	add(l,a);
	add(r+1,-a);
	query(x);
}
//区间修改+区间查询
//维护两个树状数组d[j],d[j]*j
void add(int *c,int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=y;
}
int query(int *c,int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)) tmp+=c[i];
	return tmp;
}
int ans(int x){
	return sum[x]+(x+1)*query(c1,x)-query(c2,x);
}
int main(){
	add(c1,l,a);
	add(c1,r+1,-a);
	add(c2,l,a*l);
	add(c2,r+1,-a*(r+1));
	cout<<ans(r)-ans(l-1);
}

