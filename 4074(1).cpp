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
int h[N], e[N], ne[N], idx;
int n, m, Q, lim, bcnt;
ll v[N], w[N];
int c[N], last[N];
int block[N];

struct Stack
{
    int stk[N];
    int tt;
    inline bool empty() {return tt == 0;}

    inline void clear() {tt = 0;}

    inline int size() {return tt;}

    inline int top() {return stk[tt];}

    inline void pop() {tt -- ;}

    inline void push(int x) {stk[++ tt] = x;}
}stk;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], siz[N], son[N];

void dfs1(int u, int f)
{
    int sz = stk.size();
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
        if(stk.size() - sz >= lim)
        {
            bcnt ++;
            while(stk.size() >= sz) 
            {
                block[stk.top()] = bcnt, stk.pop();
            }
        }
    }
    stk.push(u);
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
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
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

struct Query
{
    int op, x, y, tim;
    bool operator < (const Query& q) const
    {
        if(block[x] == block[q.x])
        {
            if(block[y] == block[q.y])
                return tim < q.tim;
            return block[y] < block[q.y];
        }
        return block[x] < block[q.x];
    }
}q[N];
int qt;

struct Change
{
    int x, last, to;
}ch[N];
int TIM;

bool vis[N];
int L = 1, R = 1, T;
ll num = 0, ans[N], cnt[N];

inline void update(int u)
{
    if(vis[u])
    {
        num -= (ll)v[c[u]] * w[cnt[c[u]]];
        cnt[c[u]] --;
    }
    else
    {
        cnt[c[u]] ++;
        num += (ll)v[c[u]] * w[cnt[c[u]]];
    }
    vis[u] ^= 1;
}

inline void move(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    while(dep[x] > dep[y]) update(x), x = fa[x];
    while(x != y) update(x), update(y), x = fa[x], y = fa[y];
}

inline void modify(int x, int t)
{
    if(vis[x])
    {
        update(x);
        c[x] = t;
        update(x);
    }
    else c[x] = t;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read(), Q = read();
    lim = pow(n, 0.6);

    for(int i = 1; i <= m; i ++ ) v[i] = read();
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    if(!stk.empty()) 
    {
        bcnt ++;
        while(stk.size()) block[stk.top()] = bcnt, stk.pop();
    }

    for(int i = 1; i <= n; i ++ )
    {
        c[i] = read();
        last[i] = c[i];
    }

    for(int i = 1; i <= Q; i ++ )
    {
        int type = read(), x = read(), y = read();
        if(type == 0)
        {
            TIM ++;
            ch[TIM] = {x, last[x], y};
            last[x] = y;
        }
        else
        {
            qt ++;
            q[qt] = {qt, x, y, TIM};
        }
    }

    for(int i = 1; i <= qt; i ++ )
        if(dfn[q[i].x] > dfn[q[i].y])
            swap(q[i].x, q[i].y);

    sort(q + 1, q + qt + 1);
    for(int i = 1; i <= qt; i ++ )
    {
        while(T < q[i].tim) 
        {
            T ++;
            modify(ch[T].x, ch[T].to);
        }
        while(T > q[i].tim)
        {
            modify(ch[T].x, ch[T].last);
            T --;
        }
        if(L != q[i].x) move(L, q[i].x), L = q[i].x;
        if(R != q[i].y) move(R, q[i].y), R = q[i].y;
        
        int f = lca(L, R);
        
        update(f);
        
        ans[q[i].op] = num;
        update(f);
    }

    for(int i = 1; i <= qt; i ++ ) printf("%lld\n", ans[i]);
    
    return 0;
}
