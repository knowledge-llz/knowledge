/*************************************************************************
	> File Name: 2.cpp
	> Author: Knowledge_llz
	> Mail: 925538513@qq.com 
	> Blog: https: https://www.cnblogs.com/Knowledge-Pig/ 
	> Created Time: 2021/1/20 21:41:28
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
multiset<int>Set;
multiset<int>::iterator it,eit;
multiset<int>::reverse_iterator rit;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	//set的插入
	Set.insert(1);
	Set.insert(3);
	Set.insert(3);	
	Set.insert(4);
	Set.insert(5);
	Set.insert(5);
	Set.insert(6);
	//set的删除
	Set.erase(3);
	//set的尾部迭代器
	eit=Set.end();
	cout<<"last value:"<<*(--eit)<<endl;
	//set的遍历1
	for(auto i:Set) cout<<i<<" ";
	cout<<endl;
	//set的遍历2
	eit++;
	for(it=Set.begin();it!=eit;++it) cout<<*it<<" ";
	cout<<endl;
	//set的find
	it=Set.find(1);
	cout<<"find value:"<<*it<<endl;
	//set的lower_bound
	it=Set.lower_bound(5);
	cout<<"lower_bound value:"<<*it<<endl;
	//set反向迭代器
	rit=Set.rbegin();
	cout<<*rit<<endl;
	for(;rit!=Set.rend();++rit)
		cout<<*rit<<" ";
	return 0;
}





//set自定义排序
//方法1

#include<iostream>
#include<set>
using namespace std;

struct Students
{
    string id;
    int age,height;
    Students(string s,int a,int h):id(s),age(a),height(h){}
    Students() {}
    bool operator <(const Students &s) const {
        if(id!=s.id) return id<s.id;
        else return age<s.age;
    }
};
int main(){
    set<Students> se;
    se.insert(Students("zhou",12,134));
    se.insert(Students("wu",13,42));
    se.insert(Students("zheng",34,43));
    se.emplace("wang",13,43);
    se.emplace("zhou",23,43);
    for(auto it=se.begin();it!=se.end();it++){
        cout<<it->id<<" "<<it->age<<" "<<it->height<<endl;
    }
    return 0;
}

//方法2

#include<iostream>
#include<set>
using namespace std;

struct Students
{
    string id;
    int age,height;
    Students(string s,int a,int h):id(s),age(a),height(h){}
    Students() {}
};

class comp{
public:
    bool operator()(const Students &s1,const Students &s2){
        if(s1.id!=s2.id) return s1.id<s2.id;
        return s1.age<s2.age;
    }
};

int main(){
    set<Students,comp> se;
    se.insert(Students("zhou",12,134));
    se.insert(Students("wu",13,42));
    se.insert(Students("zheng",34,43));
    se.emplace("wang",13,43);
    se.emplace("zhou",23,43);
    for(auto it=se.begin();it!=se.end();it++){
        cout<<it->id<<" "<<it->age<<" "<<it->height<<endl;
    }
    return 0;
}


//方法3

#include<iostream>
#include<set>
using namespace std;

struct Students
{
    string id;
    int age,height;
    Students(string s,int a,int h):id(s),age(a),height(h){}
    Students() {}
};

bool cmp(const Students &s1,const Students &s2){
    if(s1.id!=s2.id) return s1.id<s2.id;
    return s1.age<s2.age;
}

int main(){
    set<Students,decltype(cmp)*> se(cmp);
    se.insert(Students("zhou",12,134));
    se.insert(Students("wu",13,42));
    se.insert(Students("zheng",34,43));
    se.emplace("wang",13,43);
    se.emplace("zhou",23,43);
    for(auto it=se.begin();it!=se.end();it++){
        cout<<it->id<<" "<<it->age<<" "<<it->height<<endl;
    }
    return 0;
}

上述代码中，用decltype 来指出自定义操作的类型。当使用decltype 来获得一个函数指针类型时，必须加上一个* 来指出我们要使用一个给定函数类型的指针。用cmp 来初始化se对象，这表示当我们向se中插入元素时，通过调用cmp来为这些元素排序。可以使用cmp代替&cmp作为构造函数的参数，因为当我们使用一个函数的名字时，在需要的情况下会自动转化为一个指针，使用&cmp 效果也是一样的。
