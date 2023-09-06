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

ll a, b, ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    a = read(), b = read();
    for(int i = 0; i <= 62; i ++ )
    {
        if(a >> i & 1) continue;
        if((a | (1ll << i)) <= b) a |= (1ll << i);
    }

    while(a)
    {
        ans ++;
        a -= (a & -a);
    }

    cout << ans << endl;

    return 0;
}