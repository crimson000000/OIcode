#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;


const int N = 2e5 + 10;
int n, m;

struct segment{
    int l, r;
    int dat;
}t[N * 4];

void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    if(l == r) {
        int a;
        scanf("%d", &a);
        t[p].dat = a;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    t[p].dat = min(t[p << 1].dat, t[p << 1 | 1].dat);
}

int query(int p, int l, int r){
    if(t[p].l >= l && t[p].r <= r) return t[p].dat;
    
    int mid = t[p].l + t[p].r >> 1;
    int val = 0x3f3f3f3f;
    if(mid >= l) val = query(p << 1, l, r);
    if(mid < r) val = min(val, query(p << 1 | 1, l, r));
    return val;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    build(1, 1, n);
    
    while(m -- ){
        int a, b;
        scanf("%d%d", &a, &b);
        cout << query(1, a, b) << " ";
    }
    return 0;
}