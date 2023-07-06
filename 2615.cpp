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

const int N = 110;
int a[N][N];
int x, y;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    a[1][n / 2 + 1] = 1;
    x = 1, y = n / 2 + 1;
    for(int i = 2; i <= n * n; i ++ )
    {
        if(x == 1 && y != n) x = n, y = y + 1;
        else if(x != 1 && y == n) x = x - 1, y = 1;
        else if(x == 1 && y == n) x = x + 1;
        else if(a[x - 1][y + 1]) x = x + 1;
        else x = x - 1, y = y + 1;
        a[x][y] = i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
            printf("%d ", a[i][j]);
        puts("");
    }

    return 0;
}