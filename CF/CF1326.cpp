#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 2e6 + 10;
int z[N], f[N];
char s[N], t[N], a[N];
int n, len;
int maxn;
int ans, pre, nxt;

inline void exkmp(char *s)
{
    int len = n;
    for(int i = 1; i <= n; i ++ )
        a[i] = a[2 * len + 2 - i] = s[i];
    a[n + 1] = '$';
    len = len << 1 | 1;
    z[1] = len;
    for(int i = 2, l = 0, r = 0; i <= len; i ++ )
    {
        if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while(i + z[i] <= len && a[i + z[i]] == a[z[i] + 1]) z[i] ++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

inline void manacher(char *t)
{
    s[0] = '%', s[1] = '^';
    for(int i = 1; i <= n; i ++ )
        s[i << 1] = t[i], s[i << 1 | 1] = '^';
    len = n << 1 | 1;
    s[len + 1] = ')';
    for(int i = 1, mid = 0, r = 0; i <= len; i ++ )
    {
        f[i] = 1;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++;
        if(i + f[i] - 1 > r) mid = i, r = i + f[i] - 1;
    }
}

inline int lrange(int mid)
{
    return (mid - f[mid] + 2) >> 1;
}

inline int rrange(int mid)
{
    return (mid + f[mid] - 1) >> 1;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        for(int i = 1; i <= (n << 1) + 2; i ++ ) f[i] = 0, a[i] = 0, z[i] = 0;
        ans = pre = nxt = 0;
        scanf("%s", t + 1);
        n = strlen(t + 1);
        
        exkmp(t);
        maxn = z[n + 2];
        manacher(t);

        for(int i = 2; i < len; i ++ )
        {
            if(lrange(i) > rrange(i)) continue;
            // printf("[%d, %d]\n", lrange(i), rrange(i));
            if(lrange(i) > maxn + 1 && rrange(i) < n - maxn) continue;
            int nowans = 0;
            if(i <= len / 2)
            {
                nowans = 2 * maxn + f[i] - 1 - 2 * (maxn - lrange(i) + 1);
                if(nowans > ans)
                {
                    ans = nowans;
                    pre = f[i] - 1 + maxn - (maxn - lrange(i) + 1) * 2;
                    nxt = n - maxn + 1; 
                }
            }
            else
            {
                nowans = 2 * maxn + f[i] - 1 - 2 * (rrange(i) - n + maxn);
                if(nowans > ans)
                {
                    ans = nowans;
                    pre = maxn;
                    nxt = n - (f[i] - 1 + maxn - 2 * (rrange(i) - (n - maxn))) + 1; 
                }
            }
        }

        for(int i = 1; i <= pre; i ++ ) putchar(t[i]);
        for(int i = nxt; i <= n; i ++ ) putchar(t[i]);
        puts("");
    }

    return 0;
}
