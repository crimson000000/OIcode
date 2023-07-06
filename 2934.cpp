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
int h[N], e[N], ne[N], w[N], idx;
int dist[N], dep[N], fa[N];
bool st[N], on_tree[N], vis[N];
int nxt[N], ans[N];
int n, m;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& W) const
    {
        return w < W.w;
    }
}edge[N];
int top;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

priority_queue<PII, vector<PII>, greater<PII>> heap;
void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    dep[1] = 1;
    heap.push({0, 1});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        int ver = t.second, distance = t.first;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                fa[j] = ver;
                dist[j] = distance + w[i];
                dep[j] = dep[ver] + 1;
                heap.push({dist[j], j});
            }
        }
    }
}

// int fa[N], dep[N], son[N], siz[N];
// void dfs1(int u, int f)
// {
//     fa[u] = f, dep[u] = dep[f] + 1;
//     siz[u] = 1;
//     int maxsize = -1;
//     for(int i = h[u]; i != -1; i = ne[i])
//     {
//         if(!on_tree[i]) continue;
//         int j = e[i];
//         if(j == f) continue;
//         dfs1(j, u);
//         siz[u] += siz[j];
//         if(siz[j] > maxsize)
//         {
//             son[u] = j;
//             maxsize = siz[j];
//         }
//     }
// }

// int top[N];
// void dfs2(int u, int t)
// {
//     top[u] = t;
//     if(!son[u]) return;
//     dfs2(son[u], t);
//     for(int i = h[u]; i != -1; i = ne[i])
//     {
//         if(!on_tree[i]) continue;
//         int j = e[i];
//         if(j == fa[u] || j == son[u]) continue;
//         dfs2(j, j);
//     }
// }

int check(int x)
{
    if(x != nxt[x]) nxt[x] = check(nxt[x]);
    return nxt[x];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
        edge[i] = {a, b, c};
    }

    dijkstra();
    // dfs1(1, 1);
    // dfs2(1, 1);

    for(int u = 1; u <= n; u ++ )
    {
        ans[u] = -1;
        nxt[u] = u;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(fa[u] == v || fa[v] == u || u <= v) continue;
            edge[++ top] = {u, v, w[i] + dist[u] + dist[v]};
        }
    }

    sort(edge + 1, edge + 1 + top);
    for(int i = 1; i <= top; i ++ )
    {
        int a = edge[i].u, b = edge[i].v, val = edge[i].w;
        int pa = check(a), pb = check(b);
        while(pa != pb)
        {
            if(dep[pa] < dep[pb]) swap(pa, pb);
            ans[pa] = val - dist[pa];
            nxt[pa] = fa[pa];
            pa = check(pa);
        }
    }

    for(int i = 2; i <= n; i ++ ) cout << ans[i] << endl;

    return 0;
}