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

const int N = 1e6 + 10, M = 2 * N;
int h[N], e[2 * M], ne[2 * M], idx;
int hs[N];
int dfn[N], low[N], tim;
int stk[N], tt;
int cnt;
int n, m, root;

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

int fa[2 * N], siz[2 * N], son[2 * N], dep[2 * N];
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

int top[2 * N];
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
    else return y;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read();
    while(m -- )
    {
        int a = read(), b = read();
        add(h, a, b), add(h, b, a);
    }

    cnt = n;

    for(root = 1; root <= n; root ++ )
        if(!dfn[root])
            tarjan(root);

    dfs1(1, 1);
    dfs2(1, 1);

    // for(int i = 1; i <= cnt; i ++ ) cout << fa[i] << ' ';
    // puts("");

    int q = read();
    while(q -- )
    {
        int x = read(), y = read();
        // cout << lca(x, y) << endl;
        // cout << dep[x] << ' ' << dep[y] << endl;
        cout << (dep[x] + dep[y] - 2 * dep[lca(x, y)]) / 2 + 1 << endl;
    }

    return 0;
}
