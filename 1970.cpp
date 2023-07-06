#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int f[N][2];
int n, a[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        f[i][0] = f[i][1] = 1;
        for(int j = max(1, i - 500); j < i; j ++ )
        {
            if(a[j] > a[i]) f[i][0] = max(f[i][0], f[j][1] + 1);
            if(a[j] < a[i]) f[i][1] = max(f[i][1], f[j][0] + 1);
        }
    }

    cout << max(f[n][0], f[n][1]) << endl;

    return 0;
}