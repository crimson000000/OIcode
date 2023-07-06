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

const int N = 55;
int f[N][N];
char s[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    int n = strlen(s + 1);
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; i ++ ) f[i][i] = 1;

    for(int len = 1; len <= n; len ++ )
        for(int l = 1; l <= n; l ++ )
        {
            int r = l + len - 1;
            if(r > n) break;
            if(l != r && s[l] == s[r])
                f[l][r] = min(f[l][r - 1], f[l + 1][r]);
            for(int k = l; k < r; k ++ )
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
        }
    
    cout << f[1][n] << endl;

    return 0;
}
