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

const int N = 1000 + 10;
int sum[N][N];
int n, d;
int maxn, cnt;

inline int get(int x1, int y1, int x2, int y2)
{
    if(x1 <= 0) x1 = 1;
    if(y1 <= 0) y1 = 1;
    return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    d = read(), n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int x = read() + 1, y = read() + 1, b = read();
        sum[x][y] += b;
    }

    for(int i = 1; i <= 129 + 100; i ++ )
        for(int j = 1; j <= 129 + 100; j ++ )
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    
    // for(int i = 1; i <= 10; i ++ )
    // {
    //     for(int j = 1; j <= 10; j ++ )
    //         printf("%d ", sum[i][j]);
    //     puts("");
    // }
        
    for(int x = 1; x <= 129; x ++ )
        for(int y = 1; y <= 129; y ++ )
        {
            int s = get(x - d, y - d, x + d, y + d);
            if(maxn < s)
            {
                maxn = s;
                cnt = 1;
            }
            else if(maxn == s) cnt ++;
        }

    printf("%d %d\n", cnt, maxn);

    return 0;
}