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
int h[N], e[N], ne[N], idx, w[N];
int v[N], val[N];
int n, m;

struct query
{
    int a, b, dis, anc;
}q[N];

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dist[N], fa[N], siz[N], son[N], dep[N];
inline void dfs1(int u, int f)
{
    siz[u] = 1, fa[u] = f;
    dep[u] = dep[f] + 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dist[j] = dist[u] + w[i];
        val[j] = w[i];
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsiz)
        {
            maxsiz = siz[j];
            son[u] = j;
        }
    }
}

int top[N];
inline void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j); 
    }
}

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) return y;
    return x;
}

inline void dfs_sum(int u, int f)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs_sum(j, u);
        v[u] += v[j];
    }
}

inline bool check(int mid)
{
    int cnt = 0, maxdis = 0;
    memset(v, 0, sizeof v);
    for(int i = 1; i <= m; i ++ )
    {
        if(q[i].dis <= mid) continue;
        int x = q[i].a, y = q[i].b, z = q[i].anc;
        maxdis = max(maxdis, q[i].dis);
        cnt ++;
        v[x] ++, v[y] ++, v[z] -= 2;
    }
    dfs_sum(1, 1);
    for(int i = 1; i <= n; i ++ )
    {
        if(v[i] != cnt) continue;
        if(maxdis - val[i] <= mid) return true;
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        int anc = lca(a, b);
        int dis = dist[a] + dist[b] - 2 * dist[anc];
        q[i] = {a, b, dis, anc};
    }

    int l = 0, r = 1e9;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l << endl;

    return 0;
}