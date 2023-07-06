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
const ll M = 1e18;
ll a[N];
vector<ll> p;
ll n, m;

void dfs1(int now, ll sum)
{
    if(now == n / 2 + 1)
    {
        if(sum <= m) p.emplace_back(sum);
        return;
    }
    dfs1(now + 1, sum);
    dfs1(now + 1, sum + a[now]);
}

ll ans;
void dfs2(int now, ll sum)
{
    if(now == n + 1)
    {
        if(sum <= m) ans += upper_bound(p.begin(), p.end(), m - sum) - p.begin();
        return;
    }
    dfs2(now + 1, sum);
    dfs2(now + 1, sum + a[now]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    dfs1(1, 0);
    sort(p.begin(), p.end());
    dfs2(n / 2 + 1, 0);

    cout << ans << endl;

    return 0;
}