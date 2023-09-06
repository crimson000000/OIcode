#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 1010, mod = 1e9 + 7;

ll qmi(ll a, ll k, ll p)
{
    a %= p;
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

ll inv(ll a)
{
    return qmi(a, mod - 2, mod);
}

struct mat
{
    ll t[N][N];
    ll n, m;

    ll * operator [] (int x) 
    {
        return t[x];
    }

    bool gauss()
    {
        for(int i = 1; i <= n; i ++ )
        {
            int pos = i;
            for(int j = i; j <= n; j ++ )
                if(abs(t[j][i]) > abs(t[pos][i]))
                    pos = j;
            
            if(t[pos][i] == 0) return false;
            for(int j = 1; j <= m; j ++ )
                swap(t[pos][j], t[i][j]);

            for(int j = 1; j <= n; j ++ )
                if(j != i)
                {
                    ll tmp = t[j][i] * inv(t[i][i]) % mod;
                    for(int k = 1; k <= m; k ++ )
                        t[j][k] = (t[j][k] - tmp * t[i][k] + mod) % mod;
                }
        }

        for(int i = 1; i <= n; i ++ )
        {
            ll tmp = inv(t[i][i]);
            for(int j = 1; j <= m; j ++ )
                t[i][j] = (t[i][j] * tmp % mod + mod) % mod;
        }
        return true;
    }
}a;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            a[i][j] = read();
    
    for(int i = 1; i <= n; i ++ ) a[i][i + n] = 1;
    a.n = n, a.m = n + n;

    if(a.gauss())
    {
        for(int i = 1; i <= n; i ++ )
        {
            for(int j = n + 1; j <= 2 * n; j ++ )
                cout << a[i][j] << ' ';
            puts("");
        }
    }
    else
    {
        puts("No Solution");
    }
    
    return 0;
}
