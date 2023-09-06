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

const int N = 1e6 + 10, INF = 0x7fffffff;
int a[N];
int n, m;

struct segment
{
    struct seg
    {
        int l, r;
        int hismax, maxn;
        int hisadd, add;
        int hiscov, cov;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].maxn = max(t[p << 1].maxn, t[p << 1 | 1].maxn);
        t[p].hismax = max(t[p << 1].hismax, t[p << 1 | 1].hismax);
    }

    inline void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        t[p].cov = INF, t[p].hiscov = -INF;
        if(l == r)
        {
            t[p].maxn = t[p].hismax = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void cov(int p, int v, int hv)
    {
        t[p].maxn = v;
        t[p].hismax = max(t[p].hismax, hv);
        t[p].cov = v;
        t[p].hiscov = max(t[p].hiscov, hv);
    }

    inline void add(int p, int v, int hv)
    {
        if(t[p].cov != INF) return cov(p, t[p].cov + v, t[p].cov + hv);
        t[p].hisadd = max(t[p].hisadd, hv + t[p].add);
        t[p].add += v;
        t[p].maxn += v;
        t[p].hismax = max(t[p].hismax, t[p].maxn - t[p].add + t[p].hisadd);
    }

    inline void pushdown(int p)
    {
        add(p << 1, t[p].add, t[p].hisadd);
        add(p << 1 | 1, t[p].add, t[p].hisadd);
        t[p].add = t[p].hisadd = 0;
        if(t[p].cov != INF)
        {
            cov(p << 1, t[p].cov, t[p].hiscov);
            cov(p << 1 | 1, t[p].cov, t[p].hiscov);
            t[p].cov = INF;
        }
    }

    inline int query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].maxn;
        pushdown(p);
        int res = -INF;
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) res = max(res, query(p << 1, l, r));
        if(r > mid) res = max(res, query(p << 1 | 1, l, r));
        return res;
    } 

    inline int queryh(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].hismax;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        int res = -INF;
        if(l <= mid) res = max(res, queryh(p << 1, l, r));
        if(r > mid) res = max(res, queryh(p << 1 | 1, l, r));
        return res;
    }

    inline void changeadd(int p, int l, int r, int val)
    {
        if(t[p].l >= l && t[p].r <= r) 
        {
            add(p, val, max(val, 0));
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) changeadd(p << 1, l, r, val);
        if(r > mid) changeadd(p << 1 | 1, l, r, val);
        pushup(p);
    }

    inline void changecov(int p, int l, int r, int val)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            cov(p, val, val);
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) changecov(p << 1, l, r, val);
        if(r > mid) changecov(p << 1 | 1, l, r, val);
        pushup(p);
    }
}t;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    t.build(1, 1, n);
    m = read();
    
    while(m -- )
    {
        char s[5];
        scanf("%s", s);
        int l = read(), r = read();
        if(s[0] == 'Q')
        {
            printf("%d\n", t.query(1, l, r));
        }
        else if(s[0] == 'A')
        {
            printf("%d\n", t.queryh(1, l, r));
        }
        else if(s[0] == 'P')
        {
            int val = read();
            t.changeadd(1, l, r, val);
        }
        else
        {
            int val = read();
            t.changecov(1, l, r, val);
        }
    }

    return 0;
}