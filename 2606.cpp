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

const int N = 3e6 + 10;
ll f[N], siz[N];
ll fact[N], invfact[N];
int n, mod;

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
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

inline ll lucas(int n, int m)
{
    if(n < mod && m < mod) return C(n, m);
    if(n < 0 || m < 0 || n < m) return 0;
    return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read();
    init(min(n, mod - 1));
    for(int i = n; i >= 1; i -- ) siz[i] = f[i] = 1;
    for(int i = n; i >= 1; i -- )
    {
        siz[i / 2] += siz[i];
        f[i] = f[i] * lucas(siz[i] - 1, siz[i << 1]) % mod;
        f[i / 2] = f[i / 2] * f[i] % mod;
    }

    cout << f[1] << endl;
    
    return 0;
}