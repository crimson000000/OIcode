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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;

int h[N], e[N], ne[N], idx;
int dist[N], dep[N], top[N], fa[N], son[N], siz[N], dfn[N], tim;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int father)
{
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
}

void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
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
    if(dep[x] > dep[y]) return y;
    else return x;
}

struct tree_array
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
} bit;

inline void tree(int x, int y, int val)
{
    int f = lca(x, y);
    bit.add(dfn[x], val);
    bit.add(dfn[y], val);
    bit.add(dfn[f], -val);
    if(fa[f] != f) bit.add(dfn[fa[f]], -val);
}

inline int sontree(int u)
{
    return bit.query(dfn[u] + siz[u] - 1) - bit.query(dfn[u] - 1);
}

struct Q
{
    int op, a, b, c;
}q[N], lq[N], rq[N];
int tt, ans[N], mx;

void solve(int lval, int rval, int st, int ed)
{
    if(st > ed) return;
    if(lval == rval)
    {
        for(int i = st; i <= ed; i ++ )
            if(q[i].op > 0)
                ans[q[i].op] = lval;
        return;
    }
    int mid = lval + rval >> 1, lt = 0, rt = 0;
    int cnt = 0;
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op <= 0)
        {
            if(q[i].c > mid)
            {
                int t;
                if(q[i].op == 0) t = 1;
                else t = -1;
                tree(q[i].a, q[i].b, t);
                cnt += t;
                rq[++ rt] = q[i];
            }
            else lq[++ lt] = q[i];
        }
        else
        {
            if(sontree(q[i].a) == cnt) lq[++ lt] = q[i];
            else rq[++ rt] = q[i];
        }
    }
    
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op <= 0)
            if(q[i].c > mid)
            {
                int t;
                if(q[i].op == 0) t = 1;
                else t = -1;
                tree(q[i].a, q[i].b, -t);
            }
    }

    for(int i = 1; i <= lt; i ++ ) q[st + i - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[st + lt + i - 1] = rq[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
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

    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= m; i ++ )
    {
        int op = read();
        if(op == 0)
        {
            int a = read(), b = read(), c = read();
            q[i] = {0, a, b, c};
            mx = max(mx, c);
        }
        else if(op == 1)
        {
            int a = read();
            q[i] = {-1, q[a].a, q[a].b, q[a].c};
        }
        else
        {
            int a = read();
            q[i] = {++ tt, a, 0, 0};
        }
    }

    solve(-1, mx, 1, m);
    for(int i = 1; i <= tt; i ++ )
        printf("%d\n", ans[i]);
    
    return 0;
}
