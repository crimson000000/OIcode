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

const int N = 110, mod = 1e9 + 7;
struct mat
{
    ll a[N][N];
    ll n, m;

    ll * operator [] (ll x) 
    {
        return a[x];
    }

    void init()
    {
        memset(a, 0, sizeof a);
    }

    mat operator * (const mat& M) const 
    {
        mat tmp;
        tmp.init();
        tmp.n = n, tmp.m = M.m;
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= M.m; k ++ )
                for(int j = 1; j <= m; j ++ )
                    tmp[i][j] = (tmp[i][j] + (ll)a[i][k] * M.a[k][j] % mod) % mod;
        return tmp;
    }
}base, f;

ll n, siz;
bitset<N> x, y;

mat qmi(mat a, ll k)
{
    mat res;
    res.init();
    res.n = res.m = a.n;
    for(int i = 1; i <= res.n; i ++ ) res[i][i] = 1;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
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

    n = read();
    ll p = read();
    while(p -- )
    {
        ll t = read();
        x[t] = 1;
    }

    p = read();
    while(p -- )
    {
        ll t = read();
        y[t] = 1;
    }

    x &= y;
    for(int i = 1; i <= 100; i ++ )
        if(x[i])
        {
            base[100 - i + 1][100] = 1;
        }

    for(int i = 1; i < 100; i ++ )
        base[i + 1][i] = 1;

    base.m = base.n = 100;
    
    // for(int i = 1; i <= 100; i ++ )
    // {
    //     for(int j = 1; j <= 100; j ++ )
    //         cout << base[i][j] << ' ';
    //     puts("");
    // }

    f[1][0] = 1;
    for(int i = 1; i <= 100; i ++ )
        for(int j = 1; j <= 100; j ++ )
            if(x[j] && i >= j)
                f[1][i] = (f[1][i] + f[1][i - j]) % mod;
    
    f.n = 1, f.m = 100;
    if(n <= 100) cout << f[1][n] << endl;
    else
    {
        f = f * qmi(base, n - 100);
        cout << f[1][100] << endl;
    }

    return 0;
}
