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

const int N = 1010;
ll a[N][N], mod;
int n;

inline ll Det()
{
    ll res = 1, w = 1;
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = i + 1; j <= n; j ++ )
        {
            while(a[i][i])
            {
                ll div = a[j][i] / a[i][i];
                for(int k = i; k <= n; k ++ )
                    a[j][k] = (a[j][k] - div * a[i][k] % mod + mod) % mod;
                swap(a[i], a[j]);
                w = -w;
            }
            swap(a[i], a[j]);
            w = -w;
        }
    }
    for(int i = 1; i <= n; i ++ ) res = res * a[i][i] % mod;
    res *= w;
    return (res % mod + mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            a[i][j] = read() % mod;
    
    ll ans = Det();

    printf("%lld\n", ans);

    return 0;
}