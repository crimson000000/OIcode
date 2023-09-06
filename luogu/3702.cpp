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

const int mod = 20170408, N = 1e7 + 10;
struct mat
{
    ll a[150][150];
    int n, m;

    ll * operator [] (int x)
    {
        return a[x];
    }

    void init()
    {
        memset(a, 0, sizeof a);
    }

    mat operator * (const mat& M) const
    {
        mat tmp;
        tmp.init();
        tmp.n = n, tmp.m = M.m;
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= M.m; k ++ )
                for(int j = 1; j <= m; j ++ )
                    tmp[i][j] = (tmp[i][j] + a[i][k] * M.a[k][j] % mod) % mod;
        return tmp;
    }

    // void print()
    // {
    //     for(int i = 1; i <= n; i ++ )
    //     {
    //         for(int j = 1; j <= m; j ++ )
    //             cout << a[i][j] << ' ';
    //         puts("");
    //     }
    // }
}base1, base2, F, G;

ll n, m, p;
int primes[N], cntt;
bool st[N];
ll cnt[N], cop[N];

void init(int n)
{
    st[1] = true;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cntt] = i;
        }
        for(int j = 1; primes[j] <= n / i && j <= cntt; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

mat qmi(mat a, ll k)
{
    mat res;
    res.init();
    res.n = res.m = a.n;
    for(int i = 1; i <= res.n; i ++ ) res[i][i] = 1;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), p = read();
    if(p == 0 || m == 0) 
    {
        cout << 0 << endl;
        return 0;
    }
    init(m + 1);

    for(int i = 0; i < p; i++) cnt[i] = m / p;
	for(int i = 1; i <= m % p; i++) cnt[i]++;

    base1.n = base1.m = base2.n = base2.m = p;
    F.n = G.n = 1, F.m = G.m = p;
    
    for(int i = 1; i <= m; i ++ )
    {
        if(st[i]) cop[i % p] ++;
    } 

    for(int i = 1; i <= p; i ++ )
    {
        F[1][i] = cnt[i - 1] % mod, G[1][i] = cop[i - 1] % mod;
        for(int j = 1; j <= p; j ++ )
        {
            base1[i][j] = cnt[(j - i + p) % p] % mod;
            base2[i][j] = cop[(j - i + p) % p] % mod;
        }
    }

    // for(int i = 0; i < p; i ++ ) cout << cnt[i] << ' ';
    // puts("");
    // for(int i = 0; i < p; i ++ ) cout << cop[i] << ' ';
    // puts("");
    // F.print(), G.print();

    F = F * qmi(base1, n - 1);
    G = G * qmi(base2, n - 1);
    // F.print();
    // G.print();
    
    cout << (long long)(((F[1][1] - G[1][1]) % mod + mod) % mod);
    
    return 0;
}

