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

const int N = 1e6 + 10, G = 3, P = 998244353, Gi = 332748118;
int rev[N];
ll X[N], Y[N];

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

void NTT(ll a[], int lim, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn;
        if(opt == 1) gn = qmi(G, (P - 1) / m, P);
        else gn = qmi(Gi, (P - 1) / m, P);
        for(int k = 0; k < lim; k += m)
        {
            ll g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                ll t = (ll)a[j + k + m / 2] * g % P;
                ll u = a[j + k];
                a[j + k] = (u + t) % P;
                a[j + k + m / 2] = ((ll)u - t + P) % P;
                g = (ll)g * gn % P;
            }
        }
    }
    if(opt == -1)
    {
        ll inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * inv % P;
    }
}

inline void calc(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

void mul(ll *x, ll *y, ll *to, int n, int m)
{
    int lim = 1, len = 0;
    while(lim < (n + m)) lim <<= 1, len ++;
    calc(lim, len);
    for(int i = (lim >> 1); i <= lim; i ++ ) X[i] = Y[i] = 0;
    for(int i = 0; i < (lim >> 1); i ++ )
        X[i] = x[i], Y[i] = y[i];
    NTT(X, lim, 1), NTT(Y, lim, 1);
    for(int i = 0; i < lim; i ++ ) 
        to[i] = (ll)X[i] * Y[i] % P;
    NTT(to, lim, -1);
}

ll h[N];
void inv(ll a[], ll b[], ll n)
{
    if(n == 1)
    {
        b[0] = qmi(a[0], P - 2, P);
        return;
    }
    inv(a, b, (n + 1) >> 1);
    int lim = 1, len = 0;
    while(lim <= (n << 1)) lim <<= 1, len ++;
    calc(lim, len);
    for(int i = 0; i < n; i ++ ) h[i] = a[i];
    for(int i = n; i < lim; i ++ ) h[i] = 0;
    NTT(h, lim, 1), NTT(b, lim, 1);
    for(int i = 0; i < lim; i ++ )
        b[i] = (2 * b[i] - h[i] * b[i] % P * b[i] % P + P) % P;
    NTT(b, lim, -1);
    for(int i = n; i < lim; i ++ ) b[i] = 0;
}


ll b[2][N];
void inv(ll a[], ll to[], ll n)
{
    int cur = 0;
    b[cur][0] = qmi(a[0], P - 2, P);
    int base = 1, lim = 2, len = 1;
    calc(lim, len);
    while(base <= (n + n))
    {
        cur ^= 1;
        memset(b[cur], 0, sizeof b[cur]);
        for(int i = 0; i < base; i ++ ) b[cur][i] = b[cur ^ 1][i] * 2 % P;
        mul(b[cur ^ 1], b[cur ^ 1], b[cur ^ 1], lim);
        mul(b[cur ^ 1], a, b[cur ^ 1], lim);
        for(int i = 0; i < base; i ++ )
            b[cur][i] = (b[cur][i] - b[cur ^ 1][i] + P) % P;
        base <<= 1, lim <<= 1, len ++;
        calc(lim, len);
    }
    for(int i = 0; i < lim; i ++ ) to[i] = b[cur][i];
}


void derivative(ll a[], ll to[], ll n)
{
    for(int i = 0; i < n - 1; i ++ )
        to[i] = (ll)(i + 1) * a[i + 1] % P;
    to[n - 1] = 0;
}

void integral(ll a[], ll to[], ll n)
{
    for(int i = 1; i < n; i ++ )
        to[i] = qmi(i, P - 2, P) * a[i - 1] % P;
    to[0] = 0;
}

ll inte[N], INV[N], d[N], LN[N];
ll a[N];
void ln(ll a[], ll to[], ll n)
{
    derivative(a, d, n);
    inv(a, INV, n);
    mul(d, INV, d, n, n);
    integral(d, to, n);
}

ll c[N], E[N];
inline void exp(ll a[], ll b[], ll n)
{
    if(n == 1)
    {
        b[0] = 1;
        return;
    }
    exp(a, b, (n + 1) >> 1);
    ln(b, LN, n);
    int lim = 1;
    while(lim <= n + n) lim <<= 1;
    for(int i = 0; i < n; i ++ ) c[i] = ((ll)a[i] - LN[i] + P) % P;
    for(int i = n; i < lim; i ++ ) LN[i] = c[i] = 0;
    c[0] ++;
    mul(c, b, b, n, n);
    for(int i = n; i < lim; i ++ ) b[i] = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n = read();
    for(int i = 0; i < n; i ++ ) a[i] = read();
    
    exp(a, E, n);
    for(int i = 0; i < n; i ++ ) cout << E[i] % P << ' ';
    
    return 0;
}