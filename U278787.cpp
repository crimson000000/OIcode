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

const int N = 1e3 + 10;
int f[N];
int n, mod;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    mod = read(); 

    f[0] = 1;
    f[1] = 1;
    for(int i = 2; i <= 1000; i ++ )
    {
        f[i] = 1 + ((ll)i * (i - 1)) % mod * f[i - 2] % mod;
        for(int j = 3; j <= i; j ++ )
            f[i] = (f[i] + (ll)f[i - j] * 2 % mod * j % mod) % mod;
        f[i] = (f[i] + ((ll)i * (i - 1) / 2) % mod * f[i - 2] % mod) % mod;
    }

    while(T -- )
    {
        n = read();
        cout << f[n] << endl;
    }

    return 0;
}