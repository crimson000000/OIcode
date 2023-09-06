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
struct node
{
    int l, r;
    ll sum, add;
}t[N * 10];
int root[N], cnt;
int whe[N];
int nowtim, ti;
int n, m;
int a[N];

inline void pushup(int p, int l, int r)
{
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum + (r - l + 1) * t[p].add;
}

inline int build(int l, int r)
{
    int p = ++ cnt;
    if(l == r)
    {
        t[p].sum = a[l];
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = build(l, mid);
    t[p].r = build(mid + 1, r);
    pushup(p, l, r);
    return p;
}

inline ll query(int p, int l, int r, int L, int R)
{
    if(r < L || l > R || !p) return 0;
    if(l >= L && r <= R) return t[p].sum;
    ll res = t[p].add * (min(r, R) - max(l, L) + 1);
    int mid = l + r >> 1;
    if(L <= mid) res += query(t[p].l, l, mid, L, R);
    if(R > mid) res += query(t[p].r, mid + 1, r, L, R);
    return res;
}

inline void change(int &p, int q, int l, int r, int L, int R, ll v)
{
    p = ++ cnt;
    t[p] = t[q];
    if(L <= l && r <= R)
    {
        t[p].add += v;
        t[p].sum += (r - l + 1) * v;
        return;
    }
    int mid = l + r >> 1;
    if(L <= mid) change(t[p].l, t[q].l, l, mid, L, R, v);
    if(R > mid) change(t[p].r, t[q].r, mid + 1, r, L, R, v);
    pushup(p, l, r);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    root[0] = build(1, n);

    while(m -- )
    {
        char op[2];
        scanf("%s", op);
        if(op[0] == 'C')
        {
            whe[++ nowtim] = ++ ti;
            int l = read(), r = read(), d = read();
            change(root[ti], root[ti - 1], 1, n, l, r, d);
        }
        else if(op[0] == 'Q')
        {
            int l = read(), r = read();
            printf("%lld\n", query(root[ti], 1, n, l, r));
        }
        else if(op[0] == 'H')
        {
            int l = read(), r = read(), k = read();
            printf("%lld\n", query(root[whe[k]], 1, n, l, r));
        }
        else
        {
            nowtim = read();
            root[++ ti] = root[whe[nowtim]];
        }
    }
    
    return 0;
}
