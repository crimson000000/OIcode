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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
int v[N];
vector<int> nums;
int n, m, last, nn;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct segment_tree
{
    struct segment
    {
        int l, r;
        int cnt;
    }t[N << 2];

    int idx, root[N];

    inline void pushup(int p)
    {
        t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
    }

    void build(int &p, int l, int r)
    {
        if(!p) p = ++ idx;
        if(l == r) return;
        int mid = l + r >> 1;
        build(t[p].l, l, mid);
        build(t[p].r, mid + 1, r);
    }

    int insert(int q, int l, int r, int pos)
    {
        int p = ++ idx;
        t[p] = t[q];
        if(l == r)
        {
            t[p].cnt ++;
            return p;
        }
        int mid = l + r >> 1;
        if(pos <= mid) t[p].l = insert(t[q].l, l, mid, pos);
        else t[p].r = insert(t[q].r, mid + 1, r, pos);
        pushup(p);
        return p;
    }

    int query(int p, int pos, int l = 1, int r = n)
    {
        if(l == r) return t[p].cnt;
        int mid = l + r >> 1;
        if(pos <= mid) return query(t[p].l, pos, l, mid);
        else return query(t[p].r, pos, mid + 1, r);
    }

    int query(int p, int q, int a, int b, int l, int r, int k)
    {
        if(l == r) return l;
        int mid = l + r >> 1;
        int cnt = t[t[p].l].cnt + t[t[q].l].cnt - t[t[a].l].cnt - t[t[b].l].cnt;
        if(cnt >= k) return query(t[p].l, t[q].l, t[a].l, t[b].l, l, mid, k);
        else return query(t[p].r, t[q].r, t[a].r, t[b].r, mid + 1, r, k - cnt);
    }
} tree;

int fa[N], dep[N], son[N], siz[N];
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
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

void dfs_seg(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u]) continue;
        tree.root[j] = tree.insert(tree.root[u], 1, n, v[j]);
        dfs_seg(j);
    }
}

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
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
    {
        v[i] = read();
        nums.push_back(v[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    nn = nums.size();

    for(int i = 1; i <= n; i ++ ) 
        v[i] = lower_bound(nums.begin(), nums.end(), v[i]) - nums.begin() + 1;

    // for(int i = 1; i <= n; i ++ ) cout << v[i] << endl;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    tree.build(tree.root[0], 1, n);
    tree.root[1] = tree.insert(tree.root[0], 1, n, v[1]);

    // for(int i = 0; i <= n; i ++ )
    // {
    //     printf("%d :", i);
    //     for(int j = 1; j <= n; j ++ )
    //         printf("%d ", tree.query(tree.root[i], j));
    //     puts("");
    // }

    dfs1(1, 0);
    dfs2(1, 1);
    dfs_seg(1);

    // for(int i = 0; i <= n; i ++ ) cout << tree.root[i] << endl;

    // for(int i = 0; i <= n; i ++ )
    // {
    //     printf("%d :", i);
    //     for(int j = 1; j <= n; j ++ )
    //         printf("%d ", tree.query(tree.root[i], j));
    //     puts("");
    // }

    // cout << tree.t[tree.root[1]].cnt << endl;

    while(m -- )
    {
        int u = read(), v = read(), k = read();
        u ^= last;
        int LCA = lca(u, v);
        last = nums[tree.query(tree.root[u], tree.root[v], tree.root[LCA], tree.root[fa[LCA]], 1, n, k) - 1];
        printf("%d\n", last);
    }
    
    return 0;
}
