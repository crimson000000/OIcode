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

const int N = 25, S = 1 << 20, mod = 998244353;
ll sum[S], f[S][2], g[S];
ll a[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 0; i < (1 << n); i ++ )
    {
        for(int j = 0; j < n; j ++ )
            if(i >> j & 1)
                sum[i] = (sum[i] + a[j + 1]) % mod;
    }

    for(int i = 1; i <= n; i ++ )
        if(a[i] >= 0)
            f[1 << (i - 1)][1] = 1;
        else f[1 << (i - 1)][0] = 1;

    g[0] = 1;

    for(int i = 1; i < (1 << n); i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            if(i >> (j - 1) & 1) continue;
            int T = i | (1 << j - 1);
            if(sum[T] < 0) f[T][0] = (f[T][0] + f[i][1]) % mod;
            else f[T][1] = (f[T][1] + f[i][1]) % mod;
        }
    }

    for(int i = 0; i < (1 << n); i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            if(i >> (j - 1) & 1) continue;
            int T = i | (1 << j - 1);
            if(sum[T] < 0) g[T] = (g[T] + g[i]) % mod;
        }
    }

    int U = (1 << n) - 1;
    ll ans = 0;
    for(int i = 1; i <= U; i ++ )
    {
        ans = (ans + (f[i][0] + f[i][1]) * (sum[i] % mod + mod) % mod * g[U ^ i] % mod) % mod;
    }

    cout << ans << endl;

    return 0;
}