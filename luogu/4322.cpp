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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, M = 2510;
int h[N], e[N], ne[N], idx;
int a[N], b[N];
double c[N];
double f[M][M];
int siz[N];
int n, k;
int rt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void dfs(int u, int fa)
{
    siz[u] = 1;
    f[u][1] = c[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        for(int j = min(siz[u], k); j > 0; j -- )
            for(int t = 0; t < min(j, siz[v] + 1); t ++ )
                f[u][j] = max(f[u][j], f[u][j - t] + f[v][t]);
    }
}

inline bool check(double mid)
{
    for(int i = 0; i <= n; i ++ )
    {
        siz[i] = 0;
        c[i] = a[i] - mid * b[i];
        for(int j = 0; j <= n; j ++ ) f[i][j] = -1e20;
    }
    c[0] = 0;

    dfs(0, 0);

    return f[0][k] >= 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    k = read() + 1 , n = read();
    for(int i = 1; i <= n; i ++ )
    {
        b[i] = read(), a[i] = read();
        int fa = read();
        add(i, fa), add(fa, i);
    }
    
    double l = 0, r = 10000;
    while(r - l > 1e-6)
    {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    printf("%.3lf\n", l);

    return 0;
}