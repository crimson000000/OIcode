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

const int N = 1010;
int f[N][N];
int w[N], v[N];
int n, m, t;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), t = read();

    for(int i = 1; i <= n; i ++ )
    {
        w[i] = read();
        v[i] = read();
    }
    
    for(int i = 1; i <= n; i ++ )
        for(int j = m; j >= w[i]; j -- )
            for(int k = t; k >= v[i]; k -- )
                f[j][k] = max(f[j][k], f[j - w[i]][k - v[i]] + 1);

    cout << f[m][t] << endl;

    return 0;
}
