#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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

const int N = 20 + 10, mod = 1e9 + 1;
int a[N][N];
bitset<1000000> vis;
int n;
ll ans;

namespace solve
{
    int m;
    int line[N];
    ll f[N][1 << 18];
    vector<int> v;

    inline bool check(int s)
    {
        if(s & (s << 1)) return false;
        return true;
    }

    inline bool check(int s1, int s2)
    {
        if(s1 & s2) return false;
        return true;
    }

    inline void init()
    {
        for(int i = 0; i < (1 << 18); i ++ )
            if(check(i))
                v.emplace_back(i);
    }

    inline ll work()
    {
        for(auto i : v)
        {
            if(i >= (1ll << line[1])) break;
            if(check(i))
                f[1][i] = 1;
        }

        for(int i = 2; i <= m; i ++ )
            for(auto j : v)
            {
                f[i][j] = 0; 
                if(j >= (1ll << line[i])) break;
                if(!check(j)) continue;
                for(auto k : v)
                {
                    if(k >= (1ll << line[i - 1])) break;
                    if(!check(j, k)) continue;
                    f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                }
            }

        ll res = 0;
        for(int i = 0; i < (1 << line[m]); i ++ )
            res = (res + f[m][i]) % mod;
        
        return res;
    }
}

inline void init(int x)
{
    solve::m = 0;
    memset(solve::line, 0, sizeof solve::line);
    for(int i = 1, p = 1; p * x <= n; i ++, p *= 3) 
    {
        a[i][1] = p * x; 
        solve::m ++;
    }

    for(int i = 1; i <= solve::m; i ++ )
    {
        for(int j = 0; a[i][1] * (1ll << j) <= n; j ++ )
        {
            solve::line[i] ++;
            a[i][j + 1] = a[i][1] * (1ll << j);
        }
    }

    for(int i = 1; i <= solve::m; i ++ )
    {
        for(int j = 1; j <= solve::line[i]; j ++ )
        {
            // cout << a[i][j] << ' ';
            vis[a[i][j]] = true;
        }
        // puts("");
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    solve::init();

    ans = 1;
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            init(i);
            ans = ans * solve::work() % mod;
        }

    cout << ans << endl;

    return 0;
}