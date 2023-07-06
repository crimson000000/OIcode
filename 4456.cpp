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

const int N = 1e7 + 10;
int fact[N], invfact[N];
int primes[N], cnt;
bitset<N> st;
int ami[N], bmi[N];
ll n, a, b, mod;
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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = (ll)fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
}

inline void init1(int n)
{
    ami[0] = (a == 0);
    bmi[0] = (b == 0);
    ami[1] = bmi[1] = 1;

    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            ami[i] = qmi(i, a, mod);
            bmi[i] = qmi(i, b, mod);
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            ami[t] = (ll)ami[primes[j]] * ami[i] % mod;
            bmi[t] = (ll)bmi[primes[j]] * bmi[i] % mod;
            st[t] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return (ll)fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), a = read(), b = read(), mod = read();

    init(min(n + 1, mod - 1));
    init1(n);

    for(int i = 0; n - i + 1 >= i; i ++ )
    {
        ans = (ans + C(n - i + 1, i) * ami[n - i] % mod * bmi[i] % mod) % mod;
    }

    cout << ans << endl;

    return 0;
}