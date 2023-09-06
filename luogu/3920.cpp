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
const double alpha = 0.8;
int h[N], e[N], ne[N], idx, cost[N];
int w[N];
int n;
ll lastans;
ll ans;

inline void add(int a, int b, int c)
{
    e[idx] = b, cost[idx] = c, ne[idx] = h[a], h[a] = idx ++; 
}

// -----------------fhq
namespace fhq
{
    struct node
    {
        int l, r;
        int val, siz, key;
    }t[N * 10];
    int stk[N * 10], tt;

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    }

    inline int New(int val)
    {
        int cnt = stk[tt -- ];
        t[cnt].val = val;
        t[cnt].siz = 1;
        t[cnt].key = rand();
        t[cnt].l = t[cnt].r = 0;
        return cnt;
    }

    inline int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key < t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            pushup(x);
            return x;
        }
        else
        {
            t[y].l = merge(x, t[y].l);
            pushup(y);
            return y;
        }
    }

    inline void split(int p, int val, int &x, int &y)
    {
        if(!p) x = y = 0;
        else
        {
            if(t[p].val <= val)
            {
                x = p;
                split(t[p].r, val, t[p].r, y);
            }
            else
            {
                y = p;
                split(t[p].l, val, x, t[p].l);
            }
            pushup(p);
        }
    }

    int x, y, z;
    inline void insert(int &root, int val)
    {
        split(root, val, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline int lowernum(int &root, int val)
    {
        split(root, val, x, y);
        int res = t[x].siz;
        root = merge(x, y);
        return res;
    }

    inline void clear(int root)
    {
        if(!root) return;
        clear(t[root].l);
        clear(t[root].r);
        stk[++ tt] = root;
    }
}

struct Set
{
    int root;
    inline void insert(int val) {fhq::insert(root, val);}
    inline int lowernum(int val) {return fhq::lowernum(root, val);}
    inline void clear() {fhq::clear(root), root = 0;}
    inline int size() {return fhq::t[root].siz; }
}t[N][2];

// -----------------lca

namespace lac
{
    int fa[N][20], dep[N], distt[N];

    inline void init(int x)
    {
        for(int i = 1; i <= 18; i ++ )
            fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }

    inline int lca(int x, int y)
    {
        if(dep[x] < dep[y]) swap(x, y);
        for(int i = 18; i >= 0; i -- )
            if(dep[fa[x][i]] >= dep[y])
                x = fa[x][i];
        
        if(x == y) return x;

        for(int i = 18; i >= 0; i -- )
            if(fa[x][i] != fa[y][i])
                x = fa[x][i], y = fa[y][i];
        return fa[x][0];
    }

    inline ll dist(int x, int y)
    {
        return distt[x] + distt[y] - (distt[lca(x, y)] << 1);
    }
}

using namespace lac;

//------------------dfz

int par[N];

inline bool fuck(int son, int fa)
{
    return t[fa][0].size() * alpha < t[son][0].size();
}

bitset<N> vis;
queue<int> tag;

namespace dianfenzhi
{
    vector<int> son[N];
    int siz[N], maxsiz[N], rt, tot;
        
    inline void calc_siz(int u, int fa)
    {
        siz[u] = 1;
        maxsiz[u] = 0;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == fa || vis[v]) continue;
            calc_siz(v, u);
            siz[u] += siz[v];
            maxsiz[u] = max(maxsiz[u], siz[v]);
        }
        maxsiz[u] = max(maxsiz[u], tot - siz[u]);
        if(maxsiz[u] < maxsiz[rt])
        {
            rt = u;
        }
    }

    inline void dfs(int u, int fa, int d, int to)
    {
        t[to][0].insert(d - w[u]);
        if(par[to]) t[to][1].insert(dist(par[to], u) - w[u]);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == fa || vis[v]) continue;
            dfs(v, u, d + cost[i], to);
        }
    }

    inline void dfz(int u)
    {
        int now = tot;
        vis[u] = true;
        dfs(u, 0, 0, u);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(vis[v]) continue;
            rt = 0, tot = siz[v];
            if(siz[v] > siz[u]) tot = now - siz[u];
            calc_siz(v, u);
            par[rt] = u;
            son[u].push_back(rt);
            dfz(rt); 
        }
    }

    inline void del(int x)
    {
        vis[x] = false;
        for(auto v : son[x])
            del(v);
        t[x][0].clear(), t[x][1].clear();
        son[x].clear();
    }

    inline void rebuild(int x)
    {
        tot = t[x][0].size();
        del(x);
        rt = 0;
        calc_siz(x, 0);

        for(int i = 0; i < son[par[x]].size(); i ++ )
            if(son[par[x]][i] == x)
                son[par[x]][i] = rt;
        
        par[rt] = par[x];
        dfz(rt);
    }

    int rebuildtime;
    inline void addin(int x)
    {
        for(int i = x; i; i = par[i])
        {
            if(par[i])
            {
                int d = dist(par[i], x);
                ans += t[par[i]][0].lowernum(w[x] - d) - t[i][1].lowernum(w[x] - d);
                t[i][1].insert(d - w[x]);
            }
            t[i][0].insert(dist(i, x) - w[x]);
        }

        int upp = 0;
        for(int i = x; par[i]; i = par[i])
            if(fuck(i, par[i]))
                upp = par[i];

        if(upp != 0) rebuild(upp);
    }
}

using namespace dianfenzhi;

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    int _ = read();

    for(int i = 1; i <= 1e7; i ++ ) fhq::stk[++ fhq::tt] = i;

    memset(h, -1, sizeof h);
    n = read();
    maxsiz[0] = INF; 
    
    for(int i = 1; i <= n; i ++ )
    {
        int a = read(), c = read(), r = read();
        a ^= lastans % 1000000000;

        // init father on dfs
        par[i] = a;

        // init father on OP tree
        lac::fa[i][0] = a;
        lac::init(i);
        if(i != 1) 
        {
            add(i, a, c);
            add(a, i, c);
        }

        // init val
        w[i] = r;

        // init dist
        lac::distt[i] = lac::distt[a] + c; 
        dep[i] = dep[a] + 1;

        son[a].push_back(i);
        vis[i] = true;

        addin(i);

        printf("%lld\n", lastans = ans);
        // cerr << ans << endl;
    }

    return 0;
}
