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

const int N = 2500, P = 2333;
ll f[N][N], C[N][N];

inline void init(int n)
{
    C[0][0] = C[1][0] = C[1][1] = 1;
    for(int i = 2; i <= n; i ++ )
        for(int j = 0; j <= i; j ++ )
        {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
        }

    for(int i = 0; i <= n; i ++ )
    {
        f[i][0] = 1;
        for(int j = 1; j <= n; j ++ ) f[i][j] = (f[i][j - 1] + C[i][j]) % P;
    }
}

inline ll lucas(ll n, ll m)
{
    if(n < P && m < P) return C[n][m];
    return lucas(n % P, m % P) * lucas(n / P, m / P) % P;
}

inline ll solve(ll n, ll k)
{
    if(n < P && k < P) return f[n][k];
    return (solve(n % P, P - 1) * solve(n / P, k / P - 1) % P + lucas(n / P, k / P) * solve(n % P, k % P) % P) % P;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(P);
    int T = read();
    while(T -- )
    {
        ll n = read(), k = read();
        printf("%lld\n", solve(n, k));
    }

    return 0;
}