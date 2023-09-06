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

const int N = 5010, M = 1e6 + 10;
int cnt[M * 2];
int a[N];
ll s[N][N];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read() + M;

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = i + 1; j <= n; j ++ )
        {
            if(j > i + 1 && a[i] + a[j] <= 3 * M && a[i] + a[j] > M) 
                s[i][j] = cnt[3 * M - a[i] - a[j]];
            cnt[a[j]] ++;
        }
        for(int j = i + 1; j <= n; j ++ )
            cnt[a[j]] --;
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];

    while(m -- )
    {
        int l = read(), r = read();
        printf("%lld\n", s[r][r] - s[l - 1][r] - s[r][l - 1] + s[l - 1][l - 1]);
    }
    
    return 0;
}
