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

const int N = 1e5 + 10, K = 160, mod = 10007;
ll f[N][K];
ll S[K][K], fact[K];
ll n, k;
int h[N], e[N], ne[N], idx;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void init(int n)
{
    S[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % mod) % mod;
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
}

int siz[N];
void dfs_siz(int u, int fa)
{
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs_siz(v, u);
        siz[u] += siz[v];
    }
}

void dfs1(int u, int fa)
{
    f[u][0] = siz[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        for(int j = 1; j <= k; j ++ )
            f[u][j] = (f[u][j] + f[v][j] + f[v][j - 1]) % mod;
    }
}

ll now[K];
void dfs2(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        memset(now, 0, sizeof now);
        now[0] = f[u][0] - f[v][0];
        for(int j = 1; j <= k; j ++ )
            now[j] = (f[u][j] - f[v][j] - f[v][j - 1] + mod) % mod;
        f[v][0] += now[0];
        for(int j = 1; j <= k; j ++ ) 
        {
            f[v][j] = (f[v][j] + now[j] + now[j - 1]) % mod;
            f[v][j] = (f[v][j] % mod + mod) % mod;
        }

        dfs2(v, u);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), k = read();
    init(k);

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs_siz(1, 1);
    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ )
    {
        ll res = 0;
        for(int j = 0; j <= k; j ++ )
            res = (res + S[k][j] * fact[j] % mod * f[i][j] % mod) % mod;
        cout << res << endl;
    }

    return 0;
}