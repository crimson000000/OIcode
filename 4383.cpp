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
int h[N], e[N], ne[N], w[N], idx;
ll mid;
int n, k;

struct dat
{
    ll x, y;
    bool operator < (const dat& a) const
    {
        return x == a.x ? y > a.y : x < a.x;
    }

    dat operator + (const dat& a) const
    {
        return {x + a.x, y + a.y};
    }

    dat operator + (ll a) const
    {
        return {x + a, y};
    }
}f[N][3];

inline dat New(dat a)
{
    return {a.x - mid, a.y + 1};
}

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dp(int u, int fa)
{
    f[u][2] = max(f[u][2], {-mid, 1});
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dp(v, u);
        f[u][2] = max(f[u][2] + f[v][0], New(f[u][1] + f[v][1] + w[i]));
        f[u][1] = max(f[u][1] + f[v][0], f[u][0] + f[v][1] + w[i]);
        f[u][0] = f[u][0] + f[v][0];
    }
    f[u][0] = max(f[u][0], max(New(f[u][1]), f[u][2]));
}

inline bool check(ll mid)
{
    memset(f, 0, sizeof f);
    dp(1, 1);
    return f[1][0].y <= k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), k = read() + 1;
    
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    ll l = -1e18, r = 1e18;
    while(l < r)
    {
        mid = l + r >> 1;
        check(mid);
        if(f[1][0].y <= k) r = mid;
        else l = mid + 1;
    }

    memset(f, 0, sizeof f);
    mid = l;
    dp(1, 1);

    printf("%lld\n", f[1][0].x + l * k);

    return 0;
}