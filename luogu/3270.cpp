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

const int N = 1010, mod = 1e9 + 7;
ll fact[N], invfact[N];
int n, m, k;
ll u[N], r[N];
ll S[N];
ll ans;

ll qmi(ll a, ll k, ll p)
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

void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

int primes[N], cnt;
bitset<N> st;
ll pk[N], f[N];
void F(int n, int k)
{
    cnt = 0;
    pk[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            pk[i] = qmi(i, k, mod);
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            int t = i * primes[j];
            pk[t] = pk[i] * pk[primes[j]] % mod;
            st[t] = true;
            if(i % primes[j] == 0) break;
        }
    }
    f[1] = pk[1];
    for(int i = 2; i <= n; i ++ )
        f[i] = (f[i - 1] + pk[i]) % mod;
}

ll lagrange(ll n, ll k)
{
    static ll suf[N], pre[N];
    F(k + 10, k);
    if(n <= k + 10) return f[n];
    pre[0] = 1;
    pre[1] = n - 1;
    for(int i = 2; i <= k + 2; i ++ ) pre[i] = pre[i - 1] * (n - i) % mod;
    suf[k + 3] = 1;
    suf[k + 2] = n - k - 2;
    for(int i = k + 1; i >= 1; i -- ) suf[i] = suf[i + 1] * (n - i) % mod;
    ll res = 0;
    for(int i = 1; i <= k + 2; i ++ )
    {
        if((k + 2 - i) & 1)
            res = (res - f[i] * pre[i - 1] % mod * suf[i + 1] % mod * 
            invfact[i - 1] % mod * invfact[k + 2 - i] % mod + mod) % mod;
        else
            res = (res + f[i] * pre[i - 1] % mod * suf[i + 1] % mod * 
            invfact[i - 1] % mod * invfact[k + 2 - i] % mod) % mod;
    }
    return res;
}

ll g(int i)
{
    ll res = C(n - 1, i);
    for(int j = 1; j <= m; j ++ )
    {
        res = res * C(n - i - 1, n - r[j] - i) % mod * S[j] % mod;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    init(N - 5);
    for(int i = 1; i <= m; i ++ ) u[i] = read();
    for(int i = 1; i <= m; i ++ ) r[i] = read();

    for(int j = 1; j <= m; j ++ )
        for(int l = 0; l <= r[j] - 1; l ++ )
            S[j] = (S[j] + C(r[j] - 1, l) * qmi(u[j], r[j] - 1 - l, mod) % mod * 
                (((l & 1) ? mod - 1 : 1)) % mod * lagrange(u[j], n - r[j] + l) % mod) % mod;

    for(int i = k; i < n; i ++ )
    {
        ans = (ans + (((i - k) & 1) ? mod - 1 : 1) * C(i, k) % mod * g(i) % mod) % mod;
    }

    cout << ans << endl;

    return 0;
}