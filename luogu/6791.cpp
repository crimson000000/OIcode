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

const int N = 110;
ll f[N], dp[N];
bitset<N> v;
ll k, n;

inline ll dfs(int p, bool bound, bool lst)
{
    if(p < k) return 1;
    if(!lst && !bound && dp[p] != -1) return dp[p];
    ll r = dfs(p - 1, bound & (v[p] == 0), 0);
    if(!lst && (!bound || v[p] == 1))
        r += dfs(p - 1, bound, 1);
    if(!lst && !bound) dp[p] = r;
    return r;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    f[0] = 1, f[1] = 1;
    for(int i = 2; i <= 90; i ++ ) f[i] = f[i - 1] + f[i - 2];

    while(T -- )
    {
        v.reset();
        memset(dp, -1, sizeof dp);

        k = read(), n = read();
        n --;

        ll tn = n;
        for(int i = 90; i; i -- )
            if(tn >= f[i])
                tn -= f[i], v[i] = 1;
        
        ll tk = k;
        for(int i = 90; i; i -- )
            if(f[i] > tk)
                k = i;
        
        printf("%lld\n", n - dfs(90, 1, 0) + 1);
    }

    return 0;
}
