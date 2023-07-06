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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
int w[N];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dep[N], siz[N], fa[N], f[N], son1[N], son2[N];
void dfs1(int u, int father)
{
    siz[u] = w[u], dep[u] = dep[father] + 1;
    fa[u] = father;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == father) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        f[u] += f[v] + siz[v];
        if(siz[v] > siz[son1[u]]) son2[u] = son1[u], son1[u] = v;
        else if(siz[v] > siz[son2[u]]) son2[u] = v;
    }
}

int cut;
void dfs2(int u, int now, int sizm, int &res)
{
    res = min(now, res);
    int v;
    if(son1[u] == cut || siz[son2[u]] > siz[son1[u]]) v = son2[u];
    else v = son1[u];
    if(v && 2 * siz[v] > sizm)
        dfs2(v, now + sizm - 2 * siz[v], sizm, res);
}

void dfs3(int u, int &res)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u]) continue;

        cut = v;
        int up = INF, down = INF;
        
        for(int p = u; p; p = fa[p]) siz[p] -= siz[v];

        dfs2(1, f[1] - f[v] - siz[v] * (dep[v] - dep[1]), siz[1], up);
        dfs2(v, f[v], siz[v], down);

        res = min(res, up + down);
        for(int p = u; p; p = fa[p]) siz[p] += siz[v];
        dfs3(v, res);
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

    for(int i = 1; i <= n; i ++ ) w[i] = read();
    int ans = INF;
    dfs1(1, 0);
    dfs3(1, ans);

    cout << ans << endl;

    return 0;
}