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
const ll INF = 0x3f3f3f3f3f3f;
struct graph
{
    int h[N], e[N], ne[N], w[N], idx;
    bitset<N> st;
    queue<int> clean;

    graph()
    {
        memset(h, -1, sizeof h);
    }

    inline void add(int a, int b, int c = 0)
    {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
        if(!st[a])
        {
            clean.push(a);
            st[a] = true;
        }
    }

    inline void ADD(int a, int b, int c = 0)
    {
        add(a, b, c), add(b, a, c);
    }

    void clear()
    {
        while(clean.size()) 
        {
            h[clean.front()] = -1;
            st[clean.front()] = false;
            clean.pop();
        }
        idx = 0;
    }
}g, vg;

int fa[N], siz[N], son[N], dep[N];
int dist[N];
ll val[N];
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, fa[u] = f;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = g.h[u]; i != -1; i = g.ne[i])
    {
        int v = g.e[i];
        if(v == f) continue;
        dist[v] = dist[u] + g.w[i];
        val[v] = min(val[u], (ll)g.w[i]);
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
    }
}

int dfn[N], top[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = g.h[u]; i != -1; i = g.ne[i])
    {
        int v = g.e[i];
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

inline int distance(int x, int y)
{
    return dist[x] + dist[y] - (dist[lca(x, y)] << 1);
}

inline bool cmp(int x, int y)
{
    return dfn[x] < dfn[y];
}

int n, m;
int S[N];
int stk[N], tt;
bitset<N> st;

inline ll dfs(int u)
{
    ll sum = 0, tmp;
    for(int i = vg.h[u]; i != -1; i = vg.ne[i])
    {
        int v = vg.e[i];
        sum += dfs(v);
    }
    if(st[u]) tmp = val[u];
    else tmp = min(val[u], sum);
    st[u] = false;
    return tmp;
}

inline void solve(int c)
{
    vg.clear();
    sort(S + 1, S + c + 1, cmp);
    stk[tt = 1] = 1;

    for(int i = 1; i <= c; i ++ )
    {
        if(S[i] != 1)
        {
            int lc = lca(S[i], stk[tt]);
            while(1)
            {
                if(dep[lc] >= dep[stk[tt - 1]])
                {
                    if(lc != stk[tt])
                    {
                        vg.add(lc, stk[tt]);
                        if(lc != stk[tt - 1])
                            stk[tt] = lc;
                        else tt --;
                    }
                    break;
                }
                else
                {
                    vg.add(stk[tt - 1], stk[tt]);
                    tt --;
                }
            }
            stk[++ tt] = S[i];
        }
    }

    while(-- tt)
        vg.add(stk[tt], stk[tt + 1]);

    printf("%lld\n", dfs(1));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    val[1] = INF;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        g.add(a, b, c), g.add(b, a, c);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    m = read();

    while(m -- )
    {
        int k = read();
        for(int i = 1; i <= k; i ++ ) 
        {
            S[i] = read();
            st[S[i]] = true;
        }
        solve(k);
    }

    return 0;
}
