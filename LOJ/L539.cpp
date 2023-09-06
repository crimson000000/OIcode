#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

using PII = pair<ll, ll>;

const int N = 1e6 + 10, M = 110;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int p[N], c[N];
ll f[M][M * M], W[M][M], g[21][M][M], tmp[N];
int C, n, m, T;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline void solve(int u)
{
    int sum = 0;
    for(int i = 20; i >= 0; i -- )
    {
        if(sum + (1 << i) > min(c[u], C)) continue;

        sum += (1 << i);
        for(int i = 1; i <= n; i ++ ) tmp[i] = -INF;
        for(int x = 1; x <= n; x ++ )
            for(int v = 1; v <= n; v ++ )
                tmp[v] = max(tmp[v], W[u][x] + g[i][x][v]);

        for(int j = 1; j <= n; j ++ )
            W[u][j] = max(W[u][j], tmp[j]);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), C = read(), T = read();

    for(int i = 1; i <= n; i ++ )
    {
        p[i] = read();
        c[i] = read();
    }

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }

    memset(g, -0x3f, sizeof g);
    for(int u = 1; u <= n; u ++ )
    {
        g[0][u][u] = 0;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            g[0][u][v] = max(g[0][u][v], (ll)w[i]);
        }
    }

    for(int i = 1; i <= 20; i ++ )
    {
        for(int u = 1; u <= n; u ++ )
            for(int v = 1; v <= n; v ++ )
                g[i][u][v] = g[i - 1][u][v];

        for(int u = 1; u <= n; u ++ )
            for(int v = 1; v <= n; v ++ )
                for(int x = 1; x <= n; x ++ )
                    g[i][u][v] = max(g[i][u][v], g[i - 1][u][x] + g[i - 1][x][v]);
    }

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            if(i == j) W[i][j] = 0;
            else W[i][j] = -INF;
        }
    }

    for(int i = 1; i <= n; i ++ )
        solve(i);

    // cout << getw(1, 4, 2) << endl;

    // memset(f, -0x3f, sizeof f);
    for(int q = 0; q <= n * n; q ++ )
        for(int u = 1; u <= n; u ++ )
        {
            if(p[u] > q) 
            {
                f[u][q] = 0;
                continue;
            }
            for(int v = 1; v <= n; v ++ )
            {
                f[u][q] = max(f[u][q], f[v][q - p[u]] + W[u][v]);
            }
        }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n * n; j ++ )
            f[i][j] = max(f[i][j], f[i][j - 1]);
    
    while(T -- )
    {
        int s = read(), P = read(), d = read();
        if(f[s][P] < d) 
        {
            puts("-1");
            continue;
        }
        int l = 0, r = P;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(f[s][mid] >= d) r = mid;
            else l = mid + 1;
        }

        printf("%d\n", P - l);
    }

    return 0;
} 