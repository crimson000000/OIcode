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

const int N = 3e6 + 10, M = 3e6 + 10;
int h[M], e[N], ne[N], idx;
int hs[M];
int n, m, q;
int cnt;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace tj
{
    int dfn[M], low[M], tim;
    int stk[M], tt;

    void init()
    {
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        tim = tt = 0;
    }

    // void tarjan(int u)
    // {
    //     dfn[u] = low[u] = ++ tim;
    //     stk[++ tt] = u;
    //     for(int i = h[u]; i != -1; i = ne[i])
    //     {
    //         int v = e[i];
    //         if(!dfn[v])
    //         {
    //             tarjan(v);
    //             low[u] = min(low[u], low[v]);
    //             if(low[v] >= dfn[u])
    //             {
    //                 cnt ++;
    //                 int y;
    //                 do {
    //                     y = stk[tt -- ];
    //                     add(hs, y, cnt), add(hs, cnt, y);
    //                 } while(y != v);
    //                 add(hs, cnt, u), add(hs, u, cnt);
    //             }
    //         }
    //         else low[u] = min(low[u], dfn[v]);
    //     }
    // }

    void tarjan(int u)
    {
        dfn[u] = low[u] = ++ tim;
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

namespace sp
{
    int fa[M], dep[M], son[M], siz[M];
    int val[M];
    void dfs1(int u, int f)
    {
        fa[u] = f, dep[u] = dep[f] + 1;
        siz[u] = 1;
        val[u] = val[f] + (u <= n);
        int maxsiz = -1;
        for(int i = hs[u]; i != -1; i = ne[i])
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
}

using namespace sp;

int S[M];
inline bool cmp(int a, int b)
{
    return dfn[a] < dfn[b];
}

inline void solve(int p)
{
    sort(S + 1, S + p + 1, cmp);
    S[p + 1] = S[1];
    int res = 0;
    for(int i = 1; i <= p; i ++ ) 
    {
        int anc = lca(S[i], S[i + 1]);
        res += val[S[i]] + val[S[i + 1]] - 2 * val[anc];
    }
    res >>= 1;
    if(lca(S[1], S[p]) <= n) res ++;
    res -= p;
    printf("%d\n", res);
}

inline void init()
{
    tj::init();
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    memset(fa, 0, sizeof fa);
    memset(dep, 0, sizeof dep);
    memset(son, 0, sizeof son);
    memset(siz, 0, sizeof siz);
    memset(top, 0, sizeof top);
    memset(dfn, 0, sizeof dfn);
    memset(anti, 0, sizeof anti);
    memset(val, 0, sizeof val);
    tim = idx = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        init();

        n = read(), m = read();
        cnt = n;
        for(int i = 1; i <= m; i ++ ) 
        {
            int a = read(), b = read();
            add(h, a, b), add(h, b, a);
        }

        tj::tarjan(1);
        dfs1(1, 0);
        dfs2(1, 1);

        q = read();
        while(q -- )
        {
            int p = read();
            for(int i = 1; i <= p; i ++ ) S[i] = read();
            solve(p);
        }
    }

    return 0;
}