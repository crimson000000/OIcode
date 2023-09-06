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

const int N = 1e6 + 10, mod = 10007, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
int w[N];
ll f[N][3], g[N][3];
ll sum, maxn;
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N];
inline void dfs(int u, int father)
{
    f[u][0] = g[u][0] = w[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == father) continue;
        dfs(v, u);
        sum = (sum + f[u][1] * w[v]) % mod;
        f[u][1] = (f[u][1] + f[v][0]) % mod;
        f[u][2] = (f[u][2] + f[v][1]) % mod;
        maxn = max(maxn, g[u][1] * w[v]);
        g[u][1] = max(g[u][1], g[v][0]);
        g[u][2] = max(g[u][2], g[v][1]);
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    for(int i = 1; i <= n; i ++ ) w[i] = read();

    dfs(1, 0);

    for(int i = 1; i <= n; i ++ )
    {
        maxn = max(maxn, w[i] * g[i][2]);
        sum = (sum + (ll)w[i] * f[i][2]) % mod;
    }

    printf("%lld %lld\n", maxn, (sum << 1) % mod);
    
    return 0;
}