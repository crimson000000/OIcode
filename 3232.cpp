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

const int N = 1e6 + 10, M = 1010;
const double zero = 1e-6;
int h[N], e[N], ne[N], idx;
int deg[N];
double f[N], a[M][M], b[M];
double ans;
int n, m;
struct edge
{
    int a, b;
    double cnt;
    bool operator < (const edge& E)
    {
        return cnt < E.cnt;
    }
}edges[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void gauss(int n)
{
    for(int i = 1; i <= n; i ++ )
    {
        int pos = i;
        for(int j = i; j <= n; j ++ )
            if(fabs(a[j][i]) > fabs(a[pos][i]))
                pos = j;
        
        for(int j = 1; j <= n; j ++ )
            swap(a[pos][j], a[i][j]);
        swap(b[pos], b[i]);
        
        for(int j = 1; j <= n; j ++ )
            if(j != i)
            {
                double tmp = a[j][i] / a[i][i];
                for(int k = 1; k <= n; k ++ )
                    a[j][k] -= tmp * a[i][k];
                b[j] -= tmp * b[i];
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
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        deg[a] ++, deg[b] ++;
        edges[i] = {a, b, 0};
    }

    b[1] = 1;
    for(int u = 1; u < n; u ++ )
    {
        a[u][u] = 1.0;
        for(int j = h[u]; j != -1; j = ne[j])
        {
            int v = e[j];
            if(v == n) continue;
            a[u][v] = -1.0 / deg[v];
        }
    }

    // for(int i = 1; i < n; i ++ )
    // {
    //     for(int j = 1; j < n; j ++ )
    //         cout << a[i][j] << ' ';
    //     printf("%lf\n", b[i]);
    // }

    gauss(n - 1);
    for(int i = 1; i < n; i ++ )
        f[i] = b[i] / a[i][i];

    // for(int i = 1; i <= n; i ++ ) 
    //     cout << f[i] << endl;

    for(int i = 1; i <= m; i ++ )
    {
        int a = edges[i].a, b = edges[i].b;
        if(a != n) edges[i].cnt += f[a] / deg[a];
        if(b != n) edges[i].cnt += f[b] / deg[b];
    }

    sort(edges + 1, edges + m + 1);

    for(int i = 1; i <= m; i ++ )
    {
        ans += edges[i].cnt * (m - i + 1);
    }

    printf("%.3lf\n", ans);
    
    return 0;
}
