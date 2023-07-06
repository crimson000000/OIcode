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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, G = 3, Gi = 332748118, P = 998244353;
int rev[N], a[N], b[N];

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

void calcrev(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

int n;
void NTT(int a[], int lim, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(rev[i] > i)
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
                a[j + k] = ((ll)u + t) % P;
                a[j + k + m / 2] = ((ll)u - t + P) % P;
                g = (ll)g * gn % P;
            }
        }
    }
    if(opt == -1)
    {
        int inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ )
            a[i] = ((ll)a[i] * inv % P);
    }
}

int h[N];
inline void invvv(int a[], int b[], int n)
{
    if(n == 1) 
    {
        b[0] = qmi(a[0], P - 2, P);
        return;
    }
    invvv(a, b, (n + 1) >> 1);
    int lim = 1, len = 0;
    while(lim <= 2 * n) len ++, lim <<= 1;
    for(int i = 0; i < lim; i ++ )
    {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
        if(i < n) h[i] = a[i];
        else h[i] = 0;
    }
    NTT(h, lim, 1), NTT(b, lim, 1);
    for(int i = 0; i < lim; i ++ )
        b[i] = (2 * b[i] % P - (ll)h[i] * b[i] % P * b[i] % P + P) % P;
    NTT(b, lim, -1);
    for(int i = n; i <= lim; i ++ ) b[i] = 0;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 0; i < n; i ++ ) a[i] = read();

    invvv(a, b, n);

    for(int i = 0; i < n; i ++ ) cout << b[i] << ' ';

    return 0;    
}
