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

const int mod = 998244353;
ll a[10];
ll n, s;

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

const ll wn = qmi(3, 998244352 / 4, mod);

void solve()
{
    n = read(), s = read();
    for(int i = 0; i < 4; i ++ ) a[i] = read();

    ll ans = 0;
    for(int j = 0; j <= 3; j ++ )
    {
        ll tmp = 0;
        for(int k = 0; k <= 3; k ++ )
        {
            tmp = (tmp + qmi(qmi(wn, mod - 2, mod), k * j, mod) * 
                qmi(s * qmi(wn, k, mod) % mod + 1, n, mod)) % mod;
        }
        ans = (ans + tmp * a[j] % mod) % mod;
    }
    cout << ans * qmi(4, mod - 2, mod) % mod << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}