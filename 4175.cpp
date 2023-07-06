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
int h[N], e[N], ne[N], idx;
int v[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dep[N], fa[N], siz[N], son[N];
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
            son[u] = j;
            maxsize = siz[j];
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

    inline int ask(int l, int r)
    {
        return query(r) - query(l - 1);
    }

    inline int qtree(int x, int y)
    {
        int res = 0;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) 
                swap(x, y);
            res += ask(dfn[top[x]], dfn[x]);
            x = fa[top[x]];
        }
        if(dep[x] < dep[y]) swap(x, y);
        res += ask(dfn[y], dfn[x]);
        return res;
    }
} bit;

struct Q
{
    int op, x, y, k;
}q[N], lq[N], rq[N];
int tt, ans[N], ques;

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
    int mid = lval + rval >> 1;
    int lt = 0, rt = 0;
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op <= 0)
        {
            if(q[i].y > mid) bit.add(dfn[q[i].x], q[i].k), rq[++ rt] = q[i];
            else lq[++ lt] = q[i];
        }
        else
        {
            int cnt = bit.qtree(q[i].x, q[i].y);
            if(q[i].k <= cnt) rq[++ rt] = q[i];
            else q[i].k -= cnt, lq[++ lt] = q[i];
        }
    }

    for(int i = st; i <= ed; i ++ )
        if(q[i].op <= 0 && q[i].y > mid)
            bit.add(dfn[q[i].x], -q[i].k);
        
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
    for(int i = 1; i <= n; i ++ )
    {
        int val = read();
        v[i] = val;
        q[++ tt] = {0, i, val, 1};
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= m; i ++ )
    {
        int k = read(), x = read(), y = read();
        if(k == 0)
        {
            q[++ tt] = {-1, x, v[x], -1};
            q[++ tt] = {0, x, y, 1};
            v[x] = y;
        }
        else
        {
            q[++ tt] = { ++ ques, x, y, k};
        }
    }

    solve(-INF, INF, 1, tt);
    for(int i = 1; i <= ques; i ++ )
        if(ans[i] >= INF / 2 || ans[i] <= -INF / 2) puts("invalid request!");
        else 
            printf("%d\n", ans[i]);
    
    return 0;
}
