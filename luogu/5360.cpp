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

unsigned int SA, SB, SC;
int lim;

namespace Genshin
{
    int getweight() {
        SA ^= SA << 16;
        SA ^= SA >> 5;
        SA ^= SA << 1;
        unsigned int t = SA;
        SA = SB;
        SB = SC;
        SC ^= t ^ SA;
        return SC % lim + 1;
    }
}

#define int long long

const int N = 2e6 + 10, M = 110, MM = 10010;
int h[N], e[N], ne[N], w[N], idx;
ll ans;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

struct edge
{
    int a, b, c;
    edge() {};
    edge(int _a, int _b, int _c): a(_a), b(_b), c(_c) {};

    bool operator < (const edge& e) const
    {
        return c < e.c;
    }
};
vector<edge> g;
int n, m;
int a[MM][M], b[MM][M];

struct MST
{
    vector<edge> E;
    int tot, sum;

    MST() {};
    MST(int a[])
    {
        tot = n, sum = 0;
        for(int i = 1; i < n; i ++ )
            E.emplace_back(i, i + 1, a[i]);
    }

    inline ll query()
    {
        ll ans = sum;
        for(auto e : E) ans += e.c;
        return ans;
    }
}pre[N], suf[N];
int is[N];

namespace uni
{
    int p[N];
    inline int find(int x)
    {
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
}

inline void link(edge a)
{
    add(a.a, a.b, a.c);
    add(a.b, a.a, a.c);
    ans += a.c;
}

bool dfs1(int u, int f)
{
    int s = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        s += dfs1(v, u);
    }
    is[u] |= (s >= 2);
    return s + is[u];
}

void dfs2(int u, int f, int lst, int val)
{
    if(is[u])
    {
        if(lst) g.emplace_back(is[u], lst, val);
        lst = is[u], ans -= val, val = 0;
    }
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs2(v, u, lst, max(w[i], val));
    }
}

inline MST merge(MST a, MST b, int c[])
{
    int tot = a.tot + b.tot;
    g.clear();
    for(auto u : a.E) g.emplace_back(u);
    for(auto v : b.E) g.emplace_back(v.a + a.tot, v.b + a.tot, v.c);

    for(int i = 1; i <= n; i ++ ) 
        g.emplace_back(a.tot - n + i, a.tot + i, c[i]);
    
    sort(g.begin(), g.end());

    for(int i = 1; i <= tot; i ++ )
    {
        uni::p[i] = i;
        is[i] = (i > tot - n || i <= n);
        h[i] = -1;
    }

    idx = ans = 0;

    for(auto v : g)
    {
        if(uni::find(v.a) != uni::find(v.b))
        {
            uni::p[uni::find(v.a)] = uni::find(v.b);
            link(v);
        }
    }

    dfs1(1, 0);
    idx = 0;

    for(int i = 1; i <= tot; i ++ )
        if(is[i]) is[i] = ++ idx;
    
    g.clear();
    dfs2(1, 0, 0, 0);
    MST res;
    res.tot = idx;
    res.sum = a.sum + b.sum + ans;
    res.E = g;
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    scanf("%d%d%u%u%u%d", &n, &m, &SA, &SB, &SC, &lim);
    int i, j;
    for(i = 1; i <= n; i ++)
    {
        for(j = 1; j <= m; j ++) 
        {
            a[j][i] = Genshin::getweight();
        }
    }

    for(i = 1; i < n; i ++)
        for(j = 1; j <= m; j ++)
            b[j][i] = Genshin::getweight();
    
    pre[1] = MST(b[1]), suf[m] = MST(b[m]);
    for(int i = 2; i < m; i ++ ) 
        pre[i] = merge(pre[i - 1], MST(b[i]), a[i - 1]);
    
    for(int i = m - 1; i > 1; i -- )
        suf[i] = merge(MST(b[i]), suf[i + 1], a[i]);

    int q = read();
    while(q -- )
    {
        int l = read(), r = read();
        printf("%lld\n", merge(suf[r + 1], pre[l - 1], a[m]).query());
    }

    return 0;
}