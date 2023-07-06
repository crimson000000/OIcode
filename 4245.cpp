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

const int N = 4e5 + 10, G1 = 998244353, G2 = 1004535809, G3 = 469762049, G = 3;
int n, m, p;
int lim = 1, len;
int rev[N];
int A[3][N], B[3][N];
int a1[N], a2[N], a3[N];
ll ans[N];

__int128 qmi(__int128 a, __int128 k, __int128 p)
{
    __int128 res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

__int128 inv(__int128 a, __int128 mod)
{
    return qmi(a, mod - 2, mod);
}

void NTT(int a[], int mod, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        int gn;
        if(opt == 1) gn = qmi(G, (mod - 1) / m, mod);
        else gn = qmi(qmi(G, mod - 2, mod), (mod - 1) / m, mod);
        for(int j = 0; j < lim; j += m)
        {
            int g = 1;
            for(int k = 0; k < m / 2; k ++ )
            {
                int t = (ll)a[j + k + m / 2] * g % mod;
                int u = a[j + k];
                a[j + k] = (u + t) % mod;
                a[j + k + m / 2] = ((ll)u - t + mod) % mod;
                g = (ll)gn * g % mod;
            }
        }
    }
    if(opt == -1)
    {
        int inv = qmi(lim, mod - 2, mod);
        for(int i = 0; i < lim; i ++ ) a[i] = (ll)a[i] * inv % mod;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), p = read();
    for(int i = 0; i <= n; i ++ ) A[0][i] = read(), A[1][i] = A[2][i] = A[0][i];
    for(int i = 0; i <= m; i ++ ) B[0][i] = read(), B[1][i] = B[2][i] = B[0][i];

    while(lim <= n + m + 2) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    NTT(A[0], G1, 1), NTT(B[0], G1, 1);
    for(int i = 0; i < lim; i ++ ) a1[i] = (ll)A[0][i] * B[0][i] % G1;
    NTT(a1, G1, -1);

    NTT(A[1], G2, 1), NTT(B[1], G2, 1);
    for(int i = 0; i < lim; i ++ ) a2[i] = (ll)A[1][i] * B[1][i] % G2;
    NTT(a2, G2, -1);

    NTT(A[2], G3, 1), NTT(B[2], G3, 1);
    for(int i = 0; i < lim; i ++ ) a3[i] = (ll)A[2][i] * B[2][i] % G3;
    NTT(a3, G3, -1);

    for(int i = 0; i < lim; i ++ )
    {
        __int128 M = (__int128)G1 * G2 * G3;
        ans[i] = ((__int128)a1[i] * M / G1 * inv(M / G1, G1) % M
                    + (__int128)a2[i] * M / G2 * inv(M / G2, G2) % M + 
                    (__int128)a3[i] * M / G3 * inv(M / G3, G3) % M) % M % p;
    }

    for(int i = 0; i <= n + m; i ++ ) cout << ans[i] << ' ';
    
    return 0;
}
