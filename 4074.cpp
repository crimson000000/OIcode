#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int v[N], w[N], c[N];
int pos[N];
int n, m, Q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct query
{
    int op, l, r, time;
    bool operator < (const query& Q) const
    {
        if(pos[l] == pos[Q.l])
        {
            if(pos[r] == pos[Q.r])
                return time < Q.time;
            return pos[r] < pos[Q.r];
        }
        return pos[l] < pos[Q.l];
    }
}q[N];
int qtt;

int last[N];
struct change
{
    int x, last, to;
}ch[N];

int fa[N], dep[N], son[N], siz[N];
int f[N], g[N], idexx;
int id[N];
void dfs1(int u, int father)
{
    f[u] = ++ idexx;
    id[idexx] = u;
    fa[u] = father, dep[u] = dep[father] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
    g[u] = ++ idexx;
    id[idexx] = u;
}

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

int tim;

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

int L = 1, R = 0, T = 0;
bool vis[N];
ll num[N], ans[N];
ll cnt;
void add(int p)
{
    if(vis[p])
    {
        cnt -= (ll)v[c[p]] * w[num[c[p]]];
        num[c[p]] --;
    }
    else
    {
        num[c[p]] ++;
        cnt += (ll)v[c[p]] * w[num[c[p]]];
    }
    vis[p] ^= 1;
}

void modify(int x, int t)
{
    if(vis[x])
    {
        add(x);
        c[x] = t;
        add(x);
    }
    else c[x] = t;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), Q = read();
    for(int i = 1; i <= m; i ++ ) v[i] = read();
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    int _ = pow(idexx, 2.0 / 3.0);
    for(int i = 1; i <= idexx; i ++ ) pos[i] = (i - 1) / _;
    
    for(int i = 1; i <= n; i ++ )
    {
        c[i] = read();
        last[i] = c[i];
    }

    // for(int i = 1; i <= idexx; i ++ ) cout << id[i] << ' ';
    // puts("");
    // for(int i = 1; i <= n; i ++ )
    //     printf("%d: [%d %d]\n", i, f[i], g[i]);

    // cout << lca(2, 4) << endl;

    for(int i = 1; i <= Q; i ++ )
    {
        int op = read(), x = read(), y = read();
        if(op == 0)
        {
            tim ++;
            ch[tim] = {x, last[x], y};
            last[x] = y;
        }
        else
        {
            qtt ++;
            q[qtt].op = qtt;
            q[qtt].time = tim;
            if(f[x] > f[y]) swap(x, y);
            if(lca(x, y) == x) q[qtt].l = f[x];
            else q[qtt].l = g[x];
            q[qtt].r = f[y];
        }
    }

    sort(q + 1, q + qtt + 1);

    L = 1, R = 0, T = 0;
    for(int i = 1; i <= qtt; i ++ )
    {
        while(T < q[i].time)
        {
            T ++;
            modify(ch[T].x, ch[T].to);
        }
        while(T > q[i].time)
        {
            modify(ch[T].x, ch[T].last);
            T --;
        }
        while(R < q[i].r) add(id[++ R]);
        while(L > q[i].l) add(id[-- L]);
        while(R > q[i].r) add(id[R --]);
        while(L < q[i].l) add(id[L ++]);
        int x = id[L], y = id[R];
        int anc = lca(x, y);
        if(x != anc && y != anc)
        {
            add(anc);
            ans[q[i].op] = cnt;
            add(anc);
        }
        else ans[q[i].op] = cnt;
    }

    for(int i = 1; i <= qtt; i ++ ) 
        printf("%lld\n", ans[i]);

    return 0;
}
