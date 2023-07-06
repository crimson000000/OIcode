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

const int N = 1e6 + 10;
ll a[N];
int cur1, cur2;
ll n, ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    sort(a + 1, a + n + 1);
    cur1 = 0, cur2 = n + 1;
    for(int i = 1; i <= n && cur1 != cur2; i ++ )
    {
        if(!(i & 1))
        {
            cur1 ++;
            ans += (a[cur1] - a[cur2]) * (a[cur1] - a[cur2]);
        }
        else
        {
            cur2 --;
            ans += (a[cur1] - a[cur2]) * (a[cur1] - a[cur2]);
        }
    }


    cout << ans << endl;

    return 0;
}