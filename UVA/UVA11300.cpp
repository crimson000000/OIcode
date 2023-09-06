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

const int N = 1e6 + 10;
ll a[N], c[N], avg;
ll n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(scanf("%lld", &n) != EOF)
    {
        avg = 0;
        for(int i = 1; i <= n; i ++ ) 
        {
            cin >> a[i];
            avg += a[i];
        }

        avg /= n;
        c[1] = 0;
        for(int i = 2; i <= n; i ++ ) c[i] = c[i - 1] + a[i] - avg;

        sort(c + 1, c + n + 1);
        ll res = 0;
        for(int i = 1; i <= n; i ++ ) res += abs(c[i] - c[(n + 1) / 2]);

        cout << res << endl;
    }

    return 0;
}
