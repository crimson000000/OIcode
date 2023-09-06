#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int n, m;
int d[N];
struct node
{
    int l, r;
    int minn, add;
}t[N << 2];

inline void pushup(int p)
{
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        t[p << 1].add += t[p].add;
        t[p << 1 | 1].add += t[p].add;
        t[p << 1].minn += t[p].add;
        t[p << 1 | 1].minn += t[p].add;
        t[p].add = 0;
    }
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) 
    {
        t[p].minn = d[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].minn += val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

inline int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].minn;
    pushdown(p);
    int res = 0x3f3f3f3f;
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) res = min(res, query(p << 1, l, r));
    if(r > mid) res = min(res, query(p << 1 | 1, l, r));
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) d[i] = read();
    build(1, 1, n);

    for(int i = 1; i <= m; i ++ )
    {
        int d = read(), l = read(), r = read();
        int minnn = query(1, l, r);
        if(minnn < d)
        {
            puts("-1");
            cout << i << endl;
            return 0;
        }
        change(1, l, r, -d);
    }
    puts("0");

    return 0;
}