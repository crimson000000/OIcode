#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx, din[N];
int fa[N], siz[N], dep[N], son[N];
int n, q, root;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        siz[u] += siz[j];
        if(maxsize < siz[j])
        {
            son[u] = j;
            maxsize = siz[j];
        }
    }
}

int top[N], dfn[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == son[u] || j == fa[u]) continue;
        dfs2(j, j);
    }
}

struct segment
{
    int l, r;
    ll sum, add;
}t[N * 4];

void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

void pushdown(int p)
{
    if(t[p].add)
    {
        ll a = t[p].add;
        t[p << 1].add += a;
        t[p << 1 | 1].add += a;
        t[p << 1].sum += (t[p << 1].r - t[p << 1].l + 1) * a;
        t[p << 1 | 1].sum += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * a;
        t[p].add = 0;
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void change(int p, int l, int r, ll val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].sum += (t[p].r - t[p].l + 1) * val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

ll query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll sum = 0;
    if(l <= mid) sum += query(p << 1, l, r);
    if(r > mid) sum += query(p << 1 | 1, l, r);
    return sum;
}

void mchain(int x, int y, ll val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    change(1, dfn[x], dfn[y], val);
}

ll qtree(int x)
{
    return query(1, dfn[x], dfn[x] + siz[x] - 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        din[b] ++;
    }

    for(int i = 0; i < n; i ++ )
        if(!din[i])
            root = i;

    dfs1(root, root);
    dfs2(root, root);
    
    build(1, 1, n);

    q = read();
    while(q -- )
    {
        char op[2];
        scanf("%s", op);
        int u, v, d;
        if(op[0] == 'A')
        {
            u = read(), v = read(), d = read();
            mchain(u, v, (ll)d);
        }   
        else
        {
            u = read();
            cout << qtree(u) << endl;
        }
    }

    return 0;
}
