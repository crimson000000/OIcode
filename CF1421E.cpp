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

const int N = 2e5 + 10;
ll f[N][4][2][2];
ll a[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    if(n == 1)
    {
        cout << a[1] << endl;
        return 0;
    } 
    
    memset(f, -0x3f, sizeof f);

    f[1][1][1][0] = a[1], f[1][2][0][0] = -a[1];

    for(int i = 1; i < n; i ++ )
        for(int j = 0; j < 3; j ++ )
            for(int k = 0; k < 2; k ++ )
                for(int u = 0; u < 2; u ++ )
                {
                    f[i + 1][(j + 2) % 3][0][u | (k == 0)] = max(f[i + 1][(j + 2) % 3][0][u | (k == 0)], f[i][j][k][u] - a[i + 1]);
                    f[i + 1][(j + 1) % 3][1][u | (k == 1)] = max(f[i + 1][(j + 1) % 3][1][u | (k == 1)], f[i][j][k][u] + a[i + 1]);
                }

    cout << max(f[n][1][0][1], f[n][1][1][1]) << endl;

    return 0;
}
