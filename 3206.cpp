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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, Q;

struct edge
{
    int a, b, c, id;
    bool operator < (const edge& e) const
    {
        return c < e.c;
    }
}e[20][N >> 1], f[N], g[N];
int c[N], a[N], b[N], ct[N];

struct uniset
{
    int p[N];
    inline int find(int x)
    {
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    inline void clear(int tot)
    {
        for(int i = 1; i <= tot; i ++ ) 
        {
            p[f[i].a] = f[i].a;
            p[f[i].b] = f[i].b;
        }
    }

    inline void merge(int x, int y)
    {
        x = find(x), y = find(y);
        p[x] = y;
    }
}uni;

ll ans[N];
inline void cdq(int l, int r, int now, int tot, ll sum)
{
    if(l == r) ct[a[l]] = b[l];
    for(int i = 1; i <= tot; i ++ )
    {
        e[now][i].c = ct[e[now][i].id];
        c[e[now][i].id] = i;
        f[i] = e[now][i];
    }
    if(l == r)
    {
        ans[l] = sum;
        uni.clear(tot);
        sort(f + 1, f + tot + 1);
        for(int i = 1; i <= tot; i ++ )
        {
            int a = f[i].a, b = f[i].b, c = f[i].c;
            if(uni.find(a) == uni.find(b)) continue;
            uni.merge(a, b);
            ans[l] += c;
        }
        return;
    }

    uni.clear(tot);
    for(int i = l; i <= r; i ++ ) f[c[a[i]]].c = -INF;
    sort(f + 1, f + tot + 1);
    int tt = 0;
    for(int i = 1; i <= tot; i ++ )
    {
        int a = f[i].a, b = f[i].b, c = f[i].c;
        if(uni.find(a) == uni.find(b)) continue;
        uni.merge(a, b);
        if(c != -INF) 
        {
            g[++ tt] = f[i];
            sum += f[i].c;
        }
    }

    uni.clear(tot);
    for(int i = 1; i <= tt; i ++ ) 
    {
        uni.merge(g[i].a, g[i].b);
    }

    tt = 0;
    for(int i = 1; i <= tot; i ++ )
    {
        int a = f[i].a, b = f[i].b, c = f[i].c;
        if(uni.find(a) == uni.find(b)) continue;
        a = uni.find(a), b = uni.find(b);
        f[++ tt].a = a;
        f[tt].b = b;
        f[tt].c = f[i].c;
        f[tt].id = f[i].id;
    }

    tot = tt;
    tt = 0;
    uni.clear(tot);
    for(int i = 1; i <= tot; i ++ ) c[f[i].id] = i;
    for(int i = l; i <= r; i ++ ) f[c[a[i]]].c = INF;

    sort(f + 1, f + tot + 1);
    for(int i = 1; i <= tot; i ++ )
    {
        int a = f[i].a, b = f[i].b, c = f[i].c;
        if(c == INF) 
        {
            f[++ tt] = f[i];
            continue;
        }
        if(uni.find(a) == uni.find(b)) continue;
        uni.merge(a, b);
        f[++ tt] = f[i];
    }
    tot = tt;
    for(int i = 1; i <= tot; i ++ ) e[now + 1][i] = f[i];
    int mid = l + r >> 1;
    cdq(l, mid, now + 1, tot, sum);
    cdq(mid + 1, r, now + 1, tot, sum);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), Q = read();

    for(int i = 1; i <= n; i ++ ) uni.p[i] = i;

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        e[0][i] = {a, b, c, i};
        ct[i] = c;
    }

    for(int i = 1; i <= Q; i ++ ) a[i] = read(), b[i] = read();

    cdq(1, Q, 0, m, 0);

    for(int i = 1; i <= Q; i ++ ) cout << ans[i] << endl;
   
    return 0;
}
