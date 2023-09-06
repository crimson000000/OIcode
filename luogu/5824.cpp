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

const int N = 2e6 + 10, P = 998244353, G = 3, Gi = 332748118;
int n, m;
ll fact[N], invfact[N];
int primes[N], cnt;
bool st[N];
ll mi[N];
ll invv[N];
int rev[N], A[N], B[N], S[N];
int lim = 1, len;

inline int qmi(int a, int k, int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll)res * a % p;
        a = (ll)a * a % p;
        k >>= 1;
    }
    return res;
}

inline void init()
{
    mi[1] = 1;
    for(int i = 2; i <= N - 5; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            mi[i] = qmi(i, n, P);
        }
        for(int j = 1; primes[j] <= (N - 5) / i; j ++ )
        {
            st[primes[j] * i] = true;
            mi[primes[j] * i] = (ll)mi[primes[j]] * mi[i] % P;
            if(i % primes[j] == 0) break;
        }
    }
    invv[1] = 1;
    for(int i = 2; i < N - 5; i ++ ) 
        invv[i] = (ll)(P - P / i) * invv[P % i] % P;
}

inline void NTT(int a[], int opt)
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
                a[j + k] = ((ll)t + u) % P;
                a[j + k + m / 2] = ((ll)u - t + P) % P;
                g = (ll)g * gn % P; 
            }
        }
    }
    if(opt == -1)
    {
        ll inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ ) a[i] = (ll)a[i] * inv % P;
    }
}

inline void NTT(int a[], int lim, int opt)
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
                a[j + k] = ((ll)t + u) % P;
                a[j + k + m / 2] = ((ll)u - t + P) % P;
                g = (ll)g * gn % P; 
            }
        }
    }
    if(opt == -1)
    {
        ll inv = qmi(lim, P - 2, P);
        for(int i = 0; i < lim; i ++ ) a[i] = (ll)a[i] * inv % P;
    }
}


inline ll C(int n, int m)
{
    if(m > n) return 0;
    return (ll)fact[n] * invfact[m] % P * invfact[n - m] % P;
}

inline void strlin()
{
    for(int i = 0; i <= n; i ++ ) 
    {
        A[i] = (ll)mi[i] * invfact[i] % P;
        B[i] = (qmi(-1, i, P) * (ll)invfact[i] + P) % P;
    }

    while(lim <= (n + 1) * 2) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    
    NTT(A, 1), NTT(B, 1);
    for(int i = 0; i < lim; i ++ ) S[i] = (ll)A[i] * B[i] % P;
    NTT(S, -1); 
}

inline void calc(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

int X[N], Y[N];
inline void mul(int a[], int b[], int to[], int n, int m)
{
    int lim = 1, len = 0;
    while(lim <= (n + m)) lim <<= 1, len ++;
    calc(lim, len);
    for(int i = (lim >> 1); i <= lim; i ++ ) X[i] = Y[i] = 0;
    for(int i = 0; i < (lim >> 1); i ++ )
        X[i] = a[i] % P, Y[i] = b[i] % P;
    NTT(X, lim, 1), NTT(Y, lim, 1);
    for(int i = 0; i < lim; i ++ ) 
        to[i] = (ll)X[i] * Y[i] % P;
    NTT(to, lim, -1);
}

inline void mul(int a[], int b[], int to[], int lim)
{
    for(int i = (lim >> 1); i <= lim; i ++ ) X[i] = Y[i] = 0;
    for(int i = 0; i < (lim >> 1); i ++ )
        X[i] = a[i] % P, Y[i] = b[i] % P;
    NTT(X, lim, 1), NTT(Y, lim, 1);
    for(int i = 0; i < lim; i ++ ) 
        to[i] = (ll)X[i] * Y[i] % P;
    NTT(to, lim, -1);
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

inline void derivative(int a[], int to[], int n)
{
    for(int i = 0; i < n - 1; i ++ )
        to[i] = (ll)(i + 1) * a[i + 1] % P;
    to[n - 1] = 0;
}

inline void integ(int a[], int to[], int n)
{
    for(int i = 1; i <= n; i ++ )
        to[i] = (ll)qmi(i, P - 2, P) * (ll)a[i - 1] % P;
    to[0] = 0;
}

int d[N], in[N], LN[N], inte[N];
inline void ln(int a[], int to[], int n)
{
    inv(a, in, n);
    derivative(a, d, n);
    mul(d, in, inte, n, n);
    integ(inte, to, n);
}

int c[N], E[N];
inline void exp(int a[], int b[], ll n)
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

int LNN[N], F[N];

inline ll solve1()
{
    return qmi(m, n, P);
}

inline ll solve2()
{
    if(n > m) return 0;
    return (ll)fact[m] * invfact[m - n] % P;
}

inline ll solve3()
{
    if(n < m) return 0;
    ll res = 0;
    for(int i = 0; i <= m; i ++ )
        if((m - i) & 1) res = ((ll)res - C(m, i) % P * mi[i] % P + P) % P;
        else res = ((ll)res + C(m, i) % P * mi[i] % P) % P;

    return res % P;
}

inline ll solve4()
{
    strlin();
    ll ans = 0;
    for(int i = 0; i <= min(m, n); i ++ ) ans = (ans + S[i]) % P;
    return ans;
}

inline ll solve5()
{
    if(n > m) return 0;
    return 1;
}

inline ll solve6()
{
    if(n < m) return 0;
    return S[m];
}

inline ll solve7()
{
    return C(n + m - 1, m - 1);
}

inline ll solve8()
{
    return C(m, n);
}

inline ll solve9()
{
    if(m > n) return 0;
    return C(n - 1, m - 1);
}

inline ll solve10()
{
    for(int i = 0; i <= n; i ++ ) LNN[i] = F[i] = 0;
    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 1; j <= n / i; j ++ )
            LNN[i * j] = ((ll)LNN[i * j] + invv[j]) % P;
    }
    exp(LNN, F, n + 1);
    return F[n];
}

inline ll solve11()
{
    if(n > m) return 0;
    return 1;
}

inline ll solve12()
{
    if(n < m) return 0;
    return F[n - m];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    double st = clock();

    n = read(), m = read();
    init();
    fact[0] = 1;
    for(int i = 1; i <= n + m; i ++ ) fact[i] = (ll)fact[i - 1] * i % P;
    invfact[n + m] = qmi(fact[n + m], P - 2, P);
    for(int i = n + m; i; i -- )
        invfact[i - 1] = (ll)invfact[i] * i % P;

    cout << solve1() << endl;
    cout << solve2() << endl;
    cout << solve3() << endl;
    cout << solve4() << endl;
    cout << solve5() << endl;
    cout << solve6() << endl;
    cout << solve7() << endl;
    cout << solve8() << endl;
    cout << solve9() << endl;
    cout << solve10() << endl;
    cout << solve11() << endl;
    cout << solve12() << endl;

    // printf("%.3f\n", (clock() - st) / CLOCKS_PER_SEC);

    return 0;
}
