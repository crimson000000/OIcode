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

const int N = 1e6 + 10, mod = 1e9 + 7;
ll fact[N], invfact[N];
struct blo
{
    int x, y;
    bool operator < (const blo& a) const
    {
        if(x == a.x) return y < a.y;
        return x < a.x;
    }
}q[N];
ll f[N];
ll n, m, k;

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

void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}  

inline ll C(ll n, ll m)
{
    if(m > n || n < 0 || m < 0) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 5);
    n = read(), m = read(), k = read();

    for(int i = 1; i <= k; i ++ )
    {
        int x = read(), y = read();
        q[i] = {x, y};
    }

    k ++;
    q[k] = {n, m};

    sort(q + 1, q + k + 1);

    for(int i = 1; i <= k; i ++ )
    {
        f[i] = C(q[i].x + q[i].y - 2, q[i].x - 1);
        for(int j = 1; j < i; j ++ )
            f[i] = (f[i] - f[j] * C(q[i].x - q[j].x + q[i].y - q[j].y, q[i].x - q[j].x) % mod + mod) % mod;
    }

    cout << f[k] << endl;

    return 0;
}