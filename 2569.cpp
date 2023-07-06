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

const int N = 2010;
int f[N][N];
int q[N], hh, tt;
int n, w, m;
int ap, bp, as, bs;

inline int g1(int i, int x)
{
    return f[i - w - 1][x] + x * ap;
}

inline int g2(int i, int x)
{
    return f[i - w - 1][x] + x * bp;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), w = read();
    memset(f, -0x3f, sizeof f);
    for(int i = 1; i <= n; i ++ )
    {
        ap = read(), bp = read(), as = read(), bs = read();
        for(int j = 0; j <= as; j ++ )
            f[i][j] = - j * ap;
        for(int j = 0; j <= m; j ++ )
            f[i][j] = max(f[i][j], f[i - 1][j]);
        
        if(i <= w) continue;
        hh = 0, tt = -1;
        for(int j = 0; j <= m; j ++ )
        {
            while(hh <= tt && q[hh] < j - as) hh ++;
            while(hh <= tt && g1(i, q[tt]) <= g1(i, j)) tt --;
            q[++ tt] = j;
            if(hh <= tt) f[i][j] = max(f[i][j], g1(i, q[hh]) - j * ap);
        }

        hh = 0, tt = -1;
        for(int j = m; j >= 0; j -- )
        {
            while(hh <= tt && q[hh] > j + bs) hh ++;
            while(hh <= tt && g2(i, q[tt]) <= g2(i, j)) tt --;
            q[++ tt] = j;
            if(hh <= tt) f[i][j] = max(f[i][j], g2(i, q[hh]) - j * bp);
        }
    }

    cout << f[n][0] << endl;

    return 0;
}