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

const int N = 1e6 + 10, M = 510, mod = 999911659;
ll f[M][15][M];
ll cnt[M];
int first[N], cycle[N];
ll n, p;
ll cycst, cyclen;

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

ll C(ll n, ll m)
{
    if(m < 0) return 0;
    ll down = 1, up = 1;
    for(ll i = n - m + 1; i <= n; i ++ )
        up = up * i % mod;
    for(int i = 1; i <= m; i ++ )
        down = down * i % mod;
    return up * qmi(down, mod - 2, mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(first, -1, sizeof first);

    n = read(), p = read();

    cycle[0] = 1 % p;
    first[1 % p] = 0;
    ll addition = 0;
    for(int i = 1; ; i ++ )
    {
        cycle[i] = (cycle[i - 1] * 10 % p + 1) % p;
        if(first[cycle[i]] != -1)
        {
            for(int j = 0; j < i && j < n; j ++ )
                cnt[cycle[j]] = (cnt[cycle[j]] + 1) % mod, addition = cycle[j];
            n -= i;
            cycst = cycle[i];
            cyclen = i - first[cycle[i]];
            break;
        }
        first[cycle[i]] = i;
    }

    n = max(n, 0ll);
    ll times = n / cyclen;
    for(int i = 0; i < cyclen; i ++ )
        cnt[cycle[i + first[cycst]]] = (cnt[cycle[i + first[cycst]]] + times) % mod;
    ll nn = n % cyclen;
    for(int i = 0; i < nn; i ++ )
        cnt[cycle[i + first[cycst]]] ++, addition = cycle[i + first[cycst]];

    f[p + 1][0][addition] = 1;
    for(int i = 0; i < p; i ++ )
        for(int j = 0; j < 9; j ++ )
            for(int s = 0; s + j < 9; s ++ )
            {
                ll multi = C(cnt[i] + s - 1, s);
                for(int d = 0; d < p; d ++ )
                    f[p - i][s + j][(d + s * i) % p] = (f[p - i][s + j][(d + s * i) % p] + 
                                                        multi * f[p - i + 1][j][d]) % mod;
            }

    ll ans = 0;
    for(int i = 0; i < 9; i ++ )
        ans = (ans + f[1][i][0]) % mod;
    
    cout << ans << endl;

    return 0;
}