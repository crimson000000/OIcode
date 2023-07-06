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

const int N = 510;
int n, m;
int f[N][N];
int pre[N][N];
int a[N], b[N];

void print(int p)
{
    if(!p) return;
    print(pre[n][p]);

    cout << b[p] << " ";
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    
    m = read();
    for(int i = 1; i <= m; i ++ ) b[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        int t = 0;
        for(int j = 1; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            pre[i][j] = pre[i - 1][j];
            if(a[i] == b[j] && f[i - 1][t] + 1 > f[i][j])
            {
                f[i][j] = f[i - 1][t] + 1;
                pre[i][j] = t;
            }
            if(a[i] > b[j] && f[i - 1][t] < f[i - 1][j]) t = j; 
        }
    }

    int res = 0;
    for(int i = 1; i <= m; i ++ ) 
    {
        if(f[n][i] > f[n][res]) res = i;
    }
    cout << f[n][res] << endl;

    print(res);

    return 0;
}
