#define LOCAL
#include <bits/stdc++.h>

using namespace std;
#define int long long
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
const ll INF = 0x3f3f3f3f3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int hs[N];

// here is kruskal
struct edge
{
    int u, v, w;
    bool operator < (const edge &a) const
    {
        return w < a.w;
    }
}ed[N];
int unuse[N], cnt;
int p[N];
int n, m;
int id[N], tot;

inline void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

namespace spfa
{
    ll dist[45][100010];
    bitset<N> st;
    priority_queue<PII, vector<PII>, greater<PII>> q;

    void spaf(int s, int id)
    {
        for(int i = 1; i <= n; i ++ ) dist[id][i] = INF, st[i] = false;
        while(q.size()) q.pop();
        q.push({0, s});
        dist[id][s] = 0;

        while(q.size())
        {
            auto t = q.top();
            q.pop();
            
            int u = t.second;
            if(st[u]) continue;
            st[u] = true;

            for(int i = hs[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(dist[id][v] > dist[id][u] + w[i])
                {
                    dist[id][v] = dist[id][u] + w[i];
                    q.push({dist[id][v], v});
                }
            }
        }
    }
}

void kruskal()
{
    sort(ed + 1, ed + m + 1);
    for(int i = 1; i <= n; i ++ ) p[i] = i;

    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].u, b = ed[i].v, c = ed[i].w;
        if(find(a) == find(b))
        {
            if(!id[a]) 
            {
                id[a] = ++ tot;
                spfa::spaf(a, id[a]);
            }
            if(!id[b]) 
            {
                id[b] = ++ tot;
                spfa::spaf(b, id[b]);
            }

            continue;
        }
        p[find(a)] = find(b);
        add(h, a, b, c), add(h, b, a, c);
    }
}

int fa[N], dep[N], siz[N], son[N];
ll dist[N];
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1;
    fa[u] = f;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dist[v] = dist[u] + w[i];
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
    }
}

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

inline ll dis(int x, int y)
{
    return dist[x] + dist[y] - 2 * dist[lca(x, y)];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        ed[i] = {a, b, c};
        add(hs, a, b, c), add(hs, b, a, c);
    }

    kruskal();
    dfs1(1, 1);
    dfs2(1, 1);

    int q = read();
    while(q -- )
    {
        int x = read(), y = read();

        ll res = INF;
        res = min(res, dis(x, y));
        for(int i = 1; i <= tot; i ++ )
            res = min(res, spfa::dist[i][x] + spfa::dist[i][y]);

        printf("%lld\n", res);
    }

    return 0;
}