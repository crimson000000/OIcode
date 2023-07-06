#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
int f[N];
int h[N], e[N], ne[N], idx;
int g[N], fa[N];
char s[N];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u)
{
    g[u] = g[fa[u]];
    if(s[u] == '(') g[u] = u;
    else if(g[u]) f[u] = f[fa[g[u]]] + 1, g[u] = g[fa[g[u]]];
    
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u]) continue;
        dfs(j);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();
    scanf("%s", s + 1);

    for(int i = 2; i <= n; i ++ )
    {
        int ver = read();
        add(ver, i), add(i, ver);
        fa[i] = ver;
    }

    dfs(1);

    int res = 0;
    for(int i = 1; i <= n; i ++ )
    {
        // printf("%d %d %d\n", i, g[i], f[i]);
        f[i] += f[fa[i]];
        res ^= i * f[i];
    }

    cout << res << endl;
    
    return 0;
}
