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

const int N = 2010, M = 2 * N;
int h[N], e[M], ne[M], w[M], idx;
ll f[N][N];
ll siz[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa)
{
    siz[u] = 1, f[u][0] = f[u][1] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];

        for(int j = min(m, (int)siz[u]); j >= 0; j -- )
        {
            if(f[u][j] != -1)
                f[u][j] += f[v][0] + siz[v] * (n - m - siz[v]) * w[i];
            
            for(int k = min(j, (int)siz[v]); k > 0; k -- )
            {
                if(f[u][j - k] == -1) continue;
                ll val = (k * (m - k) + (siz[v] - k) * (n - m - siz[v] + k)) * w[i];
                f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] + val);
            }
        }
    } 
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();
    if(m > n - m) m = n - m;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    memset(f, -1, sizeof f);
    dfs(1, -1);

    cout << f[1][m] << endl;
    
    return 0;
}
