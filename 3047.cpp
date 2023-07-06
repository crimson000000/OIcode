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

const int N = 2e5 + 10, M = 25;
int h[N], e[N], ne[N], idx;
int dep[N];
int f[N][M];
int v[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void build(int u)
{
    f[u][0] = v[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(dep[j]) continue;
        dep[j] = dep[u] + 1;
        build(j);
        for(int k = 1; k <= m; k ++ )
            f[u][k] += f[j][k - 1];
    }
    return;
}

void dfs(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        if(dep[e[i]] > dep[u])
        {
            int j = e[i];
            for(int k = m; k >= 2; k -- )
                f[j][k] -= f[j][k - 2];
            
            for(int k = 1; k <= m; k ++ )   
                f[j][k] += f[u][k - 1];
            dfs(j);
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }
    
    for(int i = 1; i <= n; i ++ ) v[i] = read();

    dep[1] = 1;
    build(1);
    dfs(1);

    for(int i = 1; i <= n; i ++ )
    {
        int ans = 0;
        for(int j = 0; j <= m; j ++ ) ans += f[i][j];
        cout << ans << endl;
    }

    return 0;
}
