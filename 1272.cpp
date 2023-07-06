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

const int N = 1010;
int h[N], e[N], ne[N], idx;
int f[N][N], siz[N];
int n, p, res = 0x3f3f3f3f;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfs(int u, int fa)
{
    int sum = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        
        int tmp = dfs(v, u);
        sum += tmp;

        for(int j = sum; j >= 1; j -- )
            for(int k = 0; k < j; k ++ )
                f[u][j] = min(f[u][j], f[u][j - k] + f[v][k] - 1);
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
    n = read(), p = read();

    memset(f, 0x3f, sizeof f);

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        siz[a] ++;
    }

    for(int i = 1; i <= n; i ++ ) f[i][1] = siz[i];

    dfs(1, 1);

    res = f[1][p];
    for(int i = 1; i <= n; i ++ )
        res = min(res, f[i][p] + 1);

    cout << res << endl;
     
    return 0;
}
