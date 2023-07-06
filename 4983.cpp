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
ll f[N], cnt[N], s[N], a[N];
int q[N], hh, tt;
int n, k;

inline ll Y(int x)
{
    return f[x] + s[x] * s[x];
}

inline ll X(int x)
{
    return s[x];
}

inline ll K(int x)
{
    return 2 * (s[x] + 1);
}

inline bool check(ll mid)
{
    f[0] = 0;
    hh = 0, tt = -1;
    q[++ tt] = 0;
    for(int i = 1; i <= n; i ++ )
    {
        while(hh < tt && (Y(q[hh + 1]) - Y(q[hh])) <= K(i) * (X(q[hh + 1]) - X(q[hh]))) hh ++;
        f[i] = f[q[hh]] + (s[i] - s[q[hh]] + 1) * (s[i] - s[q[hh]] + 1) + mid;
        cnt[i] = cnt[q[hh]] + 1;
        while(hh < tt && (Y(q[tt]) - Y(q[tt - 1])) * (X(i) - X(q[tt])) >= 
                        (Y(i) - Y(q[tt])) * (X(q[tt]) - X(q[tt - 1])))
            tt --;
        q[++ tt] = i;
    }
    return cnt[n] > k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        s[i] = s[i - 1] + a[i];
    }

    ll l = 0, r = 1e18, ans;
    while(l <= r)
    {
        ll mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid - 1, ans = mid;
    }

    check(ans);

    cout << f[n] - ans * k << endl;

    return 0;
}