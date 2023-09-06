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

const int N = 110;
namespace D {long double f[2][N][10010][3];}
namespace F {__float128 f[2][N][10010][3];}
int n, m, k;

template <class T>
inline void write(T x)
{
    if(x + 1e-14 >= 1) 
    {
        printf("1.");
        for(int i = 1; i <= k; i ++ )
            putchar('0');
        return;
    }

    x *= 10;

    cout << "0.";
    for(int i = 1; i <= k; i ++ )
    {
        cout << (int)(x + (k == i) * 0.5);
        x = (x - (int)x) * 10;
    }
}

template <class T>
inline void DP(T f[][N][10010][3])
{
    int now = 0, lst = 1;
    f[now][0][5000][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        swap(now, lst);
        memset(f[now], 0, sizeof f[now]);
        for(int j = 0; j <= n; j ++ )
            for(int k = 0; k <= 10000; k ++ )
                for(int u = 0; u < 3; u ++ )
                    if(f[lst][j][k][u])
                    {
                        if(k >= i && u < 2)
                            f[now][j + 1][k - i][u + 1] += (2 - u) * f[lst][j][k][u] / i;
                        if(j && k + i <= 10000 && u < 2)
                            f[now][j][k + i][u + 1] += (2 - u) * f[lst][j][k][u] / i;
                        if(j >= 2 && k + 2 * i <= 10000)
                            f[now][j - 1][k + 2 * i][u] += (j - 1) * f[lst][j][k][u] / i;
                        if(k >= 2 * i)
                            f[now][j + 1][k - 2 * i][u] += (j + 1 - u) * f[lst][j][k][u] / i;
                        if(j >= 1)
                            f[now][j][k][u] += (j * 2 - u) * f[lst][j][k][u] / i;
                    }
    }           

    T ans = 0;
    for(int i = m; i <= 5000; i ++ )
        ans += f[now][1][i + 5000][2];
    
    write(ans);
} 

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    
    if(k <= 8) DP(D::f);
    else DP(F::f);

    return 0;
}