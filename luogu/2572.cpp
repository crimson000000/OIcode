#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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
struct node
{
    int l, r;
    int cnt, lmax, rmax, maxn;
    int zlmax, zrmax, zmaxn;
    bool rev;
    int cov;
}t[N << 2];
int n, m;

inline node empty()
{
    node res;
    res.l = res.r = res.cnt = res.lmax = res.rmax = res.maxn = 0;
    res.zlmax = res.zrmax = res.zmaxn = 0;
    res.rev = false;
    res.cov = -1;
    return res;
}

inline void pushup(node& a, node& l, node& r)
{
    a.cnt = l.cnt + r.cnt;
    
    a.lmax = l.lmax;
    if(l.cnt == l.r - l.l + 1) a.lmax = l.r - l.l + 1 + r.lmax;
    a.rmax = r.rmax;
    if(r.cnt == r.r - r.l + 1) a.rmax = r.r - r.l + 1 + l.rmax;

    a.zlmax = l.zlmax;
    if(l.cnt == 0) a.zlmax = l.r - l.l + 1 + r.zlmax;
    a.zrmax = r.zrmax;
    if(r.cnt == 0) a.zrmax = r.r - r.l + 1 + l.zrmax;
    
    a.maxn = max(max(l.maxn, r.maxn), l.rmax + r.lmax);
    a.zmaxn = max(max(l.zmaxn, r.zmaxn), l.zrmax + r.zlmax);
}

inline void pushup(int p)
{
    pushup(t[p], t[p << 1], t[p << 1 | 1]);
}

inline void reverse(int p)
{
    if(t[p].cov != -1) t[p].cov ^= 1;
    swap(t[p].lmax, t[p].zlmax);
    swap(t[p].rmax, t[p].zrmax);
    swap(t[p].maxn, t[p].zmaxn);
    t[p].cnt = t[p].r - t[p].l + 1 - t[p].cnt;
    t[p].rev ^= 1;
}

inline void cover(int p, int v)
{
    if(v)
    {
        t[p].cnt = t[p].r - t[p].l + 1;
        t[p].lmax = t[p].rmax = t[p].maxn = t[p].cnt;
        t[p].zlmax = t[p].zrmax = t[p].zmaxn = 0;
        t[p].cov = 1;
    }
    else
    {
        t[p].cnt = 0;
        t[p].lmax = t[p].rmax = t[p].maxn = 0;
        t[p].zlmax = t[p].zrmax = t[p].zmaxn = t[p].r - t[p].l + 1;
        t[p].cov = 0;
    }
}

inline void pushdown(int p)
{
    if(t[p].cov != -1)
    {
        cover(p << 1, t[p].cov);
        cover(p << 1 | 1, t[p].cov);
        t[p].cov = -1;
        t[p].rev = 0;
    }
    if(t[p].rev)
    {
        reverse(p << 1);
        reverse(p << 1 | 1);
        t[p].rev = 0;
    }
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].cov = -1, t[p].rev = 0;
    if(l == r)
    {
        int x = read();
        t[p].cnt = t[p].maxn = t[p].lmax = t[p].rmax = x;
        t[p].zlmax = t[p].zrmax = t[p].zmaxn = !x;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void cchange(int p, int l, int r, int v)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        // pushdown(p);
        cover(p, v);
        // pushdown(p);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cchange(p << 1, l, r, v);
    if(r > mid) cchange(p << 1 | 1, l, r, v);
    pushup(p);
}

inline void rchange(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        // pushdown(p);
        reverse(p);
        // pushdown(p);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) rchange(p << 1, l, r);
    if(r > mid) rchange(p << 1 | 1, l, r);
    pushup(p);
}

inline node query(int p, int l, int r)
{
    pushdown(p);
    if(t[p].l >= l && t[p].r <= r) return t[p];
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(r <= mid) return query(p << 1, l, r);
    if(l > mid) return query(p << 1 | 1, l, r);
    pushdown(p);
    auto lans = query(p << 1, l, r), rans = query(p << 1 | 1, l, r);
    node res;
    pushup(res, lans, rans);
    return res;
}

inline int query(int p, int pos)
{
    if(t[p].l == t[p].r) return t[p].maxn;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) return query(p << 1, pos);
    else return query(p << 1 | 1, pos);
}

inline void pushdown_all(int p)
{
    pushdown(p);
    if(t[p].l == t[p].r) return;
    pushdown_all(p << 1);
    pushdown_all(p << 1 | 1);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();

    build(1, 1, n);

    while(m -- )
    {
        int op = read(), l = read() + 1, r = read() + 1;
        if(op == 0)
        {
            cchange(1, l, r, 0);
        }
        else if(op == 1)
        {
            cchange(1, l, r, 1);
        }
        else if(op == 2)
        {
            rchange(1, l, r);
        }
        else if(op == 3)
        {
            node res = query(1, l, r);
            printf("%d\n", res.cnt);
            // cout << res.l << ' ' << res.r << endl;
        }
        else 
        {
            node res = query(1, l, r);
            printf("%d\n", res.maxn);
            // cout << res.l << ' ' << res.r << endl;
        }

        // pushdown_all(1);

        // for(int i = 1; i <= n; i ++ ) cout << query(1, i) << ' ';
        // puts("");
        // cout << t[1].maxn << ' ' << t[1].zmaxn << endl;
    }
    
    return 0;
}
