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
int a[N];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N];
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
        if(maxsize < siz[j])
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

int top[N], dfn[N], tim;
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

int v[N];

void dfs(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u]) continue;

        dfs(j);
        v[u] += v[j];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    a[0] = 1;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 0);
    
    for(int i = 1; i <= n - 1; i ++ )
    {
        int x = a[i], y = a[i + 1];
        int anc = lca(x, y);
        v[x] ++, v[y] ++;
        v[anc] --, v[fa[anc]] --;
    }

    dfs(1);

    for(int i = 2; i <= n; i ++ ) v[a[i]] --;

    for(int i = 1; i <= n; i ++ ) cout << v[i] << endl;
    
    return 0;
}
