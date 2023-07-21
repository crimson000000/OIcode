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

const int N = 1e7 + 10;
int primes[N], cnt;
int miu[N];
int sum[N];
bitset<N> st;
ll n, m;

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
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                break;
            }
            miu[t] = -miu[i];
        }
    }

    for(int i = 1; i <= cnt; i ++ )
        for(int j = 1; j * primes[i] <= n; j ++ )
            sum[j * primes[i]] += miu[j];

    for(int i = 1; i <= n; i ++ ) sum[i] += sum[i - 1];
}

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll f(ll n, ll m)
{
    ll res = 0;
    for(ll l = 1, r; l <= min(n, m); l = r + 1)
    {
        r = min(getr(n, l), getr(m, l));
        res += (sum[r] - sum[l - 1]) * (n / l) * (m / l);
    }
    return res;
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
        printf("%lld\n", f(n, m));
    }

    return 0;
}
