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

const int N = 1e6 + 10, INF = 0x3f3f3f3f, M = 1e6;
ll dp[N], sum[N], h[N];
int q[N], hh, tt;
int n;

struct line
{
    ll k, b;
}a[N];

inline ll f(int id, int x)
{
    return a[id].k * x + a[id].b;
}

struct node
{
    int l, r;
    int minn;
}t[N << 2];
int root, cnt;

inline void insert(int &p, int l, int r, int id)
{
    if(!p) p = ++ cnt;
    if(t[p].minn == 0)
    {
        t[p].minn = id;
        return;
    }
    if(l == r) return;
    int mid = l + r >> 1;
    if(f(id, mid) < f(t[p].minn, mid)) swap(id, t[p].minn);
    if(f(id, l) < f(t[p].minn, l)) insert(t[p].l, l, mid, id);
    if(f(id, r) < f(t[p].minn, r)) insert(t[p].r, mid + 1, r, id);
    return;
}

inline ll query(int p, int l, int r, int x)
{
    ll ans = (ll)INF * INF;
    if(!p) return (ll)INF * INF;
    if(t[p].minn) ans = min(ans, f(t[p].minn, x));
    if(l == r) return ans;
    int mid = l + r >> 1;
    if(x <= mid) ans = min(ans, query(t[p].l, l, mid, x));
    else ans = min(ans, query(t[p].r, mid + 1, r, x));
    return ans;
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
        h[i] = read();
    }

    for(int i = 1; i <= n; i ++ )
    {
        int w = read();
        sum[i] = sum[i - 1] + w;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[1] = 0;
    a[1].k = -2 * h[1], a[1].b = dp[1] - sum[1] + h[1] * h[1];
    insert(root, 0, M, 1);

    for(int i = 2; i <= n; i ++ )
    {
        dp[i] = query(root, 0, M, h[i]) + sum[i - 1] + h[i] * h[i];
        a[i].k = -2 * h[i];
        a[i].b = dp[i] - sum[i] + h[i] * h[i];
        insert(root, 0, M, i);
    }
    
    cout << dp[n] << endl;

    return 0;
}