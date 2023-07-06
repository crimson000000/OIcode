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
struct edge
{
    int a, b, c;
}e[N];
vector<PII> g[N];
int n;
ll ans;

struct Union
{
    int fa[N], siz[N];
    vector<pair<int&, int>> sizh, fah;

    inline void init(int n)
    {
        for(int i = 1; i <= n; i ++ ) fa[i] = i, siz[i] = 1;
    }

    inline int find(int x)
    {
        while(x != fa[x]) x = fa[x];
        return fa[x];
    }

    inline void merge(int x, int y, int op)
    {
        x = find(x), y = find(y);
        if(siz[x] > siz[y]) swap(x, y);
        if(op == 0)
        {
            fa[x] = y;
            siz[y] += siz[x];
        }
        else
        {
            fah.push_back({fa[x], fa[x]});
            fa[x] = y;
            sizh.push_back({siz[y], siz[y]});
            siz[y] += siz[x];
        }
    }

    inline void roll(int h)
    {
        while(sizh.size() > h)
        {
            sizh.back().first = sizh.back().second;
            sizh.pop_back();
            fah.back().first = fah.back().second;
            fah.pop_back();
        }
    }

    inline int get_size(int x)
    {
        x = find(x);
        return siz[x];
    }

    inline int now()
    {
        return sizh.size();
    }
}gat;

ll dfs(int l, int r)
{
    if(l == r)
    {
        ll res = 0;
        for(auto t : g[l])
            res += (ll)gat.get_size(t.first) * gat.get_size(t.second);
        return res;
    }
    int h = gat.now();
    int mid = l + r >> 1;
    for(int i = mid + 1; i <= r; i ++ )
        for(auto t : g[i])
            gat.merge(t.first, t.second, 1);
    ll res = dfs(l, mid);
    gat.roll(h);
    for(int i = l; i <= mid; i ++ )
        for(auto t : g[i])
            gat.merge(t.first, t.second, 1);
    res += dfs(mid + 1, r);
    gat.roll(h);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    gat.init(n);
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        e[i] = {a, b, c};
        g[c].push_back({a, b});
    }

    ans = dfs(1, n);

    cout << ans << endl;

    return 0;
}