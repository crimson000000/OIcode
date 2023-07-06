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

const int N = 6010;
int h[N], e[N], ne[N], w[N], idx;
int v[N];
int f[N][N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dp(int u, int fa)
{
    if(u > n - m) 
    {
        f[u][1] = v[u];
        return 1;
    }
    int sum = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;

        int tmp = dp(v, u);
        sum += tmp;

        for(int j = sum; j >= 1; j -- )
            for(int k = 1; k <= tmp; k ++ )
                if(j - k >= 0) f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] - w[i]);
    }
    return sum;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(f, -0x3f, sizeof f);

    n = read(), m = read();
    
    for(int i = 1; i <= n - m; i ++ )
    {
        int cnt = read();
        while(cnt -- )
        {
            int a = read(), b = read();
            add(i, a, b), add(a, i, b);
        }
    }

    for(int i = n - m + 1; i <= n; i ++ )
    {
        v[i] = read();
    }

    for(int i = 1; i <= n; i ++ ) f[i][0] = 0;

    dp(1, 0);

    int res = 0;
    for(int i = 1; i <= m; i ++ )
        if(f[1][i] >= 0)
            res = i;

    cout << res << endl;

    return 0;
}
