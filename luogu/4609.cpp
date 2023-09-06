#define LOCAL
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 50010, M = 210, mod = 1e9 + 7;
ll S[N][M], C[N][M];
int n, A, B;

inline void init(int n, int m)
{
    S[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j] % mod) % mod;

    C[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        C[i][0] = 1;
        for(int j = 1; j <= m; j ++ )
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(50000, 200);

    while(T -- )
    {
        n = read(), A = read(), B = read();
        printf("%lld\n", S[n - 1][A + B - 2] * C[A + B - 2][A - 1] % mod);
    }

    return 0;
}
