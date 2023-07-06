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
int h[N], e[N], ne[N], c[N], idx;
bool vis[N];
int wv[N];
int n, m, l, r;

inline void add(int a, int b, int w)
{
    e[idx] = b, c[idx] = w, ne[idx] = h[a], h[a] = idx ++;
}

int siz[N], maxsize[N];
int rt;
void calc_size(int u, int fa, int sz)
{
    siz[u] = 1, maxsize[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        calc_size(j, u, sz);
        siz[u] += siz[j];
        maxsize[u] = max(maxsize[u], siz[j]);
    }
    maxsize[u] = max(maxsize[u], sz - siz[u]);
    if(maxsize[u] < maxsize[rt]) rt = u;
}

struct tmp
{
    int id, val;
};

struct Monoqueue
{
    tmp q[N];
    int hh, tt;
    inline void clear() {hh = 1, tt = 0;}

    inline bool empty() {return hh > tt;}

    inline tmp top() {return q[hh];}

    inline void pop() {hh ++;}

    inline void push(tmp x)
    {
        while(hh <= tt && q[tt].val <= x.val) tt --;
        q[++ tt] = x;
    }
}q1;

int dep[N];
void getdep(int u, int fa, int len)
{
    dep[u] = len;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        getdep(j, u, len + 1);
        dep[u] = max(dep[u], dep[j]);
    }
}

int col[N], coldep[N];
inline bool cmp(int x, int y)
{
    if(col[x] == col[y]) return dep[x] < dep[y];
    return coldep[col[x]] < coldep[col[y]];
}

int q[N];
bool in_q[N];
int ans1[N], ans2[N], ans[N], sum[N];
int answer = -INF;
int maxx, maxx1, maxx2;
void bfs2(int x)
{
    q1.clear();
    int now = maxx2, hh = 1, tt = 0;
    q[++ tt] = x, in_q[x] = true, dep[x] = 1;
    while(hh <= tt)
    {
        int u = q[hh ++ ];
        while(now > 0 && now + dep[u] >= l) 
        {
            q1.push((tmp){now, ans2[now]});
            now --;
        }
        while(!q1.empty() && dep[u] + q1.top().id > r) q1.pop();
        if(!q1.empty()) ans[u] = sum[u] + q1.top().val - wv[col[x]];
        else ans[u] = -INF;
        answer = max(answer, ans[u]);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(vis[j] || in_q[j]) continue;
            in_q[j] = true;
            dep[j] = dep[u] + 1;
            q[++ tt] = j;
            col[j] = c[i];
            if(col[j] == col[u]) sum[j] = sum[u];
            else sum[j] = sum[u] + wv[c[i]];
        }
    }
    for(int i = now + 1; i <= min(r, dep[q[tt]]); i ++ ) ans2[i] = -INF;
    maxx2 = max(maxx2, min(r, dep[q[tt]]));
    for(int i = 1; i <= tt && dep[q[i]] <= r; i ++ ) 
        ans2[dep[q[i]]] = max(ans2[dep[q[i]]], sum[q[i]]);
    for(int i = 1; i <= tt; i ++ ) in_q[q[i]] = false;
}

int temp[N];
void bfs1(int tot)
{
    if(!tot) return;
    q1.clear();
    int now = maxx1, hh = 1, tt = 0;
    for(int i = 1; i <= tot; i ++ ) q[++ tt] = temp[i], dep[temp[i]] = 1, in_q[temp[i]] = true;
    while(hh <= tt)
    {
        int u = q[hh ++];
        while(now >= 0 && now + dep[u] >= l) 
        {   
            q1.push((tmp){now, ans1[now]});
            now --;
        }
        while(!q1.empty() && q1.top().id + dep[u] > r) q1.pop();
        if(!q1.empty()) ans[u] = sum[u] + q1.top().val;
        else ans[u] = -INF;
        answer = max(answer, ans[u]);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(vis[j] || in_q[j]) continue;
            in_q[j] = true;
            dep[j] = dep[u] + 1;
            q[++ tt] = j;
            col[j] = c[i];
            if(col[j] == col[u]) sum[j] = sum[u];
            else sum[j] = sum[u] + wv[c[i]];
        }
    }
    for(int i = now + 1; i <= min(r, dep[q[tt]]); i ++ ) ans1[i] = -INF;
    maxx1 = max(maxx1, min(r, dep[q[tt]]));
    for(int i = 1; i <= tt && dep[q[i]] <= r; i ++ ) ans1[dep[q[i]]] = max(ans1[dep[q[i]]], sum[q[i]]);
    for(int i = 1; i <= tt; i ++ ) in_q[q[i]] = false;
    maxx2 = 0;
}

int px[N], pxnum;
void dfz(int u)
{
    vis[u] = true;
    // cout << u << endl;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        coldep[c[i]] = 0;
        col[j] = c[i];
    }
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        px[++ pxnum] = j;
        getdep(j, u, 1);
        coldep[c[i]] = max(coldep[c[i]], dep[j]);
    }
    sort(px + 1, px + pxnum + 1, cmp);
    maxx1 = maxx2 = 0;
    int precol = 0, tot = 0;
    ans1[0] = 0;
    for(int i = 1; i <= pxnum; i ++ )
    {
        int v = px[i];
        if(vis[v]) continue;
        if(col[v] != precol) precol = col[v], bfs1(tot), tot = 0;
        sum[v] = wv[col[v]];
        bfs2(v);
        temp[++ tot] = v;
    }
    bfs1(tot);
    pxnum = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        
        if(vis[j]) continue;
        rt = 0;
        maxsize[rt] = INF;
        calc_size(j, -1, siz[j]);
        calc_size(rt, -1, siz[j]);
        dfz(rt);
    }
}

void dfs(int u)
{
    vis[u] = true;
    cout << u << endl;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        dfs(j);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), l = read(), r = read();
    for(int i = 1; i <= m; i ++ ) wv[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), w = read();
        add(a, b, w), add(b, a, w);
    }    

    // for(int u = 1; u <= n; u ++ )
    // {
    //     cout << u << ": ";
    //     for(int i = h[u]; i != -1; i = ne[i])
    //     {
    //         int j = e[i];
    //         cout << j << ' ';
    //     }
    //     puts("");
    // }

    rt = 0;
    maxsize[rt] = INF;
    calc_size(1, -1, n);
    calc_size(rt, -1, n);
    // cout << rt << endl;
    dfz(rt);

    cout << answer << endl;
    
    return 0;
}
