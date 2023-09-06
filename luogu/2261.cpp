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

ll k, n;
ll sum;

ll next_place(ll x)
{
    return k / (k / x);
}

ll getsum(ll l, ll r)
{
    return (r + l) * (r - l + 1) / 2;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> k;
    sum = n * k;
    if(n > k) n = k;

    for(ll l = 1, r; l <= n; l = r + 1)
    {
        // cout << l << endl;
        if(l > n) break;
        r = next_place(l);
        2
        if(r > n) r = n;
        sum -= (k / l) * getsum(l, r);
    }

    cout << sum << endl;
    
    return 0;
}
