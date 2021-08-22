/*************************************************************************
	> 该代码尚未经实战检验，可能存在错误，更多是提供一种思路
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https://www.cnblogs.com/Knowledge-Pig/ 
	> Created Time: 2021/2/23 15:15:43
 ************************************************************************/

#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define LL long long
#define pb push_back
#define fi first
#define se second
#define pr pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
int read(){
	char x=getchar(); int u=0,fg=0;
	while(!isdigit(x)){ if(x=='-') fg=1; x=getchar(); }
	while(isdigit(x)){ u=(u<<3)+(u<<1)+(x^48); x=getchar(); }
	return fg?-u:u;
}
/********************************计算几何必备***************************************/
//计算几何常用参数
const double pi=acos(-1.0);
const double inf=1e100;
const double eps=1e-6;
//计算几何判等函数
int dcmp(double d){
	if(fabs(d)<eps) return 0;
	if(d>0) return 1;
	return -1;
}
//计算几何化整函数
void to_integer(){
	double x=1.499999;
	int fx=floor(x); //向下取整函数
	int cx=ceil(x);	 //向上取整函数
	int rx=round(x); //四舍五入函数
	printf("%lf %d %d %d\n",x,fx,cx,rx);
}
/********************************点的定义***************************************/
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
//将点按x,y升序排序
	bool operator < (const Point& A){
	    if(x == A.x) return y < A.y;
	    return x < A.x;
	}
//等于运算
	bool operator == (const Point& A){
		if(dcmp(x-A.x)==0 && dcmp(y-A.y)==0) return true;
		else return false;
	}
};
/********************************向量的定义***************************************/
//向量的定义以及加减乘除
typedef Point Vector;
Vector operator +(Vector A,Vector B){
	return Vector(A.x+B.x,A.y+B.y);
}

Vector operator -(Vector A,Vector B){
	return Vector(A.x-B.x,A.y-B.y);
}

Vector operator *(Vector A,double p){
	return Vector(A.x*p,A.y*p);
}

Vector operator /(Vector A,double p){
	return Vector(A.x/p,A.y/p);
}

//内积
double Dot(Vector A,Vector B){
	return A.x*B.x+A.y*B.y;
}
//外积
double Cross(Vector A,Vector B){
	return A.x*B.y-A.y*B.x;
}
//取模
double Length(Vector A){
	return sqrt(Dot(A,A));
}
//弧度制下的夹角
double Angle(Vector A,Vector B){
	return acos(Dot(A,B) / Length(A) / Length(B));
}
//计算两向量构成的平行四边形有向面积
double Area2(Point A,Point B,Point C){
	return Cross(B-A,C-A);
}
//计算向量逆时针旋转后的向量
Vector Rotate(Vector A,double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
//逆时针旋转90度的单位法向量
Vector Normal(Vector A){
	double L=Length(A);
	return Vector(-A.y/L,A.x/L);
}
//判断bc是不是向ab的逆时针（左边）转向
bool ToLeftTest(Point a,Point b,Point c){
	return Cross(b-a,c-b)>0;
}
/*******************************直线***************************************/
struct Line{
	Point p; Vector v;
	Line(Point v,Vector p):p(p),v(v){}
	Point get_point(double t){
		return p+v*t;
	}
};
//判断点在直线上
//方法：直线上取两点求叉积是否为0
bool online(Point A,Point B,Point C){
	if(Cross(A-B,A-C)==0) return 1;
	else return 0;
}
//计算两直线的交点（保证直线相交后使用）
Point Get_Line_Intersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}
//点P到直线AB距离公式
double Distance_To_Line(Point P,Point A,Point B){
	Vector v1=B-A, v2=P-A;
	return fabs(Cross(v1,v2)/Length(v1));
}
//点P在直线上的投影点
Point Get_Lin_Projection(Point P,Point A,Point B){
	Vector v=B-A;
	return A+v*(Dot(v,P-A)/Dot(v,v));
}
//判断点是否在线段上
bool OnSegment(Point P,Point A,Point B){
	return dcmp(Cross(A-P,B-P))==0 && dcmp(Dot(A-P,B-P))<0;
}
//判断两线段是否相交(不允许顶点处相交)
bool Segment_Proper_Intersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1);
	double c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1);
	double c4=Cross(b2-b1,a2-b1);
	return (dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0);
}
//判断两线段是否相交(允许顶点处相交)
bool Segment_Intersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1);
	double c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1);
	double c4=Cross(b2-b1,a2-b1);
	if(!dcmp(c1) || !dcmp(c2) || !dcmp(c3) || !dcmp(c4)){
		bool f1=OnSegment(b1,a1,a2);
		bool f2=OnSegment(b2,a1,a2);
		bool f3=OnSegment(a1,b1,b2);
		bool f4=OnSegment(a2,b1,b2);
		return (f1|f2|f3|f4);
	}
	return (dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0);
}

/*******************************多边形***************************************/
//求多边形面积
bool PolygonArea(Point *p,int n){ //p为端点集合，n为个数
	double s=0;
	for(int i=1;i<n-1;++i)
		s+=Cross(p[i]-p[0],p[i+1]-p[0])/2; //?这里应该要除以2
	return s;
}

//判断点在多边形内
//转角法
/*
 * 看多边形相对与这个点转了多少度
 * 如果是零度，说明点在多边形
 * 如果是180，说明点在多边形边界上
 * 如果是360，说明点在多边形内
 * 但如果直接按照定义来算，则需要计算大量反三角函数，不仅速度慢，而且容易产生精度问题
 * 我们采用winding number绕数来计算
*/
//判断点是否在多边形内，若点在多边形内返回1，在多边形外部返回0，在多边形上返回-1
int is_Point_In_Polygon(Point p,vector<Point>poly){
	int wn=0,n=poly.size();
	for(int i=0;i<n;++i){
		if(OnSegment(p,poly[i],poly[(i+1)%n])) return -1;
		int k=dcmp(Cross(poly[(i+1)%n]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[(i+1)%n].y-p.y);
		if(k>0 && d1<=0 && d2>0) ++wn;
		if(k<0 && d2<=0 && d1>0) --wn;
	}
	return (wn!=0);
}
//若该多边形为凸多边形，只需要判断点是否在所有边的左边（按逆时针顺序排列的顶点集）ToLeftTest


/*******************************圆***************************************/
struct Circle{
	Point c;
	double r;
	Circle(Point c,double r):c(c),r(r){}
	Point point(double a){//通过圆心角求坐标
		return Point(c.x+cos(a)*r,c.y+sin(a)*r);
	}
};
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	return 0;
}
