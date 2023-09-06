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
int h[N], e[N], ne[N], idx;
int w[N], p[N];
int mp[N], tot;
int n, m, c, q;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N >> 1][22], f1[N >> 1][22], f2[N >> 1][22];
int dep[N];
int buck[N];
void dfs(int u, int father)
{
    fa[u][0] = father;
    dep[u] = dep[father] + 1;
    
    int reco = buck[w[u]];
    buck[w[u]] = u;
    f1[u][0] = buck[w[u] + 1];
    f2[u][0] = buck[w[u] - 1];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == father) continue;
        dfs(v, u);
    }
    buck[w[u]] = reco;
}

inline int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 20; i >= 0; i -- )
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];

    if(x == y) return x;
    for(int i = 20; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    return fa[x][0];
}

struct seg
{
    int l, r;
    int val;
}t[N * 50];
int root[N], cnt;

inline void change(int &p, int q, int l, int r, int pos, int val)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r) 
    {
        t[p].val = val;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) change(t[p].l, t[q].l, l, mid, pos, val);
    else change(t[p].r, t[q].r, mid + 1, r, pos, val);
}

inline int query(int p, int l, int r, int pos)
{
    if(!p) return 0;
    if(l == r) return t[p].val;
    int mid = l + r >> 1;
    if(pos <= mid) return query(t[p].l, l, mid, pos);
    else return query(t[p].r, mid + 1, r, pos);
}

void dfs2(int u)
{
    change(root[u], root[fa[u][0]], 1, n, w[u], u);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u][0]) continue;
        dfs2(v);
    }
}

void pre()
{
    dfs(1, 1);
    for(int j = 1; j <= 20; j ++ )
        for(int i = 1; i <= n; i ++ )
        {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            f1[i][j] = f1[f1[i][j - 1]][j - 1];
            f2[i][j] = f2[f2[i][j - 1]][j - 1];
        }
    dfs2(1);
}

inline int jump1(int u, int d)
{
    if(dep[u] < d) return 0;
    for(int i = 20; i >= 0; i -- )
        if(dep[f1[u][i]] >= d)
            u = f1[u][i];
    return w[u];
}

inline int jump2(int u, int d)
{
    for(int i = 20; i >= 0; i -- )
        if(dep[f2[u][i]] >= d)
            u = f2[u][i];
    return w[u];
}

inline bool check(int v, int x, int d, int se)
{
    int u = query(root[v], 1, n, x);
    if(dep[u] < d) return false;
    int st = jump2(u, d);
    return st <= (se + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read(), c = read();
    tot = c;

    for(int i = 1; i <= c; i ++ ) 
    {
        p[i] = read(); 
        mp[p[i]] = i;
    }

    for(int i = 1; i <= m; i ++ ) 
        if(!mp[i])
            mp[i] = ++ tot;

    for(int i = 1; i <= n; i ++ )
    {
        w[i] = read();
        w[i] = mp[w[i]];
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    pre();

    q = read();
    while(q -- )
    {
        int x = read(), y = read();
        int anc = lca(x, y);
        int fir = query(root[x], 1, n, 1);
        int se = min(jump1(fir, dep[anc]), c);
        int l = se + 1, r = c, ans = se;
        while(l <= r)
        {
            int mid = l + r >> 1;
            if(check(y, mid, dep[anc], se)) l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}
