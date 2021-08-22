//#include<complex>
#include<bits/stdc++.h>
using namespace std;
typedef complex<double> Point;
typedef Point Vector;
const double eps = 1e-9;
int dcmp(double x){
    if(fabs(x) < eps)
        return 0;
    if(x < 0)
        return -1;
    return 1;
}
double Length(Vector A){
    return abs(A);
}
double Dot(Vector A, Vector B){//conj(a+bi)返回共轭复数a-bi
    return real(conj(A)*B);
}
double Cross(Vector A, Vector B){
    return imag(conj(A)*B);
}
Vector Rotate(Vector A, double rad){
    return A*exp(Point(0, rad));//exp(p)返回以e为底复数的指数
}
int main(){
	complex<double> z1,z2;
	z1=5.0+3i;
	z2=(5,4);
	cout<<z1/z2<<endl;
	return 0;
}
