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

const int N = 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;

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

int n, m;
int a[N], b[N];
int A[N], B[N];
ll a1, b1, a2, b2, ans = 1e18, res;

int rev[N];
int len, lim = 1;
void NTT(int a[], int opt)
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
                a[j + k + m / 2] = (u - t + P) % P;
                g = ((ll)g * gn) % P;
            }
        }
    }
    if(opt == -1)
    {
        int inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ ) a[i] = ((ll)a[i] * inv) % P;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 0; i < n; i ++ ) 
    {
        a[i] = read();
        A[i] = A[i + n] = a[i];
        a1 += a[i] * a[i];
        a2 += a[i];
    }

    for(int i = 0; i < n; i ++ ) 
    {
        b[i] = read();
        B[n - i - 1] = b[i];
        b1 += b[i] * b[i];
        b2 += b[i];
    }
    
    while(lim <= n + n + n) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    NTT(A, 1), NTT(B, 1);
    for(int i = 0; i < lim; i ++ ) A[i] = (ll)A[i] * B[i] % P;

    NTT(A, -1);
    
    for(int i = 0; i < n; i ++ )
        for(int j = -m; j <= m; j ++ )
        {
            ans = min(ans, a1 + b1 + (ll)n * j * j + 2ll * j * (a2 - b2) - 2 * A[i + n]);
        }

    cout << ans << endl;
    
    return 0;
}
