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

const int N = 1e6 + 10, M = 1010;
ll a[N];
ll f[M][M];
int n, m, sqrtn;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    sqrtn = sqrt(n);
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= sqrtn; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            f[i][j % i] += a[j];
        }
    }

    while(m -- )
    {
        char op[10];
        scanf("%s", op);
        int x = read(), y = read();
        if(op[0] == 'A')
        {
            if(x <= sqrtn) printf("%lld\n", f[x][y]);
            else
            {
                ll res = 0;
                for(int i = y; i <= n; i += x)
                    res += a[i];
                printf("%lld\n", res);
            }
        }
        else
        {
            for(int i = 1; i <= sqrtn; i ++ )
            {
                f[i][x % i] -= a[x];
                f[i][x % i] += y;
            }
            a[x] = y;
        }
    }

    return 0;
}