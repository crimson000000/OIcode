#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef double ld;

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
int n, m, k;
bitset<N> ans;
struct node
{
    int l, r;
    vector<PII> q;
}t[N << 2];

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void change(int p, int l, int r, PII a)
{
    if(t[p].l >= l && t[p].r <= r) 
    {
        t[p].q.emplace_back(a);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, a);
    if(r > mid) change(p << 1 | 1, l, r, a);
}

struct Set
{
    int p[N], siz[N];
    vector<pair<int, int&> > hfa, hsiz;

    inline int find(int x)
    {
        while(p[x] != x) x = p[x];
        return x;
    }

    inline void merge(int x, int y, int op)
    {
        x = find(x), y = find(y);
        if(siz[x] < siz[y])
        {
            if(op)
            {
                hfa.emplace_back(p[x], p[x]);
                hsiz.emplace_back(siz[y], siz[y]);
            }
            siz[y] += siz[x];
            p[x] = y;
        }
        else
        {
            if(op)
            {
                hfa.emplace_back(p[y], p[y]);
                hsiz.emplace_back(siz[x], siz[x]);
            }
            siz[x] += siz[y];
            p[y] = x;
        }
    }

    inline int history()
    {
        return hfa.size();
    }

    inline void undo(int h)
    {
        while(history() > h)
        {
            hfa.back().second = hfa.back().first;
            hsiz.back().second = hsiz.back().first;
            hfa.pop_back();
            hsiz.pop_back();
        }
    }
}s;

inline int id(int x, int op)
{
    return x + op * n;
}

void dfs(int p)
{
    int h = s.history();
    bool flag = false;
    for(auto v : t[p].q)
    {
        int x = v.first, y = v.second;
        if(s.find(id(x, 0)) == s.find(id(y, 0)))
        {
            flag = true;
            break;
        }
        s.merge(id(x, 0), id(y, 1), 1);
        s.merge(id(x, 1), id(y, 0), 1);
    }

    if(flag) goto M1;

    if(t[p].l == t[p].r) ans[t[p].l] = true;
    else dfs(p << 1), dfs(p << 1 | 1);

    M1:;

    s.undo(h);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    build(1, 1, k);

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), l = read() + 1, r = read();
        change(1, l, r, {a, b});
    }

    for(int i = 1; i <= 2 * n; i ++ ) s.p[i] = i, s.siz[i] = 1;

    dfs(1);

    for(int i = 1; i <= k; i ++ )
        if(ans[i]) puts("Yes");
        else puts("No");

    return 0;
}
