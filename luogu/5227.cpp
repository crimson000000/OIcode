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

const int N = 1e6 + 10;
struct node
{
    int l, r;
    vector<int> q;
}t[N << 2];

struct edge
{
    int u, v;
}e[N];
int n, m, Q;
int lst[N];

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void insert(int p, int l, int r, int x)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].q.emplace_back(x);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) insert(p << 1, l, r, x);
    if(r > mid) insert(p << 1 | 1, l, r, x);
}

struct uniset
{
    int fa[N], siz[N];
    vector<pair<int, int&>> hfa, hsiz;

    inline int find(int x)
    {
        while(fa[x] != x) x = fa[x];
        return x;
    }

    inline void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if(x == y) return;
        if(siz[x] > siz[y]) swap(x, y);
        hfa.emplace_back(fa[x], fa[x]);
        hsiz.emplace_back(siz[y], siz[y]);
        fa[x] = y;
        siz[y] += siz[x];
    }

    inline int history()
    {
        return hfa.size();
    }

    inline void roll(int h)
    {
        while(history() > h)
        {
            hfa.back().second = hfa.back().first;
            hsiz.back().second = hsiz.back().first;
            hfa.pop_back();
            hsiz.pop_back();
        }
    }

    inline bool connect()
    {
        return siz[find(1)] == n;
    }
} uni;

bitset<N> ans;
void dfs(int p)
{
    int h = uni.history();
    for(auto id : t[p].q)
    {
        int u = e[id].u, v = e[id].v;
        uni.merge(u, v);
    }
    
    if(t[p].l == t[p].r)
    {
        ans[t[p].l] = uni.connect();
        goto fuckccf;
    }

    dfs(p << 1);
    dfs(p << 1 | 1);

    fuckccf:;
    uni.roll(h);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        e[i] = {a, b};
    }

    for(int i = 1; i <= n; i ++ ) uni.fa[i] = i, uni.siz[i] = 1;

    Q = read();
    build(1, 1, Q);

    for(int i = 1; i <= Q; i ++ )
    {
        int cnt = read();
        while(cnt -- )
        {
            int x = read();
            if(lst[x] + 1 <= i - 1) insert(1, lst[x] + 1, i - 1, x);
            lst[x] = i;
        }
    }

    for(int i = 1; i <= m; i ++ )
        if(lst[i] != Q)
            insert(1, lst[i] + 1, Q, i);
    
    dfs(1);

    for(int i = 1; i <= Q; i ++ )
        if(ans[i]) puts("Connected");
        else puts("Disconnected");

    return 0;
}
