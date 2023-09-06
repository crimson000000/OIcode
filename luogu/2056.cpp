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
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct DeleteHeap
{
    priority_queue<int> a, d;

    inline int top()
    {
        while(a.size() && d.size() && (d.top() == a.top())) a.pop(), d.pop();
        if(a.empty()) return -INF;
        return a.top();
    }

    inline void erase(int val)
    {
        d.push(val); 
    }

    inline void insert(int val)
    {
        a.push(val);
    }

    inline int top2()
    {
        int maxn = top();
        if(maxn == -INF) 
            return -INF;
        a.pop();
        int ret = top();
        insert(maxn);
        return ret;
    }

    inline int size()
    {
        return a.size() - d.size();
    }
}ch[N], dist[N], glob;

namespace cao
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int f)
    {
        fa[u] = f, dep[u] = dep[f] + 1;
        siz[u] = 1;
        int maxsiz = -1;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
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
    inline void dfs2(int u, int t)
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

    inline int dist(int x, int y)
    {
        return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
    }
}

int siz[N], maxsiz[N], rt;
bitset<N> vis;
void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        calc_siz(v, u, sz);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt]) 
    {
        rt = u;
    }
}

inline void find_root(int u, int sz)
{
    rt = 0;
    maxsiz[rt] = INF;
    calc_siz(u, 0, sz);
    calc_siz(rt, 0, sz);
}

int par[N];

void dfz(int u)
{
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;
        find_root(v, siz[v]);
        par[rt] = u;
        dfz(rt);
    }
}

int state[N];
inline void on(int x)
{
    state[x] ^= 1;
    if(dist[x].size() >= 2)
    {
        glob.erase(dist[x].top() + dist[x].top2());
    }
    dist[x].insert(0);
    if(dist[x].size() >= 2)
    {
        glob.insert(dist[x].top() + dist[x].top2());
    }

    for(int p = x; par[p]; p = par[p])
    {
        int dis = cao::dist(x, par[p]);
        int ntop = ch[p].size() ? ch[p].top() : -1;
        ch[p].insert(dis);
        if(ntop != ch[p].top())
        {
            if(dist[par[p]].size() >= 2)
            {
                glob.erase(dist[par[p]].top() + dist[par[p]].top2());
            }
            if(ntop != -1 && dist[par[p]].size())
            {
                dist[par[p]].erase(ntop);
            }
            dist[par[p]].insert(ch[p].top());
            if(dist[par[p]].size() >= 2)
            {
                glob.insert(dist[par[p]].top() + dist[par[p]].top2());
            }
        }
    }
}

inline void off(int x)
{
    state[x] ^= 1;
    if(dist[x].size() >= 2)
    {
        glob.erase(dist[x].top() + dist[x].top2());
    }
    dist[x].erase(0);
    if(dist[x].size() >= 2)
    {
        glob.insert(dist[x].top() + dist[x].top2());
    }

    for(int p = x; par[p]; p = par[p])
    {
        int dis = cao::dist(x, par[p]);
        if(ch[p].top() == dis)
        {
            if(dist[par[p]].size() >= 2)
                glob.erase(dist[par[p]].top() + dist[par[p]].top2());
            dist[par[p]].erase(ch[p].top());
            ch[p].erase(dis);
            if(ch[p].size())
                dist[par[p]].insert(ch[p].top());
            if(dist[par[p]].size() >= 2)
                glob.insert(dist[par[p]].top() + dist[par[p]].top2());
        }
        else ch[p].erase(dis);
    }
}

int die;

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    cao::dfs1(1, 1);
    cao::dfs2(1, 1);
    find_root(1, n);
    dfz(rt);

    for(int i = 1; i <= n; i ++ ) on(i);

    m = read();
    die = n;
    while(m -- )
    {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'G')
        {
            if(die <= 1) printf("%d\n", die - 1);
            else printf("%d\n", glob.top());
        }
        else
        {
            int x = read();
            if(state[x]) 
            {
                off(x);
                die --;
            }
            else
            {
                on(x);
                die ++;
            }
        }
    }
    
    return 0;
}
