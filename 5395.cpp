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

const int N = 2e6 + 10, P = 167772161, G = 3, Gi = 55924054;
int a[N], b[N], c[N];
int rev[N];
int n;
int lim = 1, len;

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

int primes[N], cnt;
bool st[N];
int mi[N], fact[N];

void init()
{
    mi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            mi[i] = qmi(i, n, P);
            primes[++ cnt] = i;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            mi[primes[j] * i] = (ll)mi[primes[j]] * mi[i] % P;
            if(i % primes[j] == 0) break;
        }
    }
    fact[0] = 1;
    for(int i = 1; i <= n + 2; i ++ ) fact[i] = (ll)fact[i - 1] * i % P;
}

int inv(int a)
{
    return qmi(a, P - 2, P);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    init();

    for(int i = 0; i <= n; i ++ ) 
    {
        a[i] = (ll)mi[i] * inv(fact[i]) % P;
        b[i] = (ll)qmi(-1, i, P) * inv(fact[i]) % P;
    }

    while(lim <= (n + 1) * 2) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    
    NTT(a, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ ) a[i] = (ll)a[i] * b[i] % P;
    NTT(a, -1);

    for(int i = 0; i <= n; i ++ ) cout << a[i] << ' ';

    return 0;
}