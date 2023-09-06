#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int __int128
#define ll __int128

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

const int N = 1e6 + 10, M = 1e6;
const ll INF = 123456789123456789;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
int n, m;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N];
void dfs1(int u, int father)
{
    fa[u] = father, dep[u] = dep[father] + 1;
    siz[u] = 1;
    
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;
        dist[j] = dist[u] + w[i];
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsiz)
        {
            maxsiz = siz[j];
            son[u] = j;
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
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

struct seg
{
    ll k, b;
}a[N * 5];
int sid;

inline int New(ll k, ll b)
{
    sid ++;
    a[sid] = {k, b};
    return sid;
}

inline ll get(int id, ll x)
{
    return a[id].k * x + a[id].b;
}

struct segment
{
    int l, r;
    int minn;
    ll val;
    segment(): val(INF), l(0), r(0), minn(0) {}
}t[N << 2];
int root, cnt;

inline void pushup(int p, int l, int r)
{
    t[p].val = min(t[p].val, min(get(t[p].minn, dist[anti[l]]), get(t[p].minn, dist[anti[r]])));
    if(t[p].l) t[p].val = min(t[p].val, t[t[p].l].val);
    if(t[p].r) t[p].val = min(t[p].val, t[t[p].r].val);
}

inline void insert(int &p, int l, int r, int L, int R, int id)
{
    if(!p) p = ++ cnt;
    if(L <= l && r <= R)
    {
        if(!t[p].minn)
        {
            t[p].minn = id;
            pushup(p, l, r);
            return;
        }
        int mid = l + r >> 1;
        if(get(id, dist[anti[mid]]) < get(t[p].minn, dist[anti[mid]])) swap(t[p].minn, id);
        if(get(id, dist[anti[l]]) < get(t[p].minn, dist[anti[l]])) insert(t[p].l, l, mid, L, R, id);
        if(get(id, dist[anti[r]]) < get(t[p].minn, dist[anti[r]])) insert(t[p].r, mid + 1, r, L, R, id);
        pushup(p, l, r);
        return;
    }
    int mid = l + r >> 1;
    if(L <= mid) insert(t[p].l, l, mid, L, R, id);
    if(R > mid) insert(t[p].r, mid + 1, r, L, R, id);
    pushup(p, l, r);
    return;
}

inline ll query(int p, int l, int r, int L, int R)
{
    if(!p) return INF;
    if(L <= l && r <= R) return t[p].val;
    ll ans = INF;
    if(t[p].minn) ans = min(get(t[p].minn, dist[anti[max(l, L)]]), 
                            get(t[p].minn, dist[anti[min(r, R)]]));
    int mid = l + r >> 1;
    if(L <= mid) ans = min(ans, query(t[p].l, l, mid, L, R));
    if(R > mid) ans = min(ans, query(t[p].r, mid + 1, r, L, R));
    return ans;
}

inline void cchain(int x, int y, int id)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        insert(root, 0, M, dfn[top[x]], dfn[x], id);
        x = fa[top[x]];
    }
    if(dfn[x] < dfn[y]) swap(x, y);
    insert(root, 0, M, dfn[y], dfn[x], id);
}

inline ll qchain(int x, int y)
{
    ll ans = INF;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = min(ans, query(root, 0, M, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dfn[x] < dfn[y]) swap(x, y);
    ans = min(ans, query(root, 0, M, dfn[y], dfn[x]));
    return ans;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 2; i <= n; i ++ ) 
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    a[0] = {0, INF};

    for(int i = 1; i <= N - 10; i ++ ) t[i].val = INF;

    dfs1(1, 1);
    dfs2(1, 1);

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int s = read(), t = read(), a = read(), b = read();
            int anc = lca(s, t);
            int id = New(-a, a * dist[s] + b);
            cchain(s, anc, id);
            id = New(a, a * (dist[s] - 2 * dist[anc]) + b);
            cchain(anc, t, id);
        }
        else
        {
            int s = read(), t = read();
            printf("%lld\n", (long long)qchain(s, t));
        }
        // cout << "yeah" << endl;
    }

    return 0;
}