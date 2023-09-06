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
int primes[N], cnt;
bitset<N> st;
ll d[N], s[N];
ll miu[N];
int n, m;

inline void init(int n)
{
    d[1] = 1;
    miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            d[i] = 2;
            miu[i] = -1;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                d[t] = 2 * d[i] - d[i / primes[j]];
                miu[t] = 0;
                break;
            }
            d[t] = d[i] * d[primes[j]];
            miu[t] = -miu[i];
        }
    }
    for(int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + d[i];
    for(int i = 1; i <= n; i ++ ) miu[i] += miu[i - 1];
}

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll solve(ll n, ll m)
{
    ll ans = 0;
    for(int l = 1, r; l <= min(n, m); l = r + 1)
    {
        r = min(getr(n, l), getr(m, l));
        ans += (miu[r] - miu[l - 1]) * s[n / l] * s[m / l];
    }
    return ans;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(N - 5);

    while(T -- )
    {
        n = read(), m = read();
        printf("%lld\n", solve(n, m));
    }

    return 0;
}
