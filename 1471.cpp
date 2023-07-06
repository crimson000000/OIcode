#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;

double sq(double x){
    return x * x;
}

struct segment{
    int l, r;
    double sum, ssub;
    double add;
}t[N * 4];
int n, m;
double a[N];

void pushup(int p){
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].ssub = t[p << 1].ssub + t[p << 1 | 1].ssub;
}

void pushdown(int p){
    if(t[p].add){
        t[p << 1].ssub += (t[p << 1].r - t[p << 1].l + 1) * sq(t[p].add) + 2 * t[p].add * t[p << 1].sum;
        t[p << 1 | 1].ssub += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * sq(t[p].add) + 2 * t[p].add * t[p << 1 | 1].sum;
        t[p << 1].sum += (t[p << 1].r - t[p << 1].l + 1) * t[p].add;
        t[p << 1 | 1].sum += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].add;
        t[p << 1].add += t[p].add;
        t[p << 1 | 1].add += t[p].add;
        t[p].add = 0;
    }
}

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    if(l == r){
        t[p].sum = a[l];
        t[p].ssub = sq(a[l]);
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int l, int r, double val){
    if(l <= t[p].l && t[p].r <= r){
        t[p].ssub += 2 * val * t[p].sum + (t[p].r - t[p].l + 1) * sq(val);
        t[p].add += val;
        t[p].sum += val * (t[p].r - t[p].l + 1);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

double query1(int p, int l, int r){
    if(l <= t[p].l && t[p].r <= r){
        return t[p].sum;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    double sum = 0;
    if(l <= mid) sum += query1(p << 1, l, r);
    if(r > mid) sum += query1(p << 1 | 1, l, r);
    return sum;
}

double query2(int p, int l, int r){
    if(l <= t[p].l && t[p].r <= r){
        return t[p].ssub;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    double ssub = 0;
    if(l <= mid) ssub += query2(p << 1, l, r);
    if(r > mid) ssub += query2(p << 1 | 1, l, r);
    return ssub;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++ ) scanf("%lf", &a[i]);

    build(1, 1, n);

    while(m -- ){
        int op, l, r;
        double k;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1){
            scanf("%lf", &k);
            change(1, l, r, k);
        }
        else if(op == 2){
            double s = query1(1, l, r);
            printf("%.4f\n", s / (r - l + 1));
        }
        else{
            double s = query1(1, l, r) / (r - l + 1);
            change(1, l, r, -s);
            printf("%.4f\n", query2(1, l, r) / (r - l + 1));
            change(1, l, r, s);
        }
    }
    return 0;
}