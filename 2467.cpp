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

const int N = 4210;
int f[N][N];
int n, mod;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read();

    f[1][1] = 1;
    for(int i = 2; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            f[i][j] = (f[i][j - 1] + f[i - 1][i - j + 1]) % mod;

    int ans = 0;
    for(int i = 1; i <= n; i ++ ) ans = (ans + f[n][i]) % mod;
    cout << (ans << 1) % mod << endl;
    
    return 0;
}
