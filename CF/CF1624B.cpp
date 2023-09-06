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

ll a, b, c;

void solve()
{
    a = read(), b = read(), c = read();
    ll na = b - (c - b);
    if(na % a == 0 && na > 0) 
    {
        puts("YES");
        return;
    }
    ll nc = b + (b - a);
    if(nc % c == 0 && nc > 0)
    {
        puts("YES");
        return;
    }
    ll nb = (a + c) / 2;
    if(nb * 2 != a + c) 
    {
        puts("NO");
        return;
    }
    else
    {
        if(nb % b == 0 && nb > 0)
        {
            puts("YES");
            return;
        }
    }
    puts("NO");
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