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

const int N = 310;
ll C[N][N];
ll f[N][N];
ll n, m, mod, sum[N];

inline void init(int n)
{
    C[0][0] = 1, C[1][0] = C[1][1] = 1;
    for(int i = 2; i <= n; i ++ )
        for(int j = 0; j <= i; j ++ )
        {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
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
        memset(f, 0, sizeof f);
        memset(sum, 0, sizeof sum);
        n = read(), m = read(), mod = read();
        init(n);

        for(int i = 1; i <= m; i ++ )
        {
            int x = read(), a = read();
            sum[a] ++;
        }

        bool flag = false;
        for(int i = n; i; i -- )
        {
            sum[i] += sum[i + 1];
            if(sum[i] > n - i + 1)
            {
                flag = true;
                break;
            }
        }

        if(flag)
        {
            puts("NO");
            continue;
        }

        f[n + 1][0] = 1;
        for(int i = n; i; i -- )
            for(int j = 0; j <= n - sum[i] - i + 1; j ++ )
                for(int k = 0; k <= j; k ++ )
                    f[i][j] = (f[i][j] + f[i + 1][j - k] * C[j][k] % mod) % mod;
        
        printf("YES %lld\n", f[1][n - m]);
    }

    return 0;
}