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
int d[N], t[N], lt[N], cnt[N], T[N], a[N], b[N];
int f[N];
int n, m, k;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    for(int i = 2; i <= n; i ++ ) d[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        T[i] = read(), a[i] = read(), b[i] = read();
        lt[a[i]] = max(lt[a[i]], T[i]);
        cnt[b[i]] ++;
    }

    for(int i = 2; i <= n; i ++ )
        t[i] = max(t[i - 1], lt[i - 1]) + d[i];

    while(k -- )
    {
        int y = 0, z = 0;
        for(int i = n; i >= 2; i -- )
        {
            if(t[i] <= lt[i]) f[i] = cnt[i];
            else f[i] = f[i + 1] + cnt[i];
        }

        for(int i = 1; i <= n; i ++ )
        {
            // cout << f[i] << ' ';
            if(f[i] > z && d[i])
            {
                z = f[i];
                y = i;
            }
        }
        
        // puts("");

        if(y == 0) break;
        d[y] --;
        for(int i = y; i <= n; i ++ )
            t[i] = max(t[i - 1], lt[i - 1]) + d[i];
    }

    int ans = 0;
    for(int i = 1; i <= m; i ++ )
    {
        ans += t[b[i]] - T[i];
    }

    cout << ans << endl;

    return 0;
}