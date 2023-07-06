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

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
int n, q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], son[N], siz[N];
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, fa[u] = f;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
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
    for(int i = h[u]; i != -1; i = ne[i])
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
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) return y;
    else return x;
}

int dis(int a, int b)
{
    int c = lca(a, b);
    return abs(dep[c] - dep[a]) + abs(dep[c] - dep[b]);
}

bool solve(int a, int b, int c, int d)
{
    int x = lca(a, b), y = lca(c, d);    
    if(dis(a, y) + dis(b, y) == dis(a, b) || dis(c, x) + dis(d, x) == dis(c, d)) return false;
    else return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    //图论记得初始化啊啊啊啊啊啊
    memset(h, -1, sizeof h);
    n = read(), q = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    while(q -- )
    {
        int a = read(), b = read(), c = read(), d = read();
        if(solve(a, b, c, d)) puts("N");
        else puts("Y");
    }

    return 0;
}
