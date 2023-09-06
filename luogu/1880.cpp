#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1010;
ll f[N][N], d[N][N];
ll g[N][N];
ll sum[N], a[N];
int n;

ll w(int l, int r)
{
    return sum[r] - sum[l - 1];
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
        a[i] = read();
        a[i + n] = a[i];
    }

    for(int i = 1; i <= 2 * n; i ++ ) sum[i] = sum[i - 1] + a[i];
    memset(f, 0x3f, sizeof f);

    for(int i = 1; i <= 2 * n; i ++ ) 
    {
        f[i][i] = 0;
        d[i][i] = i;
    }

    for(int len = 2; len <= n; len ++ )
    {
        for(int l = 1; l <= 2 * n; l ++ )
        {
            int r = l + len - 1;
            if(r > 2 * n) break;
            g[l][r] = max(g[l + 1][r], g[l][r - 1]) + w(l, r);
            int minid = -1;
            for(int k = d[l][r - 1]; k <= d[l + 1][r]; k ++ )
                if(f[l][r] > f[l][k] + f[k + 1][r] + w(l, r))
                {
                    f[l][r] = f[l][k] + f[k + 1][r] + w(l, r);
                    minid = k;
                }
            d[l][r] = minid;
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3f;
    ll res = 0;
    for(int i = 1; i <= n; i ++ ) 
    {
        ans = min(ans, f[i][i + n - 1]);
        res = max(res, g[i][i + n - 1]);
    }
    cout << ans << endl;
    cout << res << endl;

    return 0;
}