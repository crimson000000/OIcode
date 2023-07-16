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
int n;
int l, r;
int minn[N], maxn[N];

inline bool check(int x)
{
    for(int i = 2; i <= n; i ++ )
    {
        maxn[i] = min(a[i], a[1] - minn[i - 1]);
        minn[i] = max(0, a[i] - (x - (a[1] + a[i - 1] - maxn[i - 1])));
    }

    if(!minn[n]) return true;
    return false;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(n = read())
    {
        l = 0;
        for(int i = 1; i <= n; i ++ ) 
        {
            a[i] = read();
            l = max(l, a[i] + a[i - 1]);
        }

        minn[1] = maxn[1] = a[1];

        r = 3e5;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(check(mid)) r = mid;
            else l = mid + 1;
        }

        if(n == 1) l = a[1];

        cout << l << endl;
    }
    
    return 0;
}
