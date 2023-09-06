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

const int N = 1e7 + 10;
int a[N];
int stk[N], tt;
int ch[N][2];
int n;

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
        while(tt > 0 && a[stk[tt]] > a[i]) ch[i][0] = stk[tt -- ];
        if(tt) ch[stk[tt]][1] = i;
        stk[++ tt] = i;
    }

    ll L = 0, R = 0;
    for(int i = 1; i <= n; i ++ )
    {
        L ^= (ll)i * (ch[i][0] + 1);
        R ^= (ll)i * (ch[i][1] + 1);
    }

    cout << L << ' ' << R << endl;

    return 0;
}