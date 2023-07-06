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
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
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
int n, m, cur;
int ans[N];

struct segment
{
    int v, sum;
}t[N << 2];

inline void pushup(int p)
{
    t[p].v = t[p << 1].v + t[p << 1 | 1].v;
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

void change(int p, int l, int r, int pos, int v)
{
    if(l == r) 
    {
        t[p].v += v;
        t[p].sum = l * t[p].v;
        return;
    }

    int mid = l + r >> 1;
    if(pos <= mid) change(p << 1, l, mid, pos, v);
    else change(p << 1 | 1, mid + 1, r, pos, v);
    pushup(p);
}

int query(int p, int l, int r, int v)
{
    if(!v) return 0;
    if(l == r) return l * v;
    int mid = l + r >> 1;
    if(t[p << 1].v >= v) return query(p << 1, l, mid, v);
    else return t[p << 1].sum + query(p << 1 | 1, mid + 1, r, v - t[p << 1].v);
}

int query1(int p, int l, int r, int pos)
{
    if(l == r) return t[p].sum;
    int mid = l + r >> 1;
    if(pos <= mid) return query1(p << 1, l, mid, pos);
    else return query1(p << 1 | 1, mid + 1, r, pos);
}

struct data
{
    int d, p, l;

    bool operator<(const data &D) const
    {
        return d > D.d;
    }
} a[N];

struct Q
{
    int id, g, l;
} q[N], lq[N], rq[N];

void solve(int lval, int rval, int st, int ed)
{
    if (st > ed || lval > rval)
        return;
    if (lval == rval)
    {
        // printf("---%d\n", ed - st + 1);
        for (int i = st; i <= ed; i ++)
            ans[q[i].id] = a[lval].d;
        return;
    }

    int mid = lval + rval >> 1;
    while(cur < mid)
        cur ++, change(1, 1, N - 1, a[cur].p, a[cur].l);
    while(cur > mid)
        change(1, 1, N - 1, a[cur].p, -a[cur].l), cur --;

    int lt = 0, rt = 0;
    // printf("mid: %d %d %d\n", mid, t[1].sum, query1(1, 1, N - 1, 1));
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].l > t[1].v) rq[++ rt] = q[i];
        else if(query(1, 1, N - 1, q[i].l) <= q[i].g) lq[++ lt] = q[i];
        else rq[++ rt] = q[i];

        // cout << query(1, 1, N - 1, q[i].l) << endl;
    }

    // printf("%d %d %d %d\n", lval, rval, lt, rt);

    for(int i = 1; i <= lt; i ++ ) q[i + st - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[i + st + lt - 1] = rq[i];

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

    for (int i = 1; i <= n; i++)
    {
        a[i].d = read(), a[i].p = read(), a[i].l = read();
    }

    a[++ n] = {-1, 0, 0x3f3f3f3f};
    sort(a + 1, a + n + 1);

    // for(int i = 1; i <= n; i ++ )
    //     printf("%d %d %d\n", a[i].d, a[i].l, a[i].p);

    for (int i = 1; i <= m; i++)
    {
        int D = read(), L = read();
        q[i] = {i, D, L};
    }

    solve(1, n, 1, m);

    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
