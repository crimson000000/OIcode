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

const int N = 3010, mod = 1e9 + 7;
ll f[N][N];
int n, m;

inline ll add(ll a, ll b)
{
    ll res = a + b;
    while(res >= mod) res -= mod;
    return res;
}

inline ll solve(int n)
{
    memset(f, 0, sizeof f);
    for(int i = 0; i <= n; i ++ ) f[0][i] = 1;
    for(int i = 1; i <= m; i ++ )
        for(int j = 0; j <= n; j ++ )
        {
            if(j > 0) 
            {
                f[i][j] = add(f[i][j], f[i - 1][j - 1]);
                f[i][j] = add(f[i][j], f[i - 1][j]);
            }
            if(j < n) 
            {
                f[i][j] = add(f[i][j], f[i - 1][j + 1]); 
                f[i][j] = add(f[i][j], f[i - 1][j]);
            }
        }

    ll ans = 0;
    for(int i = 0; i <= n; i ++ ) ans = add(ans, f[m][i]);
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    cout << (solve(n) - solve(n - 1) + mod) % mod << endl;

    return 0;
}
