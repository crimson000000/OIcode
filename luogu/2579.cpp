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

const int N = 60, mod = 10000;

struct mat
{
    ll z[N][N];
    int n, m;

    ll * operator [] (int x)
    {
        return z[x];
    }

    void init()
    {
        memset(z, 0, sizeof z);
    }

    mat operator * (const mat& M) const
    {
        mat temp;
        temp.init();
        temp.n = n, temp.m = M.m;
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= M.m; k ++ )
                for(int j = 1; j <= m; j ++ )
                    temp[i][j] = (temp[i][j] + z[i][k] * M.z[k][j] % mod) % mod;
        return temp;
    }

    void print()
    {
        for(int i = 0; i <= n; i ++ )
        {
            for(int j = 0; j <= m; j ++ )
                cout << z[i][j] << ' ';
            puts("");
        }
    }
}a[15], sum;
int p[N];

int n, m, st, ed, k, nffish;

mat qmi(mat a, ll k)
{
    mat res;
    res.init();
    res.n = res.m = a.n;
    for(int i = 1; i <= n; i ++ ) res[i][i] = 1;
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

    n = read(), m = read(), st = read(), ed = read(), k = read();
    a[1].n = a[1].m = n;
    for(int i = 1; i <= m; i ++ )
    {
        int u = read() + 1, v = read() + 1;
        a[1][u][v] = a[1][v][u] = 1;
    }

    for(int i = 2; i <= 12; i ++ ) a[i] = a[1];

    nffish = read();
    while(nffish -- )
    {
        int T = read();
        for(int j = 1; j <= T; j ++ ) p[j] = read() + 1;
        p[0] = p[T];
        for(int j = 1; j <= 12; j ++ )
        {
            for(int u = 1; u <= n; u ++ )
                a[j][u][p[j % T + 1]] = 0;
        }
    }

    // for(int i = 1; i <= 12; i ++ )
    // {
    //     cout << i << ':' << endl;
    //     a[i].print();
    //     puts("");
    // }

    for(int i = 1; i <= n; i ++ ) sum[i][i] = 1;
    sum.m = sum.n = n;
    for(int i = 1; i <= 12; i ++ )
    {
        sum = sum * a[i];
    }
    // sum.print();
    // puts("");

    mat ans = qmi(sum, k / 12);

    // ans.print();
    
    for(int i = 1; i <= k - (k / 12) * 12; i ++ )
    {
        ans = ans * a[i];
    }

    // ans.print();

    cout << ans[st + 1][ed + 1] << endl;

    return 0;
}
