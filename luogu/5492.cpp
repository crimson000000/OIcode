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

const int N = 25, S = 1 << 20, mod = 998244353;
ll f[S], e[N];
ll siz[S];
int n, m;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        siz[1 << (i - 1)] = 1;
        e[i] |= 1 << (i - 1);
    }

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        e[a] |= 1 << (b - 1);
        e[b] |= 1 << (a - 1);
    }

    for(int i = 1; i < (1 << n); i ++ )
        for(int j = 1; j <= n; j ++ )
            if(i >> (j - 1) & 1)
            {
                int T = i & (~e[j]);
                siz[i] = max(siz[i], siz[T] + 1);
            }

    f[0] = 1;
    for(int i = 1; i < (1 << n); i ++ )
    {
        int cnt = 0;
        for(int j = 1; j <= n; j ++ )
        {
            if(i >> (j - 1) & 1)
            {
                cnt ++;
                int T = i & (~e[j]);
                if(siz[i] == siz[T] + 1)
                    f[i] = (f[i] + f[T]) % mod;
            }
        }
        f[i] = f[i] * qmi(cnt, mod - 2, mod) % mod;
    }

    cout << f[(1 << n) - 1] << endl;

    return 0;
}