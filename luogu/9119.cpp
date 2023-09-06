#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
using ld = long double;

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

const int N = 2010;
ld f[N][N][2];
struct state
{
    int i, j, k;
}pre[N][N][2];
ld dist[N][N];
int n, m;

struct point
{
    ld x, y;
}q[N];

ld topy = -1e20;
int top;

inline ld getdis(int i, int j)
{
    return sqrt((q[i].x - q[j].x) * (q[i].x - q[j].x) + (q[i].y - q[j].y) * (q[i].y - q[j].y));
}

inline void dfs(int i, int j, int k)
{
    if(i == j)
    {
        printf("%d ", i);
        return;
    }
    auto x = pre[i][j][k];
    dfs(x.i, x.j, x.k);
    if(!k) printf("%d ", (i - 1) % n + 1);
    else printf("%d ", (j - 1) % n + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%Lf%Lf", &q[i].x, &q[i].y);
        q[i + n] = q[i];
        if(q[i].y > topy) top = i, topy = q[i].y;
    }

    m = n << 1;
    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= m; j ++ )
            dist[i][j] = getdis(i, j);

    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= m; j ++ )
            f[i][j][0] = f[i][j][1] = 1e20;
    
    f[top][top][0] = f[top][top][1] = 0;
    f[top + n][top + n][0] = f[top + n][top + n][1] = 0;
    
    for(int len = 2; len <= n; len ++ )
    {
        for(int l = 1; l <= m; l ++ )
        {
            int r = l + len - 1;
            if(r > m) break;
            
            // f[l][r][0] = min(f[l + 1][r][1] + dist[l][r], f[l + 1][r][0] + dist[l][l + 1]);
            if(f[l + 1][r][1] + dist[l][r] < f[l + 1][r][0] + dist[l][l + 1])
            {
                f[l][r][0] = f[l + 1][r][1] + dist[l][r];
                pre[l][r][0] = {l + 1, r, 1};
            }
            else
            {
                f[l][r][0] = f[l + 1][r][0] + dist[l][l + 1];
                pre[l][r][0] = {l + 1, r, 0};
            }
            // f[l][r][1] = min(f[l][r - 1][1] + dist[r - 1][r], f[l][r - 1][0] + dist[l][r]);
            if(f[l][r - 1][1] + dist[r - 1][r] < f[l][r - 1][0] + dist[l][r])
            {
                f[l][r][1] = f[l][r - 1][1] + dist[r - 1][r];
                pre[l][r][1] = {l, r - 1, 1};
            }
            else
            {
                f[l][r][1] = f[l][r - 1][0] + dist[l][r];
                pre[l][r][1] = {l, r - 1, 0};
            }
        }
    }

    ld ans = 1e20;
    state cur;
    for(int i = 1; i <= n; i ++ )
    {
        if(ans > f[i][i + n - 1][0]) ans = f[i][i + n - 1][0], cur = {i, i + n - 1, 0};
        if(ans > f[i][i + n - 1][1]) ans = f[i][i + n - 1][1], cur = {i, i + n - 1, 1};
    }

    dfs(cur.i, cur.j, cur.k);

    return 0;
}