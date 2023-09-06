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

const int N = 1e6 + 10, mod = 1e8 + 7;
ll f[N];
ll A[N];
ll n, m;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    ll tot = qmi(2, n, mod) - 1;
    A[0] = 1;
    for(int i = 1; i <= m; i ++ )
        A[i] = A[i - 1] * (tot - i + 1 + mod) % mod;

    f[0] = 1;

    for(int i = 2; i <= m; i ++ )
    {
        f[i] = (A[i - 1] - f[i - 1] - f[i - 2] * (i - 1) % mod * (tot - i + 2) % mod + mod) % mod;
    }

    ll factm = 1;
    for(int i = 1; i <= m; i ++ ) factm = factm * i % mod;
    factm = qmi(factm, mod - 2, mod);

    cout << f[m] * factm % mod << endl;

    return 0;
}