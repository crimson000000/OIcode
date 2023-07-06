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
ll f[N];
ll ans, n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(cin >> n, n)
    {
        memset(f, 0, sizeof f);
        ans = 0;
        for(int i = n; i; i -- )
        {
            f[i] = n / i * (n / i);
            for(int j = i * 2; j <= n; j += i) f[i] -= f[j];
            ans += i * f[i];
        }

        cout << (ans - (1 + n) * n / 2) / 2 << endl;
    }
    
    return 0;
}