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

const int N = 1e5 + 10;
int n, m, B;
int a[N];
int f[N][405];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    B = sqrt(n);

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 0; i <= B; i ++ )
    {
        for(int j = n; j; j -- )
        {
            if(j + a[j] + i > n) f[j][i] = 1;
            else f[j][i] = f[j + a[j] + i][i] + 1;
        }
    }

    m = read();
    while(m -- )
    {
        int p = read(), k = read();
        if(k <= B) printf("%d\n", f[p][k]);
        else
        {
            int cnt = 0;
            while(p <= n)
            {
                p = p + a[p] + k;
                cnt ++;
            }
            printf("%d\n", cnt);
        }
    }

    return 0;
}