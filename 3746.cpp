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

const int N = 60;
ll n, mod, k, r;
struct mat
{
    ll a[N][N];
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

    void print()
    {
        for(int i = 1; i <= n; i ++ )
        {
            for(int j = 1; j <= m; j ++ )
                cout << a[i][j] << ' ';
            puts("");
        }
    }
}ans, base;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read(), k = read(), r = read();

    ans.n = 1, ans.m = k;
    ans[1][1] = 1;
    base[k][1] ++;
    for(int i = 1; i <= k; i ++ )
    {
        base[i][i] ++;
        base[i - 1][i] ++;
    }

    base.m = base.n = k;
    // base.print();
    // ans.print();

    ans = ans * qmi(base, n * k);
    // ans.print();
    cout << ans[1][r + 1] << endl;

    return 0;
}
