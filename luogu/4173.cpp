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

const int N = 1e6 + 10, mod = 998244353;
int rev[N];
int lim, len;
char a[N], b[N];
ll A[N], B[N], f[N];
ll F[N], G[N];
int n, m;

inline void calc()
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

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

inline void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn = qmi(opt == 1 ? 3 : 332748118, (mod - 1) / m, mod);
        for(int k = 0; k < lim; k += m)
        {
            ll g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                ll u = a[j + k];
                ll t = a[j + k + m / 2] * g % mod;
                a[j + k] = (u + t) % mod;
                a[j + k + m / 2] = (u - t + mod) % mod;
                g = g * gn % mod;
            }
        }
    }
    if(opt == -1)
    {
        ll inv = qmi(lim, mod - 2, mod);
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * inv % mod;
    }
}

inline void get(ll a[], char s[], int n)
{
    for(int i = 0; i < n; i ++ )
        a[i] = ((s[i] == '*') ? 0 : s[i] - 'a' + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = read();
    scanf("%s%s", a, b);

    lim = 1;
    while(lim < 2 * n) lim <<= 1, len ++;
    calc();

    reverse(a, a + m);
    get(A, a, m), get(B, b, n);
    
    for(int i = 0; i < lim; i ++ ) 
    {
        F[i] = A[i] * A[i] * A[i] % mod;
        G[i] = B[i] % mod;
    }

    NTT(F, 1), NTT(G, 1);
    for(int i = 0; i < lim; i ++ ) 
    {
        f[i] = (f[i] + F[i] * G[i] % mod) % mod;
        F[i] = G[i] = 0;
    }

    for(int i = 0; i < lim; i ++ ) 
    {
        F[i] = A[i] % mod;
        G[i] = B[i] * B[i] * B[i] % mod;
    }

    NTT(F, 1), NTT(G, 1);
    for(int i = 0; i < lim; i ++ ) 
    {
        f[i] = (f[i] + F[i] * G[i] % mod) % mod;
        F[i] = G[i] = 0;
    }

    for(int i = 0; i < lim; i ++ ) 
    {
        F[i] = A[i] * A[i] % mod;
        G[i] = B[i] * B[i] % mod;
    }

    NTT(F, 1), NTT(G, 1);
    for(int i = 0; i < lim; i ++ ) 
    {
        f[i] = (f[i] - 2 * F[i] * G[i] % mod) % mod;
        F[i] = G[i] = 0;
    }

    NTT(f, -1);

    int cnt = 0;
    for(int i = m - 1; i < n; i ++ )
        if(!f[i])
            cnt ++;

    printf("%d\n", cnt);

    for(int i = m - 1; i < n; i ++ )
        if(!f[i])
            printf("%d ", i - m + 2);

    return 0;
}