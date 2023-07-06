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

const int N = 1010, M = 210, mod = 1000000007;
int f[2][2][M][M];
char a[N], b[N];
int n, m, k, s;
int now, pre = 1;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    cin >> a + 1 >> b + 1;

    for(int i = 1; i <= n; i ++ )
    {
        swap(now, pre);
        f[0][now][1][1] = s;
        if(a[i] == b[1]) s ++, f[1][now][1][1] = 1;
        for(int j = 2; j <= m; j ++ )
            for(int k1 = 1; k1 <= k; k1 ++ )
            {
                if(a[i] == b[j])
                {
                    f[1][now][j][k1] = ((f[0][pre][j - 1][k1 - 1] + f[1][pre][j - 1][k1]) % mod + f[1][pre][j - 1][k1 - 1]) % mod;
                }
                f[0][now][j][k1] = (f[1][pre][j][k1] + f[0][pre][j][k1]) % mod;
            }
        
        memset(f[1][pre], 0, sizeof f[1][pre]);
        memset(f[0][pre], 0, sizeof f[0][pre]);
    }

    cout << (f[0][now][m][k] + f[1][now][m][k]) % mod << endl;
   
    
    return 0;
}
