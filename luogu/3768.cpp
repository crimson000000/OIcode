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

const int N = 5e6 + 10;
ll n, mod;
ll inv[10];
unordered_map<ll, ll> s;
ll f[N];
bitset<N> st;
int primes[N], cnt;
ll ans;

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
    inv[1] = 1;
    for(int i = 2; i <= 8; i ++ ) 
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    f[1] = 1;
    for(ll i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            f[i] = (i - 1) % mod;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = i * primes[j];
            st[t] = true;
            if(i % primes[j] == 0)
            {
                f[t] = f[i] * primes[j] % mod;
                break;
            }
            f[t] = f[i] * f[primes[j]] % mod;
        }
    }
    for(int i = 1; i <= n; i ++ ) 
    {
        f[i] = f[i] * i % mod * i % mod;
        f[i] = (f[i] + f[i - 1]) % mod;
    }
}

inline ll g(ll n)
{
    n %= mod;
    return (n % mod * (n + 1) % mod * inv[2] % mod) * (n % mod * (n + 1) % mod * inv[2] % mod) % mod;
}

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll sum2(ll n)
{
    n %= mod;
    return n % mod * (n + 1) % mod * (2 * n % mod + 1) % mod * inv[6] % mod;
}

inline ll sum3(ll n)
{
    n %= mod;
    return n * n % mod * (n + 1) % mod * (n + 1) % mod * inv[4] % mod;
}

inline ll getf(ll n)
{
    if(n < N - 5) return f[n];
    if(s.count(n)) return s[n];
    s[n] = sum3(n);
    for(ll l = 2, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        s[n] = (s[n] - (sum2(r) - sum2(l - 1) + mod) % mod * getf(n / l) % mod + mod) % mod;
    }
    return s[n];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    mod = read(), n = read();
    init(N - 5);

    for(ll l = 1, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        ans = (ans + (getf(r) - getf(l - 1) + mod) % mod * g(n / l) % mod) % mod;
    }

    cout << ans << endl;

    return 0;
}
