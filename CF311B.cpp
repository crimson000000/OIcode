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

const int N = 110, M = 1e5 + 10;
ll f[N][M];
ll a[M], s[M];
ll d[M], sd[M];
int q[M], hh, tt = -1;
int n, m, p;

struct point
{
    ll x, y;
}po[N];

inline double slope(int a, int b)
{
    return (po[a].y - po[b].y) / (po[a].x - po[b].x);
}

inline ll Y(int i, int x)
{
    return f[i - 1][x] + s[x];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), p = read();
    for(int i = 2; i <= n; i ++ )
    {
        d[i] = read();
        sd[i] = sd[i - 1] + d[i];
    }

    for(int i = 1; i <= m; i ++ )
    {
        int h = read(), t = read();
        a[i] = t - sd[h];
    }

    sort(a + 1, a + m + 1);

    for(int i = 1; i <= m; i ++ ) s[i] = s[i - 1] + a[i];

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for(int i = 1; i <= p; i ++ )
    {
        hh = 0, tt = -1;
        q[++ tt] = 0;
        // f[i][0] = 0x3f3f3f3f;
        for(int j = 1; j <= m; j ++ )
        {
            while(hh < tt && Y(i, q[hh + 1]) - Y(i, q[hh]) < a[j] * (q[hh + 1] - q[hh]))
                hh ++;
            // while(hh < tt && slope(q[hh], q[hh + 1]) < a[j]) hh ++;
            f[i][j] = f[i - 1][q[hh]] - q[hh] * a[j] + s[q[hh]] - s[j] + j * a[j];
            while(hh < tt && (Y(i, j) - Y(i, q[tt])) * (q[tt] - q[tt - 1]) 
                            < (Y(i, q[tt]) - Y(i, q[tt - 1])) * (j - q[tt]))
                tt --;
            // po[j] = {j, Y(i, j)};
            // while(hh < tt && slope(q[tt], q[tt - 1]) > slope(j, q[tt]))
                
            q[++ tt] = j; 
        }
    }

    // memset(f, 0x3f, sizeof f);
    // f[0][0] = 0;
    // for(int i = 1; i <= p; i ++ )
    //     for(int j = 0; j <= m; j ++ )
    //         for(int k = 0; k < j; k ++ )
    //             f[i][j] = min(f[i][j], f[i - 1][k] + (j - k) * a[j] - s[j] + s[k]);
    // for(int i = 0; i <= p; i ++ ) cout << f[i][0] << endl;

    cout << f[p][m] << endl;

    return 0;
}