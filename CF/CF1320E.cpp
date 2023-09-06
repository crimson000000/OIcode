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

const int N = 2e6 + 10, M = 2e5 + 10;
int h[N], e[N], ne[N], idx;
vector<int> g[M];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct vir
{
    int v, tim, col, s;
    bool operator < (const vir& a) const
    {
        if(tim != a.tim) return tim < a.tim;
        else if(col != a.col) return col < a.col;
        return s > a.s;
    }

    bool operator > (const vir& a) const
    {
        return a < *this;
    }
}vr[M], I;

struct state
{
    int x;
    vir p;
    state(int _x, vir _p): x(_x), p(_p) {}

    bool operator < (const state& a) const
    {
        return p > a.p;
    }
};
priority_queue<state> heap;

namespace cn
{
    queue<int> q;
    bitset<M> st;
    
    inline void push(int u)
    {
        if(!st[u])
        {
            st[u] = true;
            q.push(u);
        }
    }

    inline void clear()
    {
        while(q.size())
        {
            int u = q.front();
            q.pop();
            g[u].clear();
            st[u] = false;
            vr[u] = I;
        }
    }
}

//-------------Tree Chain-------------------
inline void aded(int a, int b)
{
    g[a].emplace_back(b);
    g[b].emplace_back(a);
    cn::push(a);
    cn::push(b);
}

int fa[N], siz[N], son[N], dep[N];
inline void dfs1(int u, int f)
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

int top[N], dfn[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
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
    if(dep[x] < dep[y]) return x;
    return y;
}

inline int dis(int x, int y)
{
    return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
}

//-----------------------------------------
//-------------Virtual Tree----------------

int stk[M], tt;
int a[N], len;
int ask[N];

inline bool cmp(int x, int y)
{
    return dfn[x] < dfn[y];
}

inline void insert(int u)
{
    int lc = lca(u, stk[tt]);
    while(tt > 1 && dep[lc] <= dep[stk[tt - 1]]) 
    {
        aded(stk[tt - 1], stk[tt]);
        tt --;
    }
    if(stk[tt] != lc)
    {
        aded(stk[tt], lc);
        stk[tt] = lc;
    }
    stk[++ tt] = u;
}

void build(int k, int m)
{
    for(int i = 1; i <= k; i ++ )
    {
        a[i] = read();
        vr[a[i]].v = read();
        vr[a[i]].col = i;
        vr[a[i]].tim = 0;
        heap.emplace(a[i], vr[a[i]]);
    }
    len = k;
    for(int i = 1; i <= m; i ++ )
    {
        ask[i] = read();
        a[++ len] = ask[i];
    }

    sort(a + 1, a + len + 1, cmp);

    stk[tt = 1] = a[1];
    for(int i = 2; i <= len; i ++ ) insert(a[i]);
    while(tt > 1) 
    {
        aded(stk[tt - 1], stk[tt]);
        tt --;
    }
}

//-------------------------------------------
//----------------Dijkstra-------------------

inline vir upd(int lst, int now)
{
    int d = dis(lst, now);
    auto res = vr[lst];
    if(d <= res.s) 
    {
        res.s -= d;
        return res;
    }
    d -= res.s;
    int dt = (d - 1) / res.v + 1;
    res.s = dt * vr[lst].v - d;
    res.tim += dt;
    return res;
}

inline void dijkstra()
{
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        if(vr[t.x] < t.p) continue;

        for(auto v : g[t.x])
        {
            auto tmp = upd(t.x, v);
            if(tmp < vr[v])
            {
                vr[v] = tmp;
                heap.emplace(v, vr[v]);
            }
        }
    }
}

//----------------------------------------

void solve(int k, int m)
{
    cn::clear();
    build(k, m);
    dijkstra();

    for(int i = 1; i <= m; i ++ ) printf("%d ", vr[ask[i]].col);
    puts("");
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

    dfs1(1, 1);
    dfs2(1, 1);

    I.tim = I.col = n + 1;
    for(int i = 1; i <= n; i ++ ) vr[i] = I;
    
    int q = read();
    while(q -- )
    {
        int k = read(), m = read();
        solve(k, m);
    }

    return 0;
}