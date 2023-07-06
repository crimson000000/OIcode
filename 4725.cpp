#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int long long

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

const int N = 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;
int a[N], b[2][N], B[N];
int d[N], in[N];
int X[N], Y[N];
int n;
int rev[N];

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

void NTT(int a[], int lim, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        int gn;
        if(opt == 1) gn = qmi(G, (P - 1) / m, P);
        else gn = qmi(Gi, (P - 1) / m, P);
        for(int k = 0; k < lim; k += m)
        {
            int g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                int t = (ll)a[j + k + m / 2] * g % P;
                int u = a[j + k];
                a[j + k] = (u + t) % P;
                a[j + k + m / 2] = ((ll)u - t + P) % P;
                g = (ll)g * gn % P;
            }
        }
    }
    if(opt == -1)
    {
        int inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ ) a[i] = (ll)a[i] * inv % P;
    }
}

inline void calc(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

inline void mul(int *x, int *y, int lim)
{
    memset(X, 0, sizeof X);
    memset(Y, 0, sizeof Y);
    for(int i = 0; i < (lim >> 1); i ++ ) 
        X[i] = x[i] % P, Y[i] = y[i] % P;
    NTT(X, lim, 1), NTT(Y, lim, 1);
    for(int i = 0; i < lim; i ++ ) 
        X[i] = (ll)X[i] * Y[i] % P;
    NTT(X, lim, -1);
    for(int i = 0; i < lim; i ++ ) 
        x[i] = X[i] % P;
}

void inv(int a[])
{
    int cur = 0;
    b[cur][0] = qmi(a[0], P - 2, P);
    int base = 1, lim = 2, len = 1;
    calc(lim, len);
    while(base <= (n << 1))
    {
        cur ^= 1;
        memset(b[cur], 0, sizeof b[cur]);
        for(int i = 0; i < base; i ++ ) b[cur][i] = (ll)b[cur ^ 1][i] * 2 % P;
        mul(b[cur ^ 1], b[cur ^ 1], lim);
        mul(b[cur ^ 1], a, lim);
        for(int i = 0; i < base; i ++ )
            b[cur][i] = ((ll)b[cur][i] - b[cur ^ 1][i] + P) % P;
        base <<= 1, lim <<= 1, len ++;
        calc(lim, len);
    }
    for(int i = 0; i < lim; i ++ ) B[i] = b[cur][i];
}

void derivative(int a[])
{
    for(int i = 0; i < n - 1; i ++ )
        d[i] = (ll)(i + 1) * a[i + 1] % P;
    d[n - 1] = 0;
}

void integral(int a[])
{
    for(int i = 1; i < n; i ++ )
        in[i] = (ll)qmi(i, P - 2, P) * a[i - 1] % P;
    in[0] = 0;
}

void ln(int a[])
{
    derivative(a);
    inv(a);

    int lim = 1, len = 0;
    while(lim <= n * 2) lim <<= 1, len ++;
    calc(lim, len);

    mul(d, B, lim);

    integral(d);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 0; i < n; i ++ ) a[i] = read();

    ln(a);

    for(int i = 0; i < n; i ++ ) cout << in[i] << ' ';

    return 0;
}
