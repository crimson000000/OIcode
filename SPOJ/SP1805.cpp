#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PII;

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
int h[N];
int l[N], r[N];
int n;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    // int T = read();
    while(n = read())
    {    
        ans = 0;
        for(int i = 1; i <= n; i ++ ) h[i] = read(), l[i] = r[i] = i;

        for(int i = 1; i <= n; i ++ )
            while(l[i] > 1 && h[i] <= h[l[i] - 1]) l[i] = l[l[i] - 1];
        
        for(int i = n; i >= 1; i -- )
            while(r[i] < n && h[i] <= h[r[i] + 1]) r[i] = r[r[i] + 1];
        
        for(int i = 1; i <= n; i ++ )
            ans = max(ans, (ll)(r[i] - l[i] + 1) * h[i]);
        
        printf("%lld\n", ans);
    }

    return 0;
}