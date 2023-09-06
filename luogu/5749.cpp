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
vector<int> pos[N];
bitset<N> vis;
int n;
ll ans;

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int v)
    {
        for(; x <= (n << 1); x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= (n << 1); i ++ )
    {
        a[i] = read();
        pos[a[i] + n].emplace_back(i);
        bit.add(i, 1);
    }

    for(int i = (n << 1); i; i -- )
    {
        if(vis[i]) continue;
        pos[n + a[i]].pop_back();
        vis[i] = true;
        int res = pos[n - a[i]].back();
        pos[n - a[i]].pop_back();
        vis[res] = true;
        bit.add(res, -1);
        ans += bit.query(i - 1) - bit.query(res) + (a[i] < 0 ? 1 : 0);
    }

    cout << ans << endl;
    
    return 0;
}
