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

const int N = 1e5 + 10, M = 1 << 20;
int f[M], a[N], sum[25][N], s[25], l[M];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        s[a[i]] ++;
        for(int j = 1; j <= m; j ++ )
        {
            if(a[i] == j) sum[j][i] = sum[j][i - 1] + 1;
            else sum[j][i] = sum[j][i - 1];
        }
    }

    for(int i = 0; i < 1 << m; i ++ )
    {
        int tot = 0;
        for(int j = 1; j <= m; j ++ )
            if(i >> (j - 1) & 1)
                tot += s[j];
        l[i] = tot;
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;

    for(int i = 1; i < 1 << m; i ++ )
        for(int j = 1; j <= m; j ++ )
            if(i >> (j - 1) & 1)
            {
                int last = i ^ (1 << j - 1);
                int L = l[last], R = l[i];
                f[i] = min(f[i], f[last] + (R - L) - (sum[j][R] - sum[j][L]));
            }
        

    cout << f[(1 << m) - 1] << endl;
    
    return 0;
}
