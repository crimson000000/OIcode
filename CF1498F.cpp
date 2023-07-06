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

const int N = 2e5 + 10, K = 25;
int h[N], e[N], ne[N], idx;
int w[N];
int dp[N][K][2];
int n, k;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int fa)
{
    dp[u][0][0] = w[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        for(int j = 0; j < k; j ++ )
            for(int s = 0; s < 2; s ++ )
            {
                int nj = j + 1, ns = s;
                if(nj >= k) nj -= k, ns ^= 1;
                dp[u][nj][ns] ^= dp[v][j][s];
            }
    }
}

int tmp[K][2];
void dfs2(int u, int fa)
{
    if(u != 1)
    {
        for(int i = 0; i < k; i ++ )
            for(int j = 0; j < 2; j ++ )
                tmp[i][j] = dp[fa][i][j];
        for(int i = 0; i < k; i ++ )
            for(int j = 0; j < 2; j ++ )
            {
                int ni = i + 1, nj = j;
                if(ni >= k) ni -= k, nj ^= 1;
                tmp[ni][nj] ^= dp[u][i][j];
            }
        for(int i = 0; i < k; i ++ )
            for(int j = 0; j < 2; j ++ )
            {
                int ni = i + 1, nj = j;
                if(ni >= k) ni -= k, nj ^= 1;
                dp[u][ni][nj] ^= tmp[i][j];
            }
    }
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    for(int i = 1; i <= n; i ++ ) w[i] = read();
    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ )
    {
        int val = 0;
        for(int j = 0; j < k; j ++ ) val ^= dp[i][j][1];
        if(val) printf("1 ");
        else printf("0 ");
    }

    return 0;
}