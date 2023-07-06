#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define int __int128
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

inline void write(int x)
{
    if(x < 0) 
    {
        putchar('-');
        x = -x;
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 110, mod = 9223372036854775783;
struct mat
{
    int a[N][N];
    int n, m;

    int * operator [] (int x)
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
                {
                    tmp[i][j] = ((tmp[i][j] % mod + mod) % mod + (a[i][k] + mod) % mod * (M.a[k][j] + mod) % mod) % mod;
                }
        return tmp;
    }
}base, a;

int phi = mod - 1;
bool flag;

mat qmi(mat a, int k)
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

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int b = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        b = b * 10 + ch - '0';
        if(b >= phi) 
        {
            b %= phi;
            flag = true;
        }
        ch = getchar();
    }
    b *= f;

    b --;
    if(b < 0) b = phi;
    if(flag) b += phi;

    a[1][1] = 1, a[1][2] = 0, a[1][3] = 2, a[1][4] = 1;
    a.n = 1, a.m = 4;
    base[1][1] = 2, base[1][2] = 1;
    base[2][1] = 2, base[2][2] = 2;
    base[3][1] = 3, base[3][2] = 1, base[3][3] = 2;
    base[4][1] = -2, base[4][2] = -1, base[4][4] = 1;
    base.n = base.m = 4;

    a = a * qmi(base, b);
    cout << (long long)a[1][1] << endl;

    return 0;
}
