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

const ll mod = 1e9 + 7, N = 2e6 + 10;
ll n, k;
ll fact[N], f[N], invfact[N], point[N];
ll pre[N], suf[N];

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

ll primes[N], cnt;
bool st[N];
void init(int n)
{
    // f
    point[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            point[i] = qmi(i, k, mod);
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            point[primes[j] * i] = point[primes[j]] * point[i] % mod;
            if(i % primes[j] == 0) break;
        }
    }
    for(int i = 1; i <= n; i ++ ) f[i] = (f[i - 1] + point[i]) % mod;
    // fact
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    init(k + 2);
    // for(int i = 0; i <= 3; i ++ ) cout << fact[i] << ' ';
    // puts("");
    // for(int i = 0; i <= 3; i ++ ) cout << invfact[i] << ' ';
    // puts("");

    pre[0] = 1;
    for(int i = 1; i <= k + 2; i ++ ) pre[i] = pre[i - 1] * (n - i) % mod;
    suf[k + 3] = 1;
    for(int i = k + 2; i >= 0; i -- ) suf[i] = suf[i + 1] * (n - i) % mod;

    ll ans = 0;
    for(int i = 1; i <= k + 2; i ++ )
        if((k - i) & 1)
            ans = (ans - f[i] * pre[i - 1] % mod * suf[i + 1] % mod * invfact[i - 1] % mod * invfact[k + 2 - i] % mod + mod) % mod;
        else
            ans = (ans + f[i] * pre[i - 1] % mod * suf[i + 1] % mod * invfact[i - 1] % mod * invfact[k + 2 - i] % mod) % mod;

    cout << ans << endl;

    return 0;
}
