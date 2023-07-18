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

const int N = 310, mod = 1e9 + 7;
int n;
struct matrix
{
    ll a[N][N];
    // matrix() {memset(a, 0, sizeof a), n = m = 0;}
    // matrix(int _n, int _m): n(_n), m(_m) {memset(a, 0, sizeof a); }

    ll * operator [] (int x)
    {
        return a[x];
    }

    inline matrix operator + (matrix b)
    {
        matrix res = *this;
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                res[i][j] = (res[i][j] + b[i][j]) % mod;
        return res;
    } 

    inline matrix operator - (matrix b)
    {
        matrix res = *this;
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                res[i][j] = (res[i][j] - b[i][j] + mod) % mod;
        return res;
    } 

    inline ll Det()
    {
        ll res = 1, w = 1;
        for(int i = 1; i < n; i ++ )
        {
            for(int j = i + 1; j < n; j ++ )
            {
                while(a[i][i])
                {
                    ll div = a[j][i] / a[i][i];
                    for(int k = i; k < n; k ++ )
                        a[j][k] = (a[j][k] - div * a[i][k] % mod + mod) % mod;
                    swap(a[j], a[i]);
                    w = -w;
                }
                swap(a[j], a[i]);
                w = -w;
            }
        }
        for(int i = 1; i < n; i ++ ) res = res * a[i][i] % mod;
        res *= w;
        return (res % mod + mod) % mod;
    }
}L;
int m, t;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), t = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        if(a == 1) a = n;
        else if(a == n) a = 1;
        if(b == 1) b = n;
        else if(b == n) b = 1;

        if(t == 0)
        {
            L[a][b] = (L[a][b] - c + mod) % mod;
            L[b][a] = (L[b][a] - c + mod) % mod;
            L[a][a] = (L[a][a] + c) % mod;
            L[b][b] = (L[b][b] + c) % mod;
        }
        else
        {
            L[a][b] = (L[a][b] - c + mod) % mod;
            L[b][b] = (L[b][b] + c) % mod;
        }
    }

    // for(int i = 1; i <= n; i ++ )
    // {
    //     for(int j = 1; j <= n; j ++ )
    //         cout << L[i][j] << ' ';
    //     puts("");
    // } 

    ans = L.Det();

    printf("%lld\n", ans);

    return 0;
}