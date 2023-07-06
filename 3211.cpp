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

const int N = 1010, M = 1e5 + 10;
int h[N], e[M], ne[M], w[M], idx;
int deg[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

double a[N][N], b[N], f[N], ans;

bool gauss()
{
    for(int i = 1; i <= n; i ++ )
    {
        int pos = i;
        for(int j = i; j <= n; j ++ )
            if(fabs(a[pos][i]) < fabs(a[j][i]))
                pos = j;
        for(int j = 1; j <= n; j ++ )
            swap(a[pos][j], a[i][j]);
        swap(b[pos], b[i]);

        if(fabs(a[i][i]) < 1e-6) return false;
        
        for(int j = 1; j <= n; j ++ )
            if(j != i)
            {
                double temp = a[j][i] / a[i][i];
                for(int k = 1; k <= n; k ++ )
                    a[j][k] -= temp * a[i][k];
                b[j] -= temp * b[i];
            }
    }

    for(int i = 1; i <= n; i ++ )
        f[i] = b[i] / a[i][i];
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), deg[a] ++;
        if(a != b)
        {
            add(b, a, c);
            deg[b] ++;
        }
    }

    for(int i = 30; i >= 0; i -- )
    {
        for(int j = 1; j <= n; j ++ )
        {
            for(int k = 1; k <= n; k ++ )
                a[j][k] = 0;
            b[j] = 0;
            f[j] = 0;
        }
        for(int u = 1; u < n; u ++ )
        {
            a[u][u] = deg[u];
            for(int j = h[u]; j != -1; j = ne[j])
            {
                int v = e[j], val = w[j];
                if(!(val >> i & 1)) a[u][v] += -1;
                else a[u][v] += 1, b[u] += 1;
            }
        }
        a[n][n] = 1;
        // puts("");
        // for(int j = 1; j <= n; j ++ )
        // {
        //     for(int k = 1; k <= n; k ++ )
        //         cout << a[j][k] << ' ';
        //     cout << b[j] << endl;
        // }

        if(!gauss()) continue;
        
        ans += pow(2, i) * f[1];
    }

    printf("%.3lf\n", ans);
    
    return 0;
}
