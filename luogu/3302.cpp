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

const int N = 200000 + 10;
struct node
{
    int l, r;
    int cnt;
}t[N * 120];
int root[N], cnt;
int fa[N][18], dep[N];
int p[N], siz[N];
int h[N], e[N << 1], ne[N << 1], idx;
int v[N];
vector<int> nums;
bitset<N> vis;
int n, MM, m;
int lastans;

inline int get(int x)
{
    return nums[x - 1];
}

inline int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if(siz[x] > siz[y]) swap(x, y);
    p[x] = y;
    siz[y] += siz[x];
    siz[x] = 0;
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int build(int l, int r)
{
    int p = ++ cnt;
    if(l == r) return p;
    int mid = l + r >> 1;
    t[p].l = build(l, mid);
    t[p].r = build(mid + 1, r);
    return p;
}

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
}

inline int insert(int q, int l, int r, int pos, int val)
{
    int p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].cnt += val;
        return p;
    }
    int mid = l + r >> 1;
    if(pos <= mid) t[p].l = insert(t[q].l, l, mid, pos, val);
    else t[p].r = insert(t[q].r, mid + 1, r, pos, val);
    pushup(p);
    return p;
}

inline int query(int u, int v, int lca, int lca_f, int l, int r, int k)
{
    if(l == r) return l;
    int cnt = t[t[u].l].cnt + t[t[v].l].cnt - t[t[lca].l].cnt - t[t[lca_f].l].cnt;
    int mid = l + r >> 1;
    if(k <= cnt) return query(t[u].l, t[v].l, t[lca].l, t[lca_f].l, l, mid, k);
    else return query(t[u].r, t[v].r, t[lca].r, t[lca_f].r, mid + 1, r, k - cnt);
}

inline int lca(int u, int v)
{
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 17; i >= 0; i -- )
        if(dep[fa[v][i]] >= dep[u])
            v = fa[v][i];
    
    if(u == v) return v;

    for(int i = 17; i >= 0; i -- )
        if(fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }

    return fa[u][0];
}

void dfs(int u, int f)
{
    vis[u] = true;
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = 1; i <= 17; i ++ )
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    
    root[u] = insert(root[f], 1, n, v[u], 1);

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs(j, u);
    }
}

inline int qchain(int x, int y, int k)
{
    int anc = lca(x, y);
    // printf("%d %d's anc: %d\n", x, y, anc);
    return query(root[x], root[y], root[anc], root[fa[anc][0]], 1, n, k);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    int what_the_fxxk = read();

    n = read(), MM = read(), m = read();

    for(int i = 1; i <= n; i ++ ) 
    {
        v[i] = read();
        p[i] = i, siz[i] = 1;
        nums.push_back(v[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        v[i] = lower_bound(nums.begin(), nums.end(), v[i]) - nums.begin() + 1;

    while(MM -- )
    {
        int x = read(), y = read();
        add(x, y), add(y, x);
        merge(x, y);
    }

    root[0] = build(1, n);

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            dfs(i, 0);
    
    while(m -- )
    {
        char s[5];
        scanf("%s", s);
        int x = read() ^ lastans, y = read() ^ lastans;
        if(s[0] == 'Q')
        {
            int k = read() ^ lastans;
            // cout << x << ' ' << y << ' ' << k << endl;
            lastans = get(qchain(x, y, k));
            printf("%d\n", lastans);
        }
        else
        {
            if(siz[find(x)] < siz[find(y)]) swap(x, y);
            add(x, y), add(y, x);
            dfs(y, x);
        }
    }

    return 0;
}