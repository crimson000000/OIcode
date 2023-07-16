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

const int N = 1e6 + 10, mod = 998244353;
ll A[N], B[N];
ll a[N], b[N];
int n, m;

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

inline void copy()
{
    for(int i = 0; i < n; i ++ ) a[i] = A[i], b[i] = B[i];
}

inline void OR(ll f[], int opt)
{
    for(int m = 2; m <= n; m <<= 1)
        for(int k = 0; k <= n; k += m)
            for(int j = 0; j < m / 2; j ++ )
                f[j + k + m / 2] = (f[j + k + m / 2] + f[j + k] * opt + mod) % mod;
}

inline void AND(ll f[], int opt)
{
    for(int m = 2; m <= n; m <<= 1)
        for(int k = 0; k <= n; k += m)
            for(int j = 0; j < m / 2; j ++ )
                f[j + k]  = (f[j + k] + f[j + k + m / 2] * opt + mod) % mod;
}

inline void XOR(ll f[], int opt)
{
    for(int m = 2; m <= n; m <<= 1)
        for(int k = 0; k <= n; k += m)
            for(int j = 0; j < m / 2; j ++ )
            {
                f[j + k] = (f[j + k] + f[j + k + m / 2]) % mod;
                f[j + k + m / 2] = (f[j + k] - 2 * f[j + k + m / 2] % mod + mod) % mod;
                f[j + k] = f[j + k] * opt % mod;
                f[j + k + m / 2] = f[j + k + m / 2] * opt % mod;
            }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = 1 << m;
    for(int i = 0; i < n; i ++ ) A[i] = read();
    for(int i = 0; i < n; i ++ ) B[i] = read();

    copy();
    OR(a, 1), OR(b, 1);
    for(int i = 0; i < n; i ++ ) a[i] = a[i] * b[i] % mod;
    OR(a, -1);
    for(int i = 0; i < n; i ++ ) printf("%lld ", a[i]);
    puts("");

    copy();
    AND(a, 1), AND(b, 1);
    for(int i = 0; i < n; i ++ ) a[i] = a[i] * b[i] % mod;
    AND(a, -1);
    for(int i = 0; i < n; i ++ ) printf("%lld ", a[i]);
    puts("");

    copy();
    XOR(a, 1), XOR(b, 1);
    for(int i = 0; i < n; i ++ ) a[i] = a[i] * b[i] % mod;
    XOR(a, qmi(2, mod - 2, mod));
    for(int i = 0; i < n; i ++ ) printf("%lld ", a[i]);
    puts("");

    return 0;
}
