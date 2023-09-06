#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

#define int ll

const int N = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
ll a[N];
struct seg
{
    int l, r;
    ll sum, mx, smx, hmx, cnt;
    ll lzy1, lzy2, lzy3, lzy4;
    inline void clear()
    {
        lzy1 = lzy2 = lzy3 = lzy4 = 0;
    }
}t[N << 2];

inline void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].mx = max(t[p << 1].mx, t[p << 1 | 1].mx);
    t[p].hmx = max(t[p << 1].hmx, t[p << 1 | 1].hmx);
    if(t[p << 1].mx == t[p << 1 | 1].mx)
        t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt, 
        t[p].smx = max(t[p << 1].smx, t[p << 1 | 1].smx);
    
    if(t[p << 1].mx > t[p << 1 | 1].mx)
        t[p].cnt = t[p << 1].cnt, 
        t[p].smx = max(t[p << 1].smx, t[p << 1 | 1].mx);
    
    if(t[p << 1].mx < t[p << 1 | 1].mx)
        t[p].cnt = t[p << 1 | 1].cnt, 
        t[p].smx = max(t[p << 1].mx, t[p << 1 | 1].smx);
}

inline void update(int p, ll l1, ll l2, ll l3, ll l4)
{
    t[p].sum += (l1 * t[p].cnt + l3 * (t[p].r - t[p].l + 1 - t[p].cnt));
    t[p].hmx = max(t[p].hmx, t[p].mx + l2);
    t[p].mx += l1;
    if(t[p].smx != -INF) t[p].smx += l3;
    t[p].lzy2 = max(t[p].lzy2, t[p].lzy1 + l2), t[p].lzy1 += l1;
    t[p].lzy4 = max(t[p].lzy4, t[p].lzy3 + l4), t[p].lzy3 += l3;
}

inline void pushdown(int p)
{
    ll maxn = max(t[p << 1].mx, t[p << 1 | 1].mx);
    if(t[p << 1].mx == maxn) update(p << 1, t[p].lzy1, t[p].lzy2, t[p].lzy3, t[p].lzy4);
    else update(p << 1, t[p].lzy3, t[p].lzy4, t[p].lzy3, t[p].lzy4);
    if(t[p << 1 | 1].mx == maxn) update(p << 1 | 1, t[p].lzy1, t[p].lzy2, t[p].lzy3, t[p].lzy4);
    else update(p << 1 | 1, t[p].lzy3, t[p].lzy4, t[p].lzy3, t[p].lzy4);
    t[p].clear();
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].mx = t[p].hmx = t[p].sum = a[l];
        t[p].smx = -INF;
        t[p].cnt = 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change1(int p, int l, int r, ll v)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        update(p, v, v, v, v);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change1(p << 1, l, r, v);
    if(r > mid) change1(p << 1 | 1, l, r, v);
    pushup(p);
}

inline void change2(int p, int l, int r, ll v)
{
    if(t[p].mx <= v) return;
    if(t[p].l >= l && t[p].r <= r && t[p].smx < v)
    {
        update(p, v - t[p].mx, v - t[p].mx, 0, 0);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change2(p << 1, l, r, v);
    if(r > mid) change2(p << 1 | 1, l, r, v);
    pushup(p);
}

inline ll query1(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll res = 0;
    if(l <= mid) res += query1(p << 1, l, r);
    if(r > mid) res += query1(p << 1 | 1, l, r);
    return res;
}

inline ll query2(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].mx;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll res = -INF;
    if(l <= mid) res = max(res, query2(p << 1, l, r));
    if(r > mid) res = max(res, query2(p << 1 | 1, l, r));
    return res;
}

inline ll query3(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].hmx;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll res = -INF;
    if(l <= mid) res = max(res, query3(p << 1, l, r));
    if(r > mid) res = max(res, query3(p << 1 | 1, l, r));
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    build(1, 1, n);

    while(m -- )
    {
        int op = read(), l = read(), r = read();
        if(op == 1)
        {
            ll v = read();
            change1(1, l, r, v);
        }
        else if(op == 2)
        {
            ll v = read();
            change2(1, l, r, v);
        }
        else if(op == 3)
        {
            printf("%lld\n", query1(1, l, r));
        }
        else if(op == 4)
        {
            printf("%lld\n", query2(1, l, r));
        }
        else
        {
            printf("%lld\n", query3(1, l, r));
        }
    }

    return 0;
}
