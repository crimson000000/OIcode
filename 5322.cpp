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

const int N = 110, M = 10010;
int a[N][N]; // a[i, j]表示第i个城堡第j大的兵力
int f[M];
int s, n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d%d", &s, &n, &m);

    for(int i = 1; i <= s; i ++ )
        for(int j = 1; j <= n; j ++ )
            scanf("%d", &a[j][i]);

    for(int i = 1; i <= n; i ++ )
        sort(a[i] + 1, a[i] + s + 1);

    for(int i = 1; i <= n; i ++ )   
        for(int j = m; j >= 0; j -- )
            for(int k = 1; k <= s; k ++ )
                if(j >= a[i][k] * 2 + 1) f[j] = max(f[j], f[j - (a[i][k] << 1) - 1] + i * k);

    cout << f[m] << endl;
    
    return 0;
}
