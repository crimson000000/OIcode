#define LOCAL
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using PII = pair<ll, ll>;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1010;
char a1[N][N], a2[N][N];
int a, b;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    a = read() - 1, b = read() - 1;

    for(int i = 1; i <= 50; i ++ )
        for(int j = 1; j <= 99; j ++ )
            a1[i][j] = '.';

    for(int i = 1; i <= 49; i ++ )
        for(int j = 1; j <= 99; j ++ )
            a2[i][j] = '#';

    int line = 1;
    while(b)
    {
        for(int i = 1; i <= 99; i += 2)
        {
            a1[line][i] = '#';
            b --;
            if(!b) break;
        }
        line += 2;
    }

    line = 1;
    while(a)
    {
        for(int i = 1; i <= 99; i += 2)
        {
            a2[line][i] = '.';
            a --;
            if(!a) break;
        }
        line += 2;
    }

    reverse(a2 + 1, a2 + 49 + 1);
    cout << 99 << ' ' << 99 << endl;
    for(int i = 1; i <= 50; i ++ ) puts(a1[i] + 1);
    for(int i = 1; i <= 49; i ++ ) puts(a2[i] + 1);

    return 0;
}
