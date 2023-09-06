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

const int N = 5010, mod = 998244353;
ll fact[N], invfact[N];
int f[N][N];
int inv[N];
int n, m;

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

inline int C(int n, int m)
{
    ll res = 1;
    for(int i = n - m + 1; i <= n; i ++ )
        res = res * i % mod;
    for(int i = 1; i <= m; i ++ )
        res = res * inv[i] % mod;
    return res;
}

inline void init(int m)
{
    inv[1] = 1;
    for(int i = 2; i <= m; i ++ )
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;

    for(int i = 0; i <= m; i ++ ) f[0][i] = qmi(2, i, mod);
    for(int i = 0; i <= m; i ++ ) f[i][0] = C(n, i);

    for(int i = 1; i <= m; i ++ )   
        for(int j = 1; j <= m; j ++ )
            f[i][j] = (2ll * f[i][j - 1] % mod - f[i - 1][j] + f[i - 1][j - 1] + mod) % mod;
} 

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(m);

    ll ans = 0;
    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= m; j ++ )
            ans ^= f[i][j];
    
    cout << ans << endl;

    return 0;
}