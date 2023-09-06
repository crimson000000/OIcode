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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int maxsiz[N], siz[N], dist[N];
bool vis[N];
int rt;
int n, k;

struct fhq
{
    struct node
    {
        int l, r;
        int val, key;
        int siz;
    }t[N];
    int root, cnt;

    inline int New(int val)
    {
        t[++ cnt].val = val;
        t[cnt].key = rand();
        t[cnt].siz = 1;
        t[cnt].l = t[cnt].r = 0;
        return cnt;
    }

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    }

    int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key > t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            pushup(x);
            return x;
        }
        else
        {
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
    inline void insert(int val)
    {
        split(root, val, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline void clear()
    {
        cnt = root = 0;
    }

    inline int lowernums(int val)
    {
        split(root, val, x, y);
        int res = t[x].siz;
        root = merge(x, y);
        return res;
    }
} t;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        calc_siz(j, u, sz);
        siz[u] += siz[j];
        maxsiz[u] = max(maxsiz[u], siz[j]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt])
    {
        rt = u;
    }
}

int dd[N], tt;
void calc_dis(int x, int fa)
{
    dd[++ tt] = dist[x];
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = dist[x] + w[i];
        calc_dis(j, x);
    }
}

ll ans;
void dfz(int u, int fa)
{
    vis[u] = true;
    t.insert(0);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = w[i];
        calc_dis(j, u);
        for(int i = 1; i <= tt; i ++ )
            ans += t.lowernums(k - dd[i]);
        for(int i = 1; i <= tt; i ++ )
            t.insert(dd[i]);
        tt = 0;
    }
    t.clear();
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(j, u, siz[j]);
        calc_siz(rt, -1, siz[j]);
        dfz(rt, u);
    }
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
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    k = read();
    rt = 0;
    maxsiz[rt] = INF;
    calc_siz(1, -1, n);
    calc_siz(rt, -1, n);
    dfz(rt, -1);

    cout << ans << endl;
    
    return 0;
}
