#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
ll n, k, m;
ll x[N];
ll l, r;
ll f[2][N];
ll ans[N];

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), m = read();
    for(int i = 1; i <= n; i ++ ) x[i] = read();

    l = 1, r = k + 1;
    f[1][1] = k + 1;
    for(int i = 2; i <= n; i ++ )
    {
        while(r + 1 <= n && x[i] - x[l] > x[r + 1] - x[i]) l ++, r ++;
        if(x[i] - x[l] >= x[r] - x[i]) f[1][i] = l;
        else f[1][i] = r;
    }

    for(int i = 1; i <= n; i ++ ) ans[i] = i;
    while(m)
    {
        if(m & 1) 
        {
            for(int i = 1; i <= n; i ++ ) 
                ans[i] = f[1][ans[i]];
        }
        memcpy(f[0], f[1], sizeof f[1]);
        for(int i = 1; i <= n; i ++ ) f[1][i] = f[0][f[0][i]];
        m >>= 1;
    }

    for(int i = 1; i <= n; i ++ ) printf("%lld ", ans[i]);

    return 0;
}
