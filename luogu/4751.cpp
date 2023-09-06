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

inline void write(int x)
{
    if(x < 0) 
    {
        putchar('-');
        x = -x;
    }
    if(x > 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N << 1], ne[N << 1], idx;
int val[N];
int f[N][2], g[N][2];
int lastans;
int n, m;
int rt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct matrix
{
    int a[2][2];
    matrix() 
    {
        memset(a, 0, sizeof a);
    }

    matrix(int xx, int xy, int yx, int yy)
    {
        a[0][0] = xx, a[0][1] = xy;
        a[1][0] = yx, a[1][1] = yy;
    }

    inline int * operator [] (int x)
    {
        return a[x];
    }

    inline matrix operator * (const matrix M) const
    {
        matrix tmp;
        for(int k = 0; k < 2; k ++ )
            for(int i = 0; i < 2; i ++ )
                for(int j = 0; j < 2; j ++ )
                    tmp.a[i][j] = max(tmp.a[i][j], a[i][k] + M.a[k][j]);
        return tmp;
    }
};

int fa[N], siz[N], dep[N], son[N];
inline void dfs1(int u, int fat)
{
    fa[u] = fat, dep[u] = dep[fat] + 1;
    siz[u] = 1;
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
    }
}

struct node
{
    int l, r;
    matrix sum, v;    
}t[N];

inline void pushup(int p)
{
    t[p].sum = t[t[p].l].sum * t[p].v * t[t[p].r].sum;
}

inline bool is_root(int p)
{
    return !(t[fa[p]].l == p || t[fa[p]].r == p);
}

int qz[N], q[N];
inline int build(int l, int r)
{
    if(l > r) return 0;
    int sm = qz[r] - qz[l - 1];
    sm = (sm + 1) >> 1;
    int L = l, R = r, nrt;
    while(L <= R)
    {
        int mid = L + R >> 1;
        if(qz[mid] - qz[l - 1] >= sm)
        {
            nrt = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    t[q[nrt]].l = build(l, nrt - 1);
    t[q[nrt]].r = build(nrt + 1, r);
    fa[t[q[nrt]].l] = q[nrt];
    fa[t[q[nrt]].r] = q[nrt];
    pushup(q[nrt]);
    return q[nrt];
}

inline void dfs2(int u)
{
    g[u][0] = 0;
    g[u][1] = val[u];
    if(!son[u])
    {
        t[u].v = matrix(0, -INF, val[u], -INF);
        f[u][0] = g[u][0], f[u][1] = g[u][1];
        if(son[fa[u]] != u)
        {
            int rtfa = fa[u];
            q[0] = qz[0] = 0;
            for(int v = u; v; v = son[v])
            {
                q[0] ++;
                q[q[0]] = v;
                qz[q[0]] = qz[q[0] - 1] + siz[v] - siz[son[v]];
            }
            rt = build(1, q[0]);
            fa[rt] = rtfa;
        } 
        return;
    }
    dfs2(son[u]);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v);
        g[u][0] += max(f[v][0], f[v][1]);
        g[u][1] += f[v][0];
    }
    f[u][0] = g[u][0] + max(f[son[u]][0], f[son[u]][1]);
    f[u][1] = g[u][1] + f[son[u]][0];
    t[u].v = matrix(g[u][0], g[u][0], g[u][1], -INF);
    if(son[fa[u]] != u)
    {
        int rtfa = fa[u];
        q[0] = qz[0] = 0;
        for(int v = u; v; v = son[v])
        {
            q[0] ++;
            q[q[0]] = v;
            qz[q[0]] = qz[q[0] - 1] + siz[v] - siz[son[v]];
        }
        rt = build(1, q[0]);
        fa[rt] = rtfa;
    } 
}

inline void modify(int x, int v)
{
    g[x][1] += v - val[x];
    val[x] = v;
    t[x].v = matrix(g[x][0], g[x][0], g[x][1], -INF);
    for(int u = x; u; u = fa[u])
    {
        if(is_root(u) && fa[u])
        {
            int v = fa[u];
            g[v][0] -= max(t[u].sum[0][0], t[u].sum[1][0]);
            g[v][1] -= t[u].sum[0][0];
            pushup(u);
            g[v][0] += max(t[u].sum[0][0], t[u].sum[1][0]);
            g[v][1] += t[u].sum[0][0];
            t[v].v = matrix(g[v][0], g[v][0], g[v][1], -INF);
        }
        else pushup(u);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) val[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    t[0].v = t[0].sum = matrix(0, -INF, -INF, 0);
    dfs2(1);

    while(m -- )
    {
        int x = read() ^ lastans, y = read();
        modify(x, y);
        lastans = max(t[rt].sum[0][0], t[rt].sum[1][0]);
        printf("%d\n", lastans);
    }

    return 0;
}
