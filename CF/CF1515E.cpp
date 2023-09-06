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

const int N = 1010;
ll f[N][N];
int n, mod;
ll C[N][N];

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
    for(int i = 0; i <= n; i ++ )
    {
        C[i][0] = 1;
        for(int j = 1; j <= i; j ++ )
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
}

inline ll g(int k)
{
    return qmi(2, k - 1, mod);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read();
    init(n);

    for(int i = 1; i <= n; i ++ )
    {
        f[i][i] = g(i);
        for(int j = 1; j < i; j ++ )
            for(int k = 1; k < j; k ++ )
                f[i][j] = (f[i][j] + f[i - k - 1][j - k] * g(k) % mod * C[j][k] % mod) % mod;
    } 

    ll ans = 0;
    for(int i = 1; i <= n; i ++ )
        ans = (ans + f[n][i]) % mod;
    
    cout << ans << endl;

    return 0;
}
