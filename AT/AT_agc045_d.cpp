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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 1e7 + 10, mod = 1e9 + 7;
ll fact[N], inv[N];
ll invfact[N];
int n, m;
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
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
    inv[1] = 1;
    for(int i = 2; i <= n; i ++ )
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

inline ll calc(int a, int b, int c)
{
    return a * fact[a + b + c] % mod * inv[a + b] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(n);

    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 0; j < i; j ++ )
            ans = (ans + (((j) & 1) ? mod - 1 : 1) * C(i - 1, j) % mod * calc(i - j - 1, n - m, m - i) % mod) % mod;
    }

    for(int i = 0; i <= m; i ++ )
        ans = (ans + ((i & 1) ? mod - 1 : 1) * C(m, i) % mod * calc(m - i, n - m, 0) % mod) % mod;

    cout << ans << endl;

    return 0;
}