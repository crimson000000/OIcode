#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int long long

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
int h[N], e[N], ne[N], idx;
struct city
{
    int a;
    int v, h;
    int cnt;
}c[N];

int n, m;
int ans[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct node
{
    int l, r;
    int siz, key;
    int val, id;
    int add, mul;
}t[N];
int root[N];
int cnt;

inline int New(int val, int id)
{
    t[++ cnt].val = val;
    t[cnt].id = id;
    t[cnt].mul = 1;
    t[cnt].siz = 1;
    t[cnt].key = rand();
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline void tag(int p, int mul, int add)
{
    if(p)
    {
        t[p].val = t[p].val * mul + add;
        t[p].add *= mul;
        t[p].mul *= mul;
        t[p].add += add;
    }
}

inline void pushdown(int p)
{
    if(t[p].l) tag(t[p].l, t[p].mul, t[p].add);
    if(t[p].r) tag(t[p].r, t[p].mul, t[p].add);
    t[p].add = 0, t[p].mul = 1;
} 

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        pushdown(x);
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

inline void split(int p, int val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[p].val <= val)
        {
            x = p;
            split(t[p].r, val, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, val, x, t[y].l);
        }
        pushup(p);
    }
}

int x, y, z;
inline void insert(int &root, int val, int id)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val, id)), y);
}

int dep[N], start[N], die[N];
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs1(j, u);
    }
}

inline void del(int p, int st)
{
    if(t[p].l) del(t[p].l, st);
    if(t[p].r) del(t[p].r, st);
    die[t[p].id] = st;
}

inline void ldr(int p)
{
    pushdown(p);
    if(t[p].l) ldr(t[p].l);
    printf("[%d %d] ", t[p].val, t[p].id);
    if(t[p].r) ldr(t[p].r);
}

inline void insert(int &root, int p)
{
    int val = t[p].val;
    split(root, val, x, y);
    root = merge(merge(x, p), y);
}

void dfs_merge(int x, int &y)
{
    if(!x) return;
    pushdown(x);
    dfs_merge(t[x].l, y);
    dfs_merge(t[x].r, y);
    t[x].l = t[x].r = 0;
    insert(y, x);
}

inline int merge_to_one(int x, int y)
{
    if(t[x].siz > t[y].siz) swap(x, y);
    dfs_merge(x, y);
    return y;
}

void dfs(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u);
        root[u] = merge_to_one(root[j], root[u]);
    }

    // printf("%d: ", u);
    // ldr(root[u]);
    // puts("");

    split(root[u], c[u].h - 1, x, y);
    del(x, u);
    
    // printf("%d: ", u);
    // ldr(y);
    // puts("");
    root[u] = y;

    if(!c[u].a) tag(root[u], 1, c[u].v);
    else tag(root[u], c[u].v, 0);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) c[i].h = read();
    for(int i = 2; i <= n; i ++ )
    {
        int x = read();
        c[i].a = read(), c[i].v = read();
        add(x, i), add(i, x);
    }

    dfs1(1, 1);

    for(int i = 1; i <= m; i ++ )
    {
        int s = read(), u = read();
        insert(root[u], s, i);
        start[i] = u;
    }

    dfs(1, 1);

    for(int i = 1; i <= m; i ++ )
        ans[die[i]] ++;

    for(int i = 1; i <= n; i ++ ) 
    {
        printf("%lld\n", ans[i]);
    }
    for(int i = 1; i <= m; i ++ ) 
    {
        printf("%lld\n", dep[start[i]] - dep[die[i]]);
    }

    return 0;
}
