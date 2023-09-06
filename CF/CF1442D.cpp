#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 3010;
vector<int> a[N];
ll sum[N];
int n, k;
ll f[N], tmp[N][N];
ll ans;

void cdq(int l, int r, int d)
{
    if(l == r)
    {
        ll now = 0;
        for(int i = 0; i <= min(a[l][0], k); i ++ )
        {
            ans = max(ans, f[k - i] + now);
            now += a[l][i + 1];
        }
        return;
    }
    int mid = l + r >> 1;
    memcpy(tmp[d], f, sizeof f);
    for(int i = mid + 1; i <= r; i ++ )
        for(int j = k; j >= a[i][0]; j -- )
            f[j] = max(f[j], f[j - a[i][0]] + sum[i]);
    cdq(l, mid, d + 1);
    memcpy(f, tmp[d], sizeof f);
    for(int i = l; i <= mid; i ++ )
        for(int j = k; j >= a[i][0]; j -- )
            f[j] = max(f[j], f[j - a[i][0]] + sum[i]);
    cdq(mid + 1, r, d + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ )
    {
        int t = read();
        a[i].emplace_back(t);
        for(int j = 1; j <= t; j ++ )
        {
            int x = read();
            a[i].emplace_back(x);
            sum[i] += x;
        }
    }

    cdq(1, n, 1);

    cout << ans << endl;
    
    return 0;
}
