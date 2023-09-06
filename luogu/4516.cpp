#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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

const int N = 1e5 + 10, M = 2 * N, mod = 1e9 + 7, NN = 110;
int h[N], e[M], ne[M], idx;
int f[N][NN][2][2], tmp[NN][2][2]; //第一个01是是否放, 第二个是是否被
int siz[N];
int n, k;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa)
{
    siz[u] = f[u][0][0][0] = f[u][1][1][0] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;

        dfs(v, u);

        memcpy(tmp, f[u], sizeof tmp);
        memset(f[u], 0, sizeof f[u]);

        for(int j = 0; j <= min(k, siz[u]); j ++ )
        {
            int lim = min(siz[v], k - j);
            for(int l = 0; l <= lim; l ++ )
            {
                f[u][j + l][0][0] = (f[u][j + l][0][0] + (ull)tmp[j][0][0] * f[v][l][0][1] % mod) % mod;
                f[u][j + l][0][1] = (f[u][j + l][0][1] + (ull)tmp[j][0][1] * (f[v][l][0][1] + f[v][l][1][1]) % mod) % mod;
                f[u][j + l][0][1] = (f[u][j + l][0][1] + (ull)tmp[j][0][0] * f[v][l][1][1] % mod) % mod;
                f[u][j + l][1][0] = (f[u][j + l][1][0] + (ull)tmp[j][1][0] * (f[v][l][0][0] + f[v][l][0][1]) % mod) % mod;
                f[u][j + l][1][1] = (f[u][j + l][1][1] + (ull)tmp[j][1][0] * (f[v][l][1][0] + f[v][l][1][1]) % mod) % mod;
                f[u][j + l][1][1] = (f[u][j + l][1][1] + (ull)tmp[j][1][1] * ((ull)(f[v][l][0][0] + f[v][l][0][1]) % mod + (ull)(f[v][l][1][0] + f[v][l][1][1]) % mod) % mod) % mod;
            }
        }
        siz[u] += siz[v];
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

    dfs(1, 1);

    cout << (f[1][k][0][1] + f[1][k][1][1]) % mod << endl;
    
    return 0;
}
