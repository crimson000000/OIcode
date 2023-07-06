#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline __int128 read()
{
    __int128 x = 0, f = 1;
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

inline void write(__int128 x)
{
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 85;
__int128 f[N][N];
__int128 n, m;
__int128 a[N][N];
__int128 base[N];
__int128 res;

void init()
{
    base[0] = 1;
    for(int i = 1; i < N; i ++ )
        base[i] = base[i - 1] * 2;
}

void print(__int128 x)
{
    write(x);
    puts("");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            a[i][j] = read();

    init();

    for(int i = 1; i <= n; i ++ )
    {
        memset(f, 0, sizeof f);
        for(int l = 1; l <= m; l ++ )
            for(int r = m; r >= l; r -- )   
            {
                f[l][r] = max(f[l - 1][r] + a[i][l - 1] * base[m - r + l - 1], f[l][r]);
                f[l][r] = max(f[l][r + 1] + a[i][r + 1] * base[m - r + l - 1], f[l][r]);  
                // printf("%d:%d ", l, r);
                // print(f[l][r]);   
            }
        
        __int128 ans = 0;
        for(int j = 1; j <= m; j ++ )
        {
            ans = max(f[j][j] + a[i][j] * base[m], ans);
            // printf("%d : %d : ", i, j);
            // write(f[j][j] + a[i][j] * pow2(m));
            // puts("");
        }

        // write(ans);
        // puts("");

        res += ans;
    }

    write(res);
    
    return 0;
}
