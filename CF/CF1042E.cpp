#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1010, mod = 998244353;
ll a[N][N], f[N][N];
vector<PII> pos[N * N];
vector<ll> nums;
ll sumx, sumx2, sumy, sumy2, sumf;
ll cnt;
int n, m;
int stx, sty;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
        {
            a[i][j] = read();
            nums.push_back(a[i][j]);
        }
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            a[i][j] = lower_bound(nums.begin(), nums.end(), a[i][j]) - nums.begin();
            pos[a[i][j]].emplace_back(i, j);
        }

    for(int i = 0; i < (int)nums.size(); i ++ )
    {
        for(auto t : pos[i])
        {
            int x = t.first, y = t.second;
            f[x][y] = (cnt * x % mod * x % mod - 2ll * x % mod * sumx % mod + sumx2 + mod) % mod
                    + (cnt * y % mod * y % mod - 2ll * y % mod * sumy % mod + sumy2 + mod) % mod
                    + sumf;
            
            f[x][y] = f[x][y] * qmi(cnt, mod - 2, mod) % mod; 
        }

        for(auto t : pos[i])
        {
            int x = t.first, y = t.second;
            sumx = (sumx + x) % mod;
            sumy = (sumy + y) % mod;
            sumx2 = (sumx2 + x * x) % mod;
            sumy2 = (sumy2 + y * y) % mod;
            sumf = (sumf + f[x][y]) % mod;
        }

        cnt += pos[i].size();
    }

    stx = read(), sty = read();

    cout << f[stx][sty] << endl;

    return 0;
}