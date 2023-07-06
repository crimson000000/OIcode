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

const int N = 110, mod = 1e6 + 7;
int n, m;
int a[N];
int f[N][N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    f[0][0] = 1;

    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j <= m; j ++ )
            for(int k = 0; k <= min(a[i], j); k ++ )
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;
            
    cout << f[n][m] << endl;
    
    return 0;
}
