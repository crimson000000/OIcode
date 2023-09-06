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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

ll d[70];
ll a[1010];
ll n, ans;

bool insert(ll x)
{
    for(int i = 33; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                d[i] = x;
                return true;
            }
            x ^= d[i];
        }
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
    }
    
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++ )
    {
        if(!insert(a[i])) ans += a[i];
    }

    cout << ans << endl;

    return 0;
}
