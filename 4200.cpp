#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
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
    int key, siz;
    int fa;
    int w, power, tu;
    int ptag, ttag;
}t[N];
int cnt, root[N];
int wei[N];
int n, m;

map<pair<int, int>, int> mp;
int npos[N];
int tot;

inline int New(int val)
{
    t[++ cnt].w = val;
    t[cnt].siz = 1;
    t[cnt].key = rand();
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline void streng(int p, int val)
{
    if(!p) return;
    t[p].power = max(t[p].power, val);
    t[p].ptag = max(t[p].ptag, val);
}

inline void tuan(int p, int val)
{
    if(!p) return;
    t[p].tu = max(t[p].tu, val);
    t[p].ttag = max(t[p].ttag, val);
}

inline void pushdown(int p)
{
    if(t[p].ptag)
    {
        if(t[p].l) streng(t[p].l, t[p].ptag);
        if(t[p].r) streng(t[p].r, t[p].ptag);
        t[p].ptag = 0;
    }
    if(t[p].ttag)
    {
        if(t[p].l) tuan(t[p].l, t[p].ttag);
        if(t[p].r) tuan(t[p].r, t[p].ttag);
        t[p].ttag = 0;
    }
}

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        pushdown(x);
        t[x].r = merge(t[x].r, y);
        t[t[x].r].fa = x;
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        t[y].l = merge(x, t[y].l);
        t[t[y].l].fa = y;
        pushup(y);
        return y;
    }
}

inline void split(int p, int siz, int &x, int &y, int fa = 0, int fb = 0)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[t[p].l].siz + 1 > siz)
        {
            y = p;
            t[y].fa = fb;
            split(t[p].l, siz, x, t[y].l, fa, y);
        }
        else
        {
            x = p;
            t[x].fa = fa;
            split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y, x, fb);
        }
        pushup(p);
    }
}

inline void split_val(int p, int val, int &x, int &y, int fa = 0, int fb = 0)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[p].w > val)
        {
            y = p;
            t[y].fa = fb;
            split_val(t[p].l, val, x, t[y].l, fa, y);
        }
        else
        {
            x = p;
            t[x].fa = fa;
            split_val(t[p].r, val, t[x].r, y, x, fb);
        }
        pushup(p);
    }
}

int x, y, z;
inline int find(int x)
{
    int p = x, res = t[t[x].l].siz + 1;
    while(x)
    {
        if(t[t[x].fa].r == x) res += t[t[t[x].fa].l].siz + 1;
        x = t[x].fa;
    }
    return res;
}

inline int max(int root)
{
    int p = root;
    while(t[p].r) p = t[p].r;
    return t[p].w;
}

inline void insert(int& root, int val)
{
    streng(root, val);
    int p = New(val);
    streng(p, max(root));
    split_val(root, val, x, y);
    root = merge(merge(x, p), y);
    tuan(root, t[root].siz - 1);
}

inline void insert_node(int &root, int p)
{
    int val = t[p].w;
    streng(root, val);
    streng(p, max(root));
    split_val(root, val, x, y);
    root = merge(merge(x, p), y);
    tuan(root, t[root].siz - 1);
}

inline void pushdown_all(int p)
{
    pushdown(p);
    if(t[p].l) pushdown_all(t[p].l);
    if(t[p].r) pushdown_all(t[p].r);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int w = read(), x = read(), y = read();
        wei[i] = w;
        if(!mp[{x, y}]) mp[{x, y}] = ++ tot;
        insert(root[mp[{x, y}]], w);
        npos[i] = mp[{x, y}];
    }

    m = read();
    while(m -- )
    {
        int id = read(), xx = read(), yy = read();
        if(!mp[{xx, yy}]) mp[{xx, yy}] = ++ tot;
        int to = mp[{xx, yy}];
        
        int now = npos[id];
        int rk = find(id);
        split(root[now], rk - 1, x, y);
        split(y, 1, y, z);
        root[now] = merge(x, z);

        insert_node(root[to], y);
        npos[id] = to;
    }

    for(int i = 1; i <= tot; i ++ ) pushdown_all(root[i]);

    for(int i = 1; i <= n; i ++ )
    {
        printf("%lld\n", (long long)t[i].power * t[i].tu);
    }

    return 0;
}