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

const int N = 510, mod = 998244353;
ll a[N][N], b[N][N], tmp[N][N];
int num[N], ed[N];
int n, m, k;

inline void mul(int n, int m, int l)
{
    memset(tmp, 0, sizeof tmp);
    for(int i = 1; i <= n; i ++ )
        for(int k = 1; k <= m; k ++ )
            for(int j = 1; j <= l; j ++ )
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j] % mod) % mod;
    memset(a, 0, sizeof a);
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= l; j ++ )
            a[i][j] = tmp[i][j];
    memset(b, 0, sizeof b);
}

inline ll calc(int n)
{
    ll res = 1, w = 1;
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = i + 1; j <= n; j ++ )
        {
            while(a[i][i])
            {
                ll div = a[j][i] / a[i][i];
                for(int k = i; k <= n; k ++ )
                    a[j][k] = (a[j][k] - div * a[i][k] % mod + mod) % mod;
                swap(a[i], a[j]);
                w = -w;
                // cout << "yeah" << endl;
            }
            swap(a[i], a[j]);
            w = -w;
        }
    }
    for(int i = 1; i <= n; i ++ ) res = res * a[i][i] % mod;
    res = res * w;
    return (res % mod + mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        memset(num, 0, sizeof num);
        memset(ed, 0, sizeof ed);

        k = read();
        
        for(int i = 1; i <= k; i ++ ) num[i] = read();
        for(int i = 1; i < k; i ++ ) ed[i] = read();

        m = ed[1], n = num[1];
        while(m -- )
        {
            int x = read(), y = read();
            a[x][y] = 1;
        } 
        
        for(int i = 2; i < k; i ++ )
        {
            m = ed[i];
            while(m -- )
            {
                int x = read(), y = read();
                b[x][y] = 1;
            }
            mul(n, num[i], num[i + 1]);
        }

        // cout << "yeah" << endl;
        cout << calc(n) << endl;
    }

    return 0;
}