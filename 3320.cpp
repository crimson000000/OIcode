#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int ll

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
int n, m;
set<int> s;
ll nowans;
bitset<N> st;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dist[N], dep[N], fa[N], siz[N], son[N];
inline void dfs1(int u, int fat)
{
    fa[u] = fat, dep[u] = dep[fat] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fat) continue;
        dist[v] = dist[u] + w[i];
        dfs1(v, u);
        siz[u] += siz[v];
        if(maxsiz < siz[v])
        {
            maxsiz = siz[v];
            son[u] = v;
        }
    }
}

int top[N], dfn[N], anti[N], tim;
inline void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
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

inline int dis(int x, int y)
{
    return dist[x] + dist[y] - (dist[lca(x, y)] << 1);
}

signed main()
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
        add(a, b, c);
        add(b, a, c);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    while(m -- )
    {
        int x = read();
        if(st[x])
        {
            // delete
            auto it = s.lower_bound(dfn[x]);
            int pre = -1, nxt = -1;
            if(it != s.begin())
            {
                it --;
                pre = anti[*it];
                it ++;
            }
            it ++;
            if(it != s.end())
            {
                nxt = anti[*it];
            }
            if(pre != -1) nowans -= dis(pre, x);
            if(nxt != -1) nowans -= dis(x, nxt);
            if(pre != -1 && nxt != -1) nowans += dis(pre, nxt);
            s.erase(dfn[x]);
        }
        else
        {
            s.insert(dfn[x]);
            auto it = s.lower_bound(dfn[x]);
            int pre = -1, nxt = -1;
            if(it != s.begin())
            {
                it --;
                pre = anti[*it];
                it ++;
            }
            it ++;
            if(it != s.end())
            {
                nxt = anti[*it];
            }
            if(pre != -1) nowans += dis(pre, x);
            if(nxt != -1) nowans += dis(x, nxt);
            if(pre != -1 && nxt != -1) nowans -= dis(pre, nxt);
        }
        st[x] = st[x] ^ 1;
        ll ans = nowans;
        if(s.size() > 1) ans += dis(anti[*s.begin()], anti[*(-- s.end())]);
        printf("%lld\n", ans);

        // for(auto it = s.begin(); it != s.end(); it ++ )
        //     printf("%d ", anti[*it]);
        // puts("");
    }

    return 0;
}
