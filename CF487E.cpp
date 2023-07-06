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
int hs[N];
int w[M];
int n, m, q;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace tj
{
    int dfn[M], low[M], timstamp;
    int stk[M], tt;
    int cnt;
    void tarjan(int u)
    {
        dfn[u] = low[u] = ++ timstamp;
        stk[++ tt] = u;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u])
                {
                    cnt ++;
                    int y;
                    // printf("the square point is %d\n", cnt);
                    // printf("it has: ");
                    do {
                        y = stk[tt -- ];
                        // printf("%d ", y);
                        add(hs, cnt, y), add(hs, y, cnt);
                    } while(y != v);
                    // printf("%d\n", u);
                    add(hs, cnt, u), add(hs, u, cnt);
                }
            }
            else low[u] = min(low[u], dfn[v]);
        }
    }
}

namespace tc
{
    multiset<int> sqval[M];
    int fa[M], siz[M], son[M], dep[M];
    void dfs1(int u, int f)
    {
        fa[u] = f, dep[u] = dep[f] + 1;
        siz[u] = 1;
        int maxsiz = -1;
        for(int i = hs[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            if(u > n) sqval[u].insert(w[v]);
            dfs1(v, u);
            siz[u] += siz[v];
            if(siz[v] > maxsiz)
            {
                maxsiz = siz[v];
                son[u] = v;
            }
        }
        if(u > n) w[u] = *sqval[u].begin();
    }

    int top[M], dfn[M], anti[M], tim;
    void dfs2(int u, int t)
    {
        top[u] = t;
        dfn[u] = ++ tim;
        anti[tim] = u;
        if(!son[u]) return;
        dfs2(son[u], t);
        for(int i = hs[u]; i != -1; i = ne[i])
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

    struct segment
    {
        int l, r;
        int minn;
    }t[N];

    inline void pushup(int p)
    {
        t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r)
        {
            t[p].minn = w[anti[l]];
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void change(int p, int pos, int val)
    {
        if(t[p].l == t[p].r)
        {
            t[p].minn = val;
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) change(p << 1, pos, val);
        else change(p << 1 | 1, pos, val);
        pushup(p);
    }

    inline int query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].minn;
        int mid = t[p].l + t[p].r >> 1;
        int ans = 0x3f3f3f3f;
        if(l <= mid) ans = min(ans, query(p << 1, l, r));
        if(r > mid) ans = min(ans, query(p << 1 | 1, l, r));
        return ans;
    }

    inline int qchain(int x, int y)
    {
        int ans = 0x3f3f3f3f;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) swap(x, y);
            ans = min(ans, query(1, dfn[top[x]], dfn[x]));
            x = fa[top[x]];
        }
        if(dep[x] < dep[y]) swap(x, y);
        ans = min(ans, query(1, dfn[y], dfn[x]));
        return ans;
    }
}
using namespace tc;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    memset(w, 0x3f, sizeof w);

    n = read(), m = read(), q = read();
    tj::cnt = n;
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i <= m; i ++ ) 
    {
        int a = read(), b = read();
        add(h, a, b), add(h, b, a);
    }

    tj::tarjan(1);
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, tj::cnt);

    while(q -- )
    {
        char op[2];
        scanf("%s", op);
        if(op[0] == 'C')
        {
            int x = read(), y = read();
            if(fa[x] > n)
            {
                sqval[fa[x]].erase(sqval[fa[x]].lower_bound(w[x]));
                sqval[fa[x]].insert(y);
                w[fa[x]] = *sqval[fa[x]].begin();
                change(1, dfn[fa[x]], w[fa[x]]);
            }
            change(1, dfn[x], y);
            w[x] = y;
        }
        else
        {
            int x = read(), y = read();
            int anc = lca(x, y);
            int res = qchain(x, y);
            if(anc > n) 
            {
                res = min(res, w[fa[anc]]);
            }
            printf("%d\n", res);
        }
    }

    

    return 0;
}