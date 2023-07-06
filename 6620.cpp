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

const int N = 2010;
ll S[N][N];
ll a[N], b[N];
ll n, x, mod, m;
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
    S[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % mod) % mod;

    for(int i = 0; i <= m; i ++ )
        for(int j = i; j <= m; j ++ )
            b[i] = (b[i] + a[j] * S[j][i] % mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), x = read(), mod = read(), m = read();
    for(int i = 0; i <= m; i ++ ) a[i] = read();

    init(m);

    ll ndown = 1;
    for(int i = 0; i <= m; i ++ )
    {
        ans = (ans + b[i] * ndown % mod * qmi(x, i, mod) % mod * qmi(x + 1, n - i, mod) % mod) % mod;
        ndown = ndown * (n - i) % mod;
    }

    cout << ans << endl;

    return 0;
}