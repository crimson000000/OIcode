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
int miu[N];
ll a, b, c, d, k;
int primes[N], cnt;
bitset<N> st;

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
            miu[t] = -miu[i];
            if(i % primes[j] == 0) 
            {
                miu[t] = 0;
                break;
            } 
        }
    }
    for(int i = 1; i <= n; i ++ ) miu[i] += miu[i - 1];
}

inline ll getr(ll a, ll x)
{
    return a / (a / x);
}

inline ll solve(int n, int m, int k)
{
    n /= k, m /= k;
    ll ans = 0;
    for(int l = 1, r = 0; l <= min(n, m); l = r + 1)
    {
        r = min(getr(n, l), getr(m, l));
        ans = ans + (miu[r] - miu[l - 1]) * (ll)(n / l) * (m / l);
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
        a = read(), b = read(), c = read(), d = read(), k = read();
        printf("%lld\n", solve(b, d, k) - solve(a - 1, d, k) - solve(b, c - 1, k) + solve(a - 1, c - 1, k));
    }

    return 0;
}
