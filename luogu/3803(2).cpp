#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 3e6 + 10, mod = 998244353, GG = 3, Gi = 332748118;
ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}
int F[N], G[N];
int rev[N];
int n, m;
int lim = 1, len;

void NTT(int a[], int opt)
{
    for (int i = 0; i < lim; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for (int dep = 1; dep <= up; dep++)
    {
        int m = 1 << dep;
        int gn;
        if(opt == 1) gn = qmi(GG, (mod - 1) / m, mod);
        else gn = qmi(Gi, (mod - 1) / m, mod);
        for (int k = 0; k < lim; k += m)
        {
            int g = 1;
            for (int j = 0; j < m / 2; j++)
            {
                int t = (ll)g * a[j + k + m / 2] % mod;
                int u = a[j + k];
                a[j + k] = (u + t) % mod;
                a[j + k + m / 2] = (u - t + mod) % mod;
                g = (ll)g * gn % mod;
            }
        }
    }
    if (opt == -1)
    {
        int inv = qmi(lim, mod - 2, mod);
        for (int i = 0; i < lim; i++)
            a[i] = (ll)a[i] * inv % mod;
    }
}

signed main()
{
#ifdef LOCAL
    freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
    freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
#endif

    n = read(), m = read();
    for (int i = 0; i <= n; i++)
        F[i] = (read() + mod) % mod;
    for (int i = 0; i <= m; i++)
        G[i] = (read() + mod) % mod;

    while (lim <= n + m)
        lim <<= 1, len++;
    for (int i = 0; i < lim; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    NTT(F, 1), NTT(G, 1);
    for (int i = 0; i <= lim; i++)
        F[i] = (ll)F[i] * G[i] % mod;
    NTT(F, -1);

    for (int i = 0; i <= n + m; i++)
        cout << F[i] % mod << ' ';

    return 0;
}
