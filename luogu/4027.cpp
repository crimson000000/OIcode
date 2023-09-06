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
ld f[N];
int n, s;
ld a[N], b[N], R[N];

struct line
{
    ld k, b;
}li[N];

inline ld get(int id, ld x)
{
    return li[id].k * x + li[id].b;
}

struct lct
{
    int l, r;
    int maxn;
}t[N];
int rt, cnt;

inline void insert(int &p, ld l, ld r, int id)
{
    if(!p) p = ++ cnt;
    if(!t[p].maxn)
    {
        t[p].maxn = id;
        return;
    }
    ld mid = (l + r) / 2;
    if(get(t[p].maxn, mid) < get(id, mid)) swap(t[p].maxn, id);
    if(get(t[p].maxn, l) < get(id, l)) insert(t[p].l, l, mid, id);
    if(get(t[p].maxn, r) < get(id, r)) insert(t[p].r, mid, r, id);
}

inline ld query(int p, ld l, ld r, ld x)
{
    if(!p) return -1e20;
    ld mid = (l + r) / 2;
    ld ans = get(t[p].maxn, x);
    if(x <= mid) ans = max(ans, query(t[p].l, l, mid, x));
    else ans = max(ans, query(t[p].r, mid, r, x));
    return ans;
}

inline ld X(int i)
{
    return R[i] * f[i] / (a[i] * R[i] + b[i]);
}

inline ld Y(int i)
{
    return f[i] / (a[i] * R[i] + b[i]);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), s = read();

    for(int i = 1; i <= n; i ++ )
    {
        cin >> a[i] >> b[i] >> R[i];
    }

    f[1] = s;
    li[1].k = X(1), li[1].b = Y(1);
    insert(rt, -1, 101, 1);

    for(int i = 2; i <= n; i ++ )
    {
        f[i] = max(query(rt, -1, 101, a[i] / b[i]) * b[i], f[i - 1]);
        li[i].k = X(i), li[i].b = Y(i);
        insert(rt, -1, 101, i);
        // cout << f[i] << endl;
    }

    printf("%.3Lf\n", f[n]);
    
    return 0;
}
