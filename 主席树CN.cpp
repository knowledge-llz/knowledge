#include<cstdio>
#include<iostream>
#include<algorithm>

#define N 200001
#define M 4000001
#define For(a, b, c) for(a = b; a <= c; ++a)
#define Forr(a, b, c) for(a = b; a >= c; --a)
using namespace std;
typedef long long LL;
int n, m, cnt, id[N];
struct node{
    int id;
    LL x;
}ls[N];

inline LL read(){
    LL u = 0, f = 1;
    char x = getchar();
    while(!isdigit(x)){ if(x == '-') f = -1; x = getchar(); }
    while(isdigit(x)) u = (u << 3) + (u << 1) + (x ^ 48), x = getchar();
    return u * f;
}

inline bool cmp(node a, node b){
    return a.x < b.x;
}

inline void pre(){
    sort(ls + 1, ls + cnt + 1, cmp);
    int i;
    For(i, 1, cnt) id[ls[i].id] = i;
}

struct Chairman_Tree{
#define L(x) ch[x][0]
#define R(x) ch[x][1]
    int e, rt[N], w[M], ch[M][2];
    inline void cpy(int x, int y){ w[x] = w[y]; L(x) = L(y); R(x) = R(y); }
    void insert(int &q, int l, int r, int x){
        cpy(++e, q);
        ++w[q = e];
        if(l == r) return ;
        int mid = l + r >> 1;
        if(x <= mid) insert(L(q), l, mid, x);
        else insert(R(q), mid + 1, r, x);
    }
    int query(int t1, int t2, int l, int r, int k){
        if(l == r) return l;
        int ws = w[L(t2)] - w[L(t1)], mid = l + r >> 1;
        if(ws >= k) return query(L(t1), L(t2), l, mid, k);
        else return query(R(t1), R(t2), mid + 1, r, k - ws);
    }
    inline void solve(){
        int i, c = 0, l, r, k;
        For(i, 1, n) rt[i] = rt[i - 1], insert(rt[i], 1, cnt, id[++c]);
        For(i, 1, m){
            l = read(), r = read(), k = read();
            printf("%d\n", ls[query(rt[l - 1], rt[r], 1, cnt, k)].x);
        }
    }
}ctr;

int main(){
    int i, a;
    n = read(), m = read();
    Forr(i, n, 1) a = read(), ls[++cnt].x = a, ls[cnt].id = cnt;
    pre();
    ctr.solve();
    return 0;
}
