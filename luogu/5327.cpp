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

const int N = 1e6 + 10, M = 1e6 + 5;
int h[N], e[N], ne[N], idx;
vector<int> del[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

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

int top[N], dfn[N], anti[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
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
    if(!x || !y) return 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

namespace sgmt
{
    struct seg
    {
        int l, r;
        ll f, st, ed, c;
    }t[N << 3];
    int root[N], cnt;

    inline void pushup(int p)
    {
        t[p].f = t[t[p].l].f + t[t[p].r].f - dep[lca(t[t[p].l].ed, t[t[p].r].st)];
        t[p].st = t[t[p].l].st ? t[t[p].l].st : t[t[p].r].st;
        t[p].ed = t[t[p].r].ed ? t[t[p].r].ed : t[t[p].l].ed;
    }

    inline ll query(int p)
    {
        if(!p) return 0;
        return t[p].f - dep[lca(t[p].st, t[p].ed)];
    }

    void change(int &p, int l, int r, int pos, int val)
    {
        if(!p) p = ++ cnt;
        if(l == r)
        {
            t[p].c += val;
            if(t[p].c)
            {
                t[p].f = dep[pos];
                t[p].st = t[p].ed = pos;
            }
            else t[p].f = t[p].st = t[p].ed = 0;
            return;
        }
        int mid = l + r >> 1;
        if(dfn[pos] <= mid) change(t[p].l, l, mid, pos, val);
        else change(t[p].r, mid + 1, r, pos, val);
        pushup(p);
    }

    inline void merge(int &p, int q, int l, int r)
    {
        if(!p || !q) 
        {
            p |= q;
            return;
        }
        if(l == r)
        {
            t[p].c += t[q].c;
            t[p].f |= t[q].f;
            t[p].st |= t[q].st;
            t[p].ed |= t[q].ed;
            return;
        }
        int mid = l + r >> 1;
        merge(t[p].l, t[q].l, l, mid);
        merge(t[p].r, t[q].r, mid + 1, r);
        pushup(p);
    }
}

using namespace sgmt;
ll ans;

void solve(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u]) continue;
        solve(v);
    }
    for(auto v : del[u]) change(root[u], 1, M, v, -1);
    ans += query(root[u]);
    merge(root[fa[u]], root[u], 1, M);
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
        int a = read(), b = read();
        add(a, b), add(b, a);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);

    while(m -- )
    {
        int x = read(), y = read();
        int lc = lca(x, y);
        change(root[x], 1, M, x, 1);
        change(root[x], 1, M, y, 1);
        change(root[y], 1, M, x, 1);
        change(root[y], 1, M, y, 1);
        del[lc].emplace_back(x);
        del[lc].emplace_back(y);
        if(lc != 1)
        {
            del[fa[lc]].emplace_back(x);
            del[fa[lc]].emplace_back(y);
        }
    }

    solve(1);
    printf("%lld\n", ans >> 1);

    return 0;
}