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

const int N = 2e5 + 10;
int h[N], e[N * 2], ne[N * 2], idx;
int v[N], c[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N];
void dfs1(int u, int father)
{
    fa[u] = father, dep[u] = dep[father] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;

        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        } 
    }
}

int dfn[N], top[N], anti[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
    if(!son[u]) return;

    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

struct node
{
    int l, r;
    int maxn, sum;
}t[N * 40];
int root[N], cnt;

inline void pushup(int p)
{
    t[p].maxn = max(t[t[p].l].maxn, t[t[p].r].maxn);
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
}

void insert(int &p, int l, int r, int pos, int val)
{
    if(!p) p = ++ cnt;
    if(l == r)
    {
        t[p].maxn = t[p].sum = val;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, l, mid, pos, val);
    else insert(t[p].r, mid + 1, r, pos, val);
    pushup(p);
    if(t[p].sum == 0) p = 0;
}

int query_sum(int p, int l, int r, int L, int R)
{
    if(!p) return 0;
    if(r < L || l > R) return 0; 
    if(l >= L && r <= R) return t[p].sum;
    int mid = l + r >> 1;
    int sum = 0;
    if(L <= mid) sum += query_sum(t[p].l, l, mid, L, R);
    if(R > mid) sum += query_sum(t[p].r, mid + 1, r, L, R);
    return sum;
}

int query_max(int p, int l, int r, int L, int R)
{
    if(!p) return 0;
    if(r < L || l > R) return 0; 
    if(l >= L && r <= R) return t[p].maxn;
    int mid = l + r >> 1;
    int maxn = 0;
    if(L <= mid) maxn = max(maxn, query_max(t[p].l, l, mid, L, R));
    if(R > mid) maxn = max(maxn, query_max(t[p].r, mid + 1, r, L, R));
    return maxn;
}

int qchain_max(int x, int y)
{
    int maxn = 0;
    int reli = c[x];
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        maxn = max(maxn, query_max(root[reli], 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    maxn = max(maxn, query_max(root[reli], 1, n, dfn[y], dfn[x]));
    return maxn;
}

int qchain_sum(int x, int y)
{
    int sum = 0;
    int reli = c[x];
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        sum += query_sum(root[reli], 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    sum += query_sum(root[reli], 1, n, dfn[y], dfn[x]);
    return sum;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) 
        v[i] = read(), c[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    
    for(int i = 1; i <= n; i ++ )
    {
        insert(root[c[i]], 1, n, dfn[i], v[i]);
    }

    while(m -- )
    {
        string op;
        cin >> op;
        int x = read(), y = read();
        if(op == "CC")
        {
            insert(root[c[x]], 1, n, dfn[x], 0);
            c[x] = y;
            insert(root[c[x]], 1, n, dfn[x], v[x]);
        }
        else if(op == "CW")
        {
            v[x] = y;
            insert(root[c[x]], 1, n, dfn[x], y);
        }
        else if(op == "QS")
        {
            cout << qchain_sum(x, y) << endl;
        }
        else
        {
            cout << qchain_max(x, y) << endl;
        }
    }
    
    return 0;
}
