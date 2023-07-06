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
int a[N];
int n, mod;
int ans;

inline bool check(int mid)
{
    int now = 0;
    for(int i = 1; i <= mid; i ++ )
    {
        now = max(now, a[i] + a[2 * mid - i + 1]);
    }

    for(int i = 1; i <= n - mid; i ++ )
    {
        int v = a[2 * mid + i] + a[2 * n - i + 1];
        if(v < mod) return false;
        now = max(now, v - mod);
    }
    ans = min(ans, now);
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mod = read();
    ans = mod;
    for(int i = 1; i <= 2 * n; i ++ ) a[i] = read();

    sort(a + 1, a + n * 2 + 1);

    int l = 0, r = n;
    while(l <= r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid - 1;
        else l = mid + 1;
    }

    cout << ans << endl;

    return 0;
}