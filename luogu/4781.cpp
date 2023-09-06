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

const int mod = 998244353, N = 1e5 + 10;
int n, k;

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

ll inv(ll a)
{
    return qmi(a, mod - 2, mod);
}

int x[N], y[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ )
    {
        x[i] = read(), y[i] = read();
    }

    ll res = 0;
    for(int i = 1; i <= n; i ++ )
    {
        ll s1 = 1, s2 = 1;
        for(int j = 1; j <= n; j ++ )
            if(j != i)
            {
                s1 = s1 * (k - x[j]) % mod;
                s2 = s2 * (x[i] - x[j] + mod) % mod;
            }

        res = (res + (ll)y[i] * s1 % mod * inv(s2) % mod) % mod;
    }
    
    cout << (res % mod + mod) % mod << endl;

    return 0;
}
