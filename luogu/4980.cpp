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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e7 + 10, mod = 1e9 + 7;
int primes[N], phi[N], cnt;
bitset<N> st;
int n;

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
    phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            ll t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * phi[primes[j]];
        }
    }
}

inline ll Phi(ll x)
{
    if(x < N - 5) return phi[x];
    ll res = x;
    for(int i = 1; primes[i] <= x / primes[i]; i ++ )
    {
        if(x % primes[i] == 0)
        {
            res = res / primes[i] * (primes[i] - 1);
            while(x % primes[i] == 0) x /= primes[i];
        }
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

inline ll solve(ll n)
{
    ll res = 0;
    for(int i = 1; i <= n / i; i ++ )
    {
        if(n % i == 0)
        {
            res = (res + qmi(n, i, mod) * Phi(n / i) % mod) % mod;
            if(i * i != n)
                res = (res + qmi(n, n / i, mod) * Phi(i) % mod) % mod;
        }
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 5);

    // for(int i = 1; i <= 100; i ++ ) cout << Phi(i) << ' ';

    int T = read();
    while(T -- )
    {
        n = read();
        printf("%lld\n", solve(n) * qmi(n, mod - 2, mod) % mod);
    }

    return 0;
}
