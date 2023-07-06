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

const int N = 5e5 + 10, K = 55;
int n, m, k, Q;

struct edge
{
    int u, v, c;
}e[N];
int P[N];
int a[N], b[N];

int fa[K][N << 1], siz[K][N << 1];
vector<pair<int, int&>> hfa, hsiz;

inline void init()
{
    for(int i = 1; i <= 2 * n; i ++ ) 
        for(int j = 1; j <= k; j ++ )
            fa[j][i] = i, siz[j][i] = 1;
}

inline int find(int c, int x)
{
    while(fa[c][x] != x) x = fa[c][x];
    return x;
} 

inline void merge(int c, int x, int y)
{
    x = find(c, x), y = find(c, y);
    if(x == y) return;
    if(siz[c][x] > siz[c][y]) swap(x, y);
    hfa.emplace_back(fa[c][x], fa[c][x]);
    hsiz.emplace_back(siz[c][y], siz[c][y]);
    fa[c][x] = y;
    siz[c][y] += siz[c][x];
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

struct segm
{
    int l, r;
    vector<int> q;
}t[N << 2];

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void insert(int p, int l, int r, int a)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].q.emplace_back(a);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) insert(p << 1, l, r, a);
    if(r > mid) insert(p << 1 | 1, l, r, a);
}

inline int id(int x, int op)
{
    return x + op * n;
}

int ans[N];
void dfs(int p)
{
    int h = history();

    for(auto qq : t[p].q)
    {
        int u = e[a[qq]].u, v = e[a[qq]].v, c = b[qq];
        merge(c, id(u, 0), id(v, 1));
        merge(c, id(u, 1), id(v, 0));
    }
    if(t[p].l == t[p].r)
    {
        int idd = a[t[p].l];
        int u = e[idd].u, v = e[idd].v, c = b[t[p].l];
        if(find(c, id(u, 0)) == find(c, id(v, 0)))
        {
            puts("NO");
            b[t[p].l] = P[idd];
        }
        else
        {
            puts("YES");
            P[idd] = b[t[p].l];
        }
        return;
    }

    dfs(p << 1);
    dfs(p << 1 | 1);
    
    roll(h);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read(), Q = read();

    init();

    build(1, 1, Q);

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        e[i] = {a, b, 0};
        P[i] = Q + 1;
    }

    for(int i = 1; i <= Q; i ++ ) a[i] = read(), b[i] = read();

    for(int i = Q; i; i -- )
    {
        int aa = a[i];
        if(i < P[aa] - 1) insert(1, i + 1, P[aa] - 1, i);
        P[aa] = i;
    }

    for(int i = 1; i <= m; i ++ ) P[i] = 0;

    dfs(1);

    return 0;
}
