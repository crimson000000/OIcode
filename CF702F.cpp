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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct node
{
    int l, r;
    int val, siz, key;
    int add, num, id;
    int laz;
}t[N];
int cnt, root;

inline int New(int val, int id)
{
    t[++ cnt].val = val;
    t[cnt].siz = 1;
    t[cnt].key = rand();
    t[cnt].id = id;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        t[t[p].l].add += t[p].add;
        t[t[p].r].add += t[p].add;
        t[t[p].l].num += t[p].add;
        t[t[p].r].num += t[p].add;
        t[p].add = 0;
    }
    if(t[p].laz)
    {
        t[t[p].l].laz += t[p].laz;
        t[t[p].r].laz += t[p].laz;
        t[t[p].l].val += t[p].laz;
        t[t[p].r].val += t[p].laz;
        t[p].laz = 0;
    }
}

int merge(int x, int y)
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

void split(int p, int val, int &x, int &y)
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
void insert_val(int val, int id, int r = root)
{
    split(r, val, x, y);
    root = merge(merge(x, New(val, id)), y);
}

void insert(int &root, int p)
{
    int val = t[p].val;
    split(root, val, x, y);
    root = merge(merge(x, p), y);
}

void dfs(int x, int &y)
{
    if(!x) return;
    pushdown(x);
    dfs(t[x].l, y);
    dfs(t[x].r, y);
    t[x].l = t[x].r = 0;
    insert(y, x);
}

int merge_one(int x, int y)
{
    if(t[x].siz > t[y].siz) swap(x, y);
    dfs(x, y);
    return y;
}

void dfs(int p)
{
    if(!p) return;
    pushdown(p);
    dfs(t[p].l);
    dfs(t[p].r);
}

int ans[N];
void dfs1(int p)
{
    if(!p) return;
    ans[t[p].id] = t[p].num;
    dfs1(t[p].l);
    dfs1(t[p].r);
}

struct T
{
    int c, q;
    bool operator < (const T& a) const
    {
        if(q == a.q) return c > a.c;
        return q < a.q;
    }
}a[N];

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int c = read(), q = read();
        a[i] = {c, q};
    }

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int v = read();
        insert_val(v, i);
    }

    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);

    for(int i = 1; i <= n; i ++ )
    {
        int cost = a[i].c;
        split(root, cost - 1, x, y);
        t[y].num ++, t[y].add ++;
        t[y].laz += -cost, t[y].val -= cost;
        split(y, cost - 1, y, z);
        x = merge_one(x, y);
        root = merge(x, z);
    }

    dfs(root);
    dfs1(root);

    for(int i = 1; i <= m; i ++ ) cout << ans[i] << ' ';

    return 0;
}
