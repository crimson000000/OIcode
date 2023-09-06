#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define int long long 
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

const int N = 1e6 + 10;
int n, m, tt;

struct segment
{
    int l, r;
    ll sum, add;
};

struct segmenttree
{
    segment t[N << 2];

    inline void pushup(int p)
    {
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    }

    inline void pushdown(int p)
    {
        if(t[p].add)
        {
            t[p << 1].add += t[p].add;
            t[p << 1 | 1].add += t[p].add;
            t[p << 1].sum += (t[p << 1].r - t[p << 1].l + 1) * t[p].add;
            t[p << 1 | 1].sum += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].add;
            t[p].add = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void change(int p, int l, int r, int val)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].sum += (t[p].r - t[p].l + 1) * val;
            t[p].add += val;
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) change(p << 1, l, r, val);
        if(r > mid) change(p << 1 | 1, l, r, val);
        pushup(p);
    }

    ll query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].sum;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        ll sum = 0;
        if(l <= mid) sum += query(p << 1, l, r);
        if(r > mid) sum += query(p << 1 | 1, l, r);
        return sum;
    }
} tree;

struct Q
{
    int op, l, r;
    ll c;
}q[N], lq[N], rq[N];
int ans[N];

void solve(int lval, int rval, int st, int ed)
{
    if(st > ed) return;
    if(lval == rval)
    {
        for(int i = st; i <= ed; i ++ )
            if(q[i].op > 0) 
                ans[q[i].op] = lval;
        return;
    }
    int mid = lval + rval >> 1;
    int lt = 0, rt = 0;
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op == 0)
        {
            if(q[i].c > mid) tree.change(1, q[i].l, q[i].r, 1), rq[++ rt] = q[i];
            else lq[++ lt] = q[i];
        }
        else
        {
            int cnt = tree.query(1, q[i].l, q[i].r);
            if(q[i].c <= cnt) rq[++ rt] = q[i];
            else q[i].c -= cnt, lq[++ lt] = q[i];
        }
    }

    for(int i = st; i <= ed; i ++ )
        if(q[i].op == 0 && q[i].c > mid)
            tree.change(1, q[i].l, q[i].r, -1);
    
    for(int i = 1; i <= lt; i ++ ) q[st + i - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[st + lt + i - 1] = rq[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int op = read();
        if(op == 1)
        {
            int l = read(), r = read();
            ll c;
            scanf("%lld", &c);
            q[i] = {0, l, r, c};
        }
        else
        {
            int l = read(), r = read();
            ll c;
            scanf("%lld", &c);
            q[i] = {++ tt, l, r, c};
        }
    }

    tree.build(1, 1, N - 1);

    solve(-N + 1, N - 1, 1, m);
    for(int i = 1; i <= tt; i ++ )
        printf("%d\n", ans[i]);
    
    return 0;
}
