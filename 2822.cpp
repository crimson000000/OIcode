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

const int N = 2e3 + 10;
ll c[N][N], ans[N][N];
ll t, k, n, m;

void init()
{
    c[0][0] = 1;
    c[1][0] = 1;
    c[1][1] = 1;
    for(int i = 2; i <= 2000; i ++ )
    {
        for(int j = 0; j <= i; j ++ )
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
            ans[i][j] += ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
            if(c[i][j] % k == 0) ans[i][j] ++;
        }
        ans[i][i + 1] = ans[i][i];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> t >> k;

    init();
    while(t -- )
    {
        cin >> n >> m;
        if(m > n) cout << ans[n][n] << endl;
        else cout << ans[n][m] << endl;
    }
    
    return 0;
}
