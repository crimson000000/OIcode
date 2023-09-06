#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 160, mod = 998244353;
ll f[N][1300000], s[1300000];
int maxn = 280000;
int k;

inline void init(int n)
{
    f[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        memcpy(s, f[i - 1], sizeof s);
        for(int j = i; j <= maxn; j ++ )
            s[j] = (s[j] + s[j - i]) % mod;
        for(int j = 0; j <= maxn; j ++ )
            if(j >= (k + 1) * i)
                f[i][j] = (s[j] - s[j - (k + 1) * i] + mod) % mod;
            else f[i][j] = s[j]; 
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    k = read();
    init(150);

    // cout << f[2][4] << endl; 

    int q = read();
    while(q -- )
    {
        int n = read(), x = read();
        ll res = 0;

        for(int i = 0; i <= maxn; i ++ )
            res = (res + f[x - 1][i] * f[n - x][i] % mod) % mod;
        
        res = res * (k + 1) % mod;
        printf("%lld\n", (res - 1 + mod) % mod);
    }

    return 0;
} 