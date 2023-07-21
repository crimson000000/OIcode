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

const int N = 1e6 + 10, mod = 998244353;
ll fact[N];
ll n, k;
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

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    if(k >= n)
    {
        puts("0");
        return 0;
    }

    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;

    if(!k)
    {
        cout << fact[n] << endl;
        return 0;
    }
    
    ans = fact[n] * qmi(fact[k], mod - 2, mod) % mod;
    ll res = 0;
    for(int i = 0; i <= n - k; i ++ )
    {
        if((n - k - i) & 1) 
            res = (res - qmi(i, n, mod) * qmi(fact[i], mod - 2, mod) % mod * qmi(fact[n - k - i], mod - 2, mod) % mod + mod) % mod;
        else res = (res + qmi(i, n, mod) * qmi(fact[i], mod - 2, mod) % mod * qmi(fact[n - k - i], mod - 2, mod) % mod + mod) % mod;
    }

    ans = ans * res % mod;
    cout << (ans << 1) % mod << endl;

    return 0;
}
