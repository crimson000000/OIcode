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

const int N = 10010;
struct item
{
    ll val;
    ll num;
    bool operator < (const item& I)
    {
        return val > I.val;
    }
}a[N];
ll d[N];
ll n, ans;

bool insert(ll x)
{
    for(int i = 62; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(d[i + 1] == 0)
            {
                d[i + 1] = x;
                return true;
            }
            else x ^= d[i + 1];
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
        a[i].num = read();
        a[i].val = read();
    }

    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++ )
    {
        if(insert(a[i].num))
            ans += a[i].val;
    }

    cout << ans << endl;
    
    return 0;
}
