#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 4e4 + 10, B = 1000;
bitset<N> f[42][42];
int id[N], tot;
int h[N], e[N << 1], ne[N << 1], idx;
int n, m;
int lastans;
vector<int> nums;
int col[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], maxdep[N], siz[N], son[N];
void dfs1(int u, int fat)
{
    fa[u] = fat;
    dep[u] = dep[fat] + 1;
    siz[u] = 1;
    maxdep[u] = dep[u];
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fat) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
        if(maxdep[v] > maxdep[u]) maxdep[u] = maxdep[v];
    }
    if(maxdep[u] - dep[u] >= B) id[u] = ++ tot, maxdep[u] = dep[u];
}

int stk[N], tt;
int FA[N];
void dfs2(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u]) continue;
        if(id[v])
        {
            int id1 = id[stk[tt]], id2 = id[v];
            for(int x = v; x != stk[tt]; x = fa[x]) f[id1][id2].set(col[x]);
            for(int i = 1; i < tt; i ++ )
                f[id[stk[i]]][id2] = f[id[stk[i]]][id1] | f[id1][id2];
            FA[v] = stk[tt];
            stk[++ tt] = v;
        }
        dfs2(v);
        if(id[v]) tt --;
    }
}

int top[N];
void dfs3(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs3(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs3(v, v);
    }
}

int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

bitset<N> now;
int query(int u, int v)
{
    now.reset();
    int lc = lca(u, v);
    // cout << "yeah" << endl;
    while(u != lc && !id[u]) now.set(col[u]), u = fa[u];
    while(v != lc && !id[v]) now.set(col[v]), v = fa[v];
    if(u != lc)
    {
        int pre = u;
        while(dep[FA[pre]] >= dep[lc]) pre = FA[pre];
        if(pre != u) now |= f[id[pre]][id[u]];
        while(pre != lc) now.set(col[pre]), pre = fa[pre];
    }
    if(v != lc)
    {
        int pre = v;
        while(dep[FA[pre]] >= dep[lc]) pre = FA[pre];
        if(pre != v) now |= f[id[pre]][id[v]];
        while(pre != lc) now.set(col[pre]), pre = fa[pre];
    }
    now.set(col[lc]);
    return now.count();
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        col[i] = read();
        nums.push_back(col[i]);
    }

    for(int i = 1; i < n; i ++ ) 
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        col[i] = lower_bound(nums.begin(), nums.end(), col[i]) - nums.begin();

    dfs1(1, 0);
    if(!id[1]) id[1] = ++ tot;
    stk[++ tt] = 1;
    
    dfs2(1);
    dfs3(1, 1);

    while(m -- )
    {
        int u = read() ^ lastans, v = read();
        printf("%d\n", lastans = query(u, v));
    }

    return 0;
}