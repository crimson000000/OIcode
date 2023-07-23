#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
int siz[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int son[N], ans[N], fa[N];
int maxsiz[N], rt;
inline void dfs(int u, int f)
{
    siz[u] = 1;
    fa[u] = f;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    int id = u, maxnow = maxsiz[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u]) continue;
        int it = ans[v], pre = max(maxsiz[it], siz[u] - siz[it]);
        int p = it;
        while(fa[it] != u)
        {
            it = fa[it];
            int nw = max(maxsiz[it], siz[u] - siz[it]);
            if(nw < pre) pre = nw, p = it;
            else break;
        }
        if(maxnow > pre)
        {
            maxnow = pre;
            id = p;
        }
    }
    ans[u] = id;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 2; i <= n; i ++ )
    {
        int a = read();
        add(a, i), add(i, a);
    }

    dfs(1, 0);

    while(m -- )
    {
        int x = read();
        printf("%d\n", ans[x]);
    }

    return 0;
}
