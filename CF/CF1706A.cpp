#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
bitset<N> st;
int n, m;

inline void solve()
{
    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) st[i] = false;
    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        if(x > m - x + 1) x = m - x + 1;
        if(st[x]) st[m - x + 1] = true;
        else st[x] = true;
    }

    for(int i = 1; i <= m; i ++ )
        putchar('A' + (st[i] ? 0 : 1));
    puts("");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}