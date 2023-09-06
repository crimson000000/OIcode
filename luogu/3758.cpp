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

const int mod = 2017;
struct mat
{
    int m[35][35];
    int a, b;

    mat operator * (const mat& M) const
    {
        mat temp;
        temp.a = a, temp.b = M.b;
        memset(temp.m, 0, sizeof temp.m);
        for(int i = 0; i <= a; i ++ )
            for(int j = 0; j <= M.b; j ++ )
                for(int k = 0; k <= b; k ++ )
                    temp.m[i][j] = (temp.m[i][j] + m[i][k] * M.m[k][j] % mod) % mod;
        return temp;
    }

    void print()
    {
        for(int i = 0; i <= a; i ++ )
        {
            for(int j = 0; j <= b; j ++ )
                cout << m[i][j] << ' ';
            puts("");
        }
    }
}mp;

int t, n, m;

mat qmi(mat a, int k)
{
    mat res;
    res.a = a.a, res.b = a.b;
    memset(res.m, 0, sizeof res.m);
    for(int i = 0; i <= n; i ++ ) res.m[i][i] = 1;

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

    n = read(), m = read();
    mp.a = mp.b = n;
    for(int i = 0; i <= n; i ++ ) 
    {
        mp.m[i][0] = 1;
        mp.m[i][i] = 1;
    }

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        mp.m[a][b] = mp.m[b][a] = 1;
    }

    t = read();

    mp = qmi(mp, t);

    ll res = 0;
    for(int i = 0; i <= n; i ++ ) res = (res + mp.m[1][i]) % mod;

    cout << res << endl;
    
    return 0;
}
