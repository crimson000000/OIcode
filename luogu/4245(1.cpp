#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

using i128 = __int128;

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

inline void write(i128 x)
{
    if(x > 10) write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1e6 + 10;
i128 mod;
string modd = "21267647932558654224715329996419235841";
int n, m, p;
i128 F[N], G[N];
int rev[N];
int lim, len;

inline void calc()
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

inline i128 mul(i128 a, i128 b, i128 p)
{
    i128 res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

inline i128 qmi(i128 a, i128 k, i128 p)
{
    i128 res = 1;
    while(k)
    {
        if(k & 1) res = mul(res, a, p);
        a = mul(a, a, p);
        k >>= 1;
    }
    return res;
}

inline void NTT(i128 a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        i128 gn = qmi(opt == 1 ? 11 : qmi(11, mod - 2, mod), (mod - 1) / m, mod);
        for(int k = 0; k < lim; k += m)
        {
            i128 g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                i128 u = a[j + k];
                i128 t = mul(a[j + k + m / 2], g, mod);
                a[j + k] = (u + t) % mod;
                a[j + k + m / 2] = (u - t + mod) % mod;
                g = mul(g, gn, mod); 
            }
        }
    }
    if(opt == -1)
    {
        i128 inv = qmi(lim, mod - 2, mod);
        for(int i = 0; i < lim; i ++ ) a[i] = mul(a[i], inv, mod);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    for(int i = 0; i < modd.size(); i ++ )
        mod = mod * 10 + modd[i] - '0';

    // write(mod);
    // puts("");

    n = read(), m = read(), p = read();

    for(int i = 0; i <= n; i ++ ) F[i] = read();
    for(int i = 0; i <= m; i ++ ) G[i] = read();

    lim = 1;
    while(lim <= (n + m)) lim <<= 1, len ++;
    calc();
    
    NTT(F, 1), NTT(G, 1);
    for(int i = 0; i < lim; i ++ ) F[i] = mul(F[i], G[i], mod);
    NTT(F, -1);

    for(int i = 0; i <= n + m; i ++ ) 
        printf("%lld ", ll(F[i] % p));
    
    return 0;
}
