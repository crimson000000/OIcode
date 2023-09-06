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

const int N = 5e6 + 10;
ll n, k, mod;
ll a[N], pre[N], inv[N];

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

    n = read(), mod = read(), k = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    pre[0] = 1;
    for(int i = 1; i <= n; i ++ ) pre[i] = pre[i - 1] * a[i] % mod;
    inv[n] = qmi(pre[n], mod - 2, mod);

    for(int i = n - 1; i >= 0; i -- ) inv[i] = inv[i + 1] * a[i + 1] % mod;
    for(int i = 1; i <= n; i ++ )
        inv[i] = inv[i] * pre[i - 1] % mod;

    ll ans = 0, kk = k;
    for(int i = 1; i <= n; i ++ )
    {
        ans = (ans + kk * inv[i]) % mod;
        kk = kk * k % mod;
    }

    cout << ans << endl;

    return 0;
}