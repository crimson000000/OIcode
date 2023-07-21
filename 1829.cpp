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

#define int ll
const int N = 1e7 + 10, mod = 20101009;
int primes[N], cnt;
bitset<N> st;
ll sum1[N], sum2[N];
int miu[N];
ll ans;
int n, m;

inline void init(int n)
{
    miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            miu[i] = -1;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = i * primes[j];
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                break;
            }
            miu[t] = -miu[i];
        }
    }

    for(int i = 1; i <= n; i ++ ) 
    {
        sum2[i] = (sum2[i - 1] + (miu[i] + mod) % mod * i % mod * i % mod + mod) % mod;
    }
}

inline ll getr(int n, int l)
{
    return n / (n / l);
}

inline ll g(ll n, ll m)
{
    return 1ll * (n * (n + 1) / 2) % mod * (m * (m + 1) / 2 % mod) % mod;
}

inline ll s(int n, int m)
{
    ll res = 0;
    for(int l = 1, r; l <= min(n, m); l ++ )
    {
        r = min(getr(n, l), getr(m, l));
        res = (res + (ll)(sum2[r] - sum2[l - 1] + mod) % mod * g(n / l, m / l) % mod) % mod;
        l = r;
    }
    return (res % mod + mod) % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(N - 5);

    for(int l = 1, r; l <= min(n, m); l ++ )
    {
        r = min(getr(n, l), getr(m, l));
        ans = (ans + (ll)(r - l + 1) * (l + r) / 2 % mod * s(n / l, m / l) % mod) % mod;
        l = r;
    }

    cout << (ans % mod + mod) % mod << endl;

    return 0;
}
