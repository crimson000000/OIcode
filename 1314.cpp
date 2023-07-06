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
ll w[N], v[N];
struct query
{
    ll l, r;
}q[N];
ll cnt1[N], cntv[N];
ll n, m, s, ans = 1e18;

bool check(ll mid)
{
    memset(cnt1, 0, sizeof cnt1);
    memset(cntv, 0, sizeof cntv);
    for(int i = 1; i <= n; i ++ )
        if(w[i] >= mid)
            cnt1[i] ++, cntv[i] += v[i];
    for(int i = 1; i <= n; i ++ )
    {
        cnt1[i] += cnt1[i - 1];
        cntv[i] += cntv[i - 1];
    }
    ll Y = 0;   
    for(int i = 1; i <= m; i ++ )
    {
        ll l = q[i].l, r = q[i].r;
        Y += (cnt1[r] - cnt1[l - 1]) * (cntv[r] - cntv[l - 1]);
    }
    ans = min(ans, abs(s - Y));
    return s <= Y;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), s = read();

    for(int i = 1; i <= n; i ++ ) w[i] = read(), v[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        ll l = read(), r = read();
        q[i] = {l, r};
    }

    ll l = 0, r = s + 10;
    while(l < r)
    {
        ll mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << ans << endl;

    return 0;
}