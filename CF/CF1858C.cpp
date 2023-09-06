#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
bitset<N> vis;
int n;
int p[N];
int tt;

inline void solve()
{
    n = read();
    for(int i = 1; i <= n; i ++ ) vis[i] = false;
    tt = 0;
    
    for(int i = 1; i <= n; i ++ )
    {
        if(vis[i]) continue;
        int x = i;
        while(x <= n)
        {
            vis[x] = true;
            p[++ tt] = x;
            x <<= 1;
        }
    }

    for(int i = 1; i <= n; i ++ ) printf("%d ", p[i]);
    puts("");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}