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

const int N = 3e5 + 10, M = 50;
int f[N][M], a[N], s[N];
int q[N], hh, tt;
int n, m, c, d;

int pre[N][M];

void print(int i, int j)
{
    if(!j) return;
    print(pre[i][j], j - 1);
    printf("%d ", pre[i][j] + 1);
}

inline int calc(int j, int k)
{
    return f[k][j - 1] + a[k + 1] - s[k + c];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), c = read(), d = read();
    for(int i = 1; i <= c * n + m; i ++ ) a[i] = read();

    for(int i = 1; i <= c * n + m; i ++ ) s[i] = s[i - 1] + a[i];

    memset(f, -0x3f, sizeof f);
    for(int i = 1; i <= d; i ++ ) f[i][0] = s[i];

    for(int j = 1; j <= n; j ++ )
    {
        hh = 0, tt = -1;
        for(int k = max(0, j * c - c - d); k <= j * c - c; k ++ )
        {
            while(hh <= tt && calc(j, q[tt]) <= calc(j, k)) tt --;
            q[++ tt] = k;
        }
        for(int i = j * c; i <= n * c + m; i ++ )
        {
            while(hh <= tt && q[hh] < max(0, i - c - d)) hh ++;
            if(hh <= tt) f[i][j] = calc(j, q[hh]) + s[i], pre[i][j] = q[hh];
            int k = i + 1 - c;
            while(hh <= tt && calc(j, q[tt]) <= calc(j, k)) tt --;
            q[++ tt] = k;
        }
    }

    printf("%d\n", f[c * n + m][n]);

    print(c * n + m, n);
    
    return 0;
}
