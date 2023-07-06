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

const int N = 310;
int f[N][N];
int a[N];
int n, ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for (int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        f[i][i] = a[i];
    } 

    for(int len = 2; len <= n; len ++ )
    {
        for(int l = 1; l <= n; l ++ )
        {
            int r = l + len - 1;
            if(r > n) break;

            for(int k = l; k < r; k ++ )
            {
                if(f[l][k] == f[k + 1][r] && f[l][k] != 0 && f[k + 1][r] != 0)
                {
                    f[l][r] = max(f[l][r], f[l][k] + 1);
                    ans = max(ans, f[l][r]);
                }
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}
