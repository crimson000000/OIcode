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
int v[N];
int f[N][N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfs(int u)
{
    int sum = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int son = e[i];

        int tmp = dfs(son);
        sum += tmp;

        for(int j = sum; j > 0; j -- )
            for(int k = 0; k < j; k ++ )
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
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

    n = read(), m = read() + 1;

    for(int i = 1; i <= n; i ++ )
    {
        int p = read();
        v[i] = read();
        add(p, i);
        f[i][1] = v[i];
    }

    dfs(0);

    cout << f[0][m] << endl;
    
    return 0;
}
