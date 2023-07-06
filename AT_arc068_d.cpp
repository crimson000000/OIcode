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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 3010, mod = 1e9 + 7;
ll f[N][N];
ll fact[N], invfact[N];
ll n, k, ans;

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
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[n - m] % mod * invfact[m] % mod;
}

inline ll g(int n, int m)
{
    return C(n - 1, m);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    
    for(int i = 2; i <= n; i ++ ) f[1][i] = 1;
    for(int i = 1; i <= k - 1; i ++ )
    {
        f[i + 1][n - i + 1] = f[i][n - i + 1];
        for(int j = n - i; j >= 2; j -- )
            f[i + 1][j] = (f[i + 1][j + 1] + f[i][j]) % mod;
    }

    for(int i = 2; i <= n - k + 2; i ++ )
        ans = (ans + f[k - 1][i]) % mod;
    
    if(k == 1) ans = 1;
    if(n - k - 1 >= 0) cout << ans * qmi(2, n - k - 1, mod) % mod << endl;
    else cout << ans << endl;

    return 0;
}
