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

const int N = 200;
ll d[N], sum;
ll c[N][N];
ll n, ans = 1;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> d[i];
        sum += d[i] - 1;
    }

    if(n == 1)
    {
        cout << !d[1] << endl;
        return 0;
    }

    if(sum != n - 2)
    {
        cout << 0 << endl;
        return 0;
    }

    c[0][0] = c[1][0] = c[1][1] = 1;
    for(int i = 2; i <= N - 1; i ++ )
        for(int j = 0; j <= i; j ++ )
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

    for(int i = 1; i <= n; i ++ )
    {
        ans *= c[sum][d[i] - 1];
        sum -= d[i] - 1;
    }

    cout << ans << endl;
    
    return 0;
}
