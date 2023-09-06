#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

using i128 = __int128;

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

const int N = 30000;
ll f[N], g[N];
i128 sum[N];
ll mod;

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

inline void init(int n)
{
    f[0] = f[1] = 1, g[1] = 1;
    f[2] = 2, g[2] = 1;
    for(int i = 1; i <= n; i ++ ) sum[i] ++;
    for(int i = 2; i <= n; i += 2) sum[i] += 2;
    for(int i = 3; i <= n; i ++ )
    {
        i128 tmp = 0;
        for(int j = 0; j < i; j ++ ) tmp += f[j] * sum[i - j];
        tmp %= mod;
        g[i] = tmp * qmi(i, mod - 2, mod) % mod;
        f[i] = g[i] * 2 % mod;
        for(int j = i; j <= n; j += i) sum[j] += tmp, sum[j] %= mod;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    mod = read();
    init(23333);
    
    while(T -- )
    {
        int n = read();
        printf("%lld\n", f[n]);
    }
    
    return 0;
}
