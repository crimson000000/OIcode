#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
ll buc[N], *p = buc;
ll *f[N], *g[N];
int n;
ll ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], son[N];
inline void dfs1(int u, int fat)
{
    fa[u] = fat;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fat) continue;
        dfs1(v, u);
        if(dep[v] > dep[son[u]]) son[u] = v;
    }
    dep[u] = dep[son[u]] + 1;
}

inline void dfs(int u)
{
    f[u][0] = 1;
    if(son[u])
    {
        f[son[u]] = f[u] + 1;
        g[son[u]] = g[u] - 1;
        dfs(son[u]);
    }

    ans += g[u][0];

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        f[v] = p, p += dep[v] << 1;
        g[v] = p, p += dep[v] << 1;
        dfs(v);
        for(int i = 0; i < dep[v]; i ++ )
        {
            ans += g[u][i + 1] * f[v][i];
            if(i) ans += f[u][i - 1] * g[v][i];
        }

        for(int i = 0; i < dep[v]; i ++ )
        {
            g[u][i + 1] += f[u][i + 1] * f[v][i];
            if(i) g[u][i - 1] += g[v][i];
            f[u][i + 1] += f[v][i];
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    f[1] = p, p += dep[1] << 1;
    g[1] = p, p += dep[1] << 1;
    dfs(1);

    cout << ans << endl;

    return 0;
}