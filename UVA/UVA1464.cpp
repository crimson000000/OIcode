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
int hs[N];
int dfn[N], low[N], tim;
int stk[N], tt;
int cnt, n, m, q;

struct edge
{
    int a, b;
}edges[N];

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if(low[j] >= dfn[u])
            {
                int y;
                cnt ++;
                do {
                    y = stk[tt -- ];
                    add(hs, y, cnt), add(hs, cnt, y);
                } while(y != j);
                add(hs, u, cnt), add(hs, cnt, u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}

int fa[N], dep[N], son[N], siz[N];
void dfs1(int u, int father)
{
    fa[u] = father, dep[u] = dep[father] + 1;
    siz[u] = 1;
    int maxsize = -1;
    
    for(int i = hs[u]; i != -1; i = ne[i])
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

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) 
            swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

int getcut(int x, int y)
{
    return (dep[x] + dep[y] - 2 * dep[lca(x, y)]) / 2 - 1;
}

void init()
{
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(stk, 0, sizeof stk);
    memset(edges, 0, sizeof edges);
    memset(fa, 0, sizeof fa);
    memset(siz, 0, sizeof siz);
    memset(dep, 0, sizeof dep);
    memset(son, 0, sizeof son);
    memset(top, 0, sizeof top);
    tt = idx = tim = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(n = read(), m = read(), n && m)
    {
        init();
        for(int i = 1; i <= m; i ++ )
        {
            int a = read(), b = read();
            add(h, a, b), add(h, b, a);
            edges[i] = {a, b};
        }

        cnt = n;

        for(int i = 1; i <= n; i ++ )
            if(!dfn[i])
                tarjan(i);
        
        for(int i = 1; i <= n; i ++ )
            if(!dep[i])
                dfs1(i, i);
        
        for(int i = 1; i <= n; i ++ )
            if(!top[i])
                dfs2(i, i);
        
        q = read();
        while(q -- )
        {
            int x = read(), y = read();
            int a1 = edges[x].a, a2 = edges[x].b;
            int b1 = edges[y].a, b2 = edges[y].b;
            // printf("%d %d %d %d\n", a1, a2, b1, b2);
            int t = -1;
            t = max(t, getcut(a1, b1));
            t = max(t, getcut(a1, b2));
            t = max(t, getcut(a2, b1));
            t = max(t, getcut(a2, b2));
            cout << t << endl;
        }
    }
    
    return 0;
}
