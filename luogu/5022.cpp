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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int n, m;

bitset<N> st;
struct per
{
    int a[5010], tt;
    per()
    {
        tt = 0;
        memset(a, 0, sizeof a);
    }
    bool operator < (const per &t) const
    {
        for(int i = 1; i <= n; i ++ )
            if(a[i] != t.a[i])
                return a[i] < t.a[i];
        return false;
    }
};
vector<per> ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace tree
{
    void dfs(int u, int f)
    {
        printf("%d ", u);
        priority_queue<int, vector<int>, greater<int>> heap;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            heap.push(v);
        }
        while(heap.size())
        {
            int v = heap.top();
            heap.pop();
            dfs(v, u);
        }
    }
}

int pre[N];
bitset<N> vis;
bool flag;
int sta, ed;
vector<int> cir;

void find_circle(int u, int f)
{
    pre[u] = f;
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        if(vis[v]) 
        {
            sta = u, ed = v;
            flag = true;
            return;
        }
        find_circle(v, u);
        if(flag) return;
    }
}

void dfs(int u, int f, per& a)
{
    a.a[++ a.tt] = u;
    priority_queue<int, vector<int>, greater<int>> heap;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        if(v == sta && u == ed) continue;
        if(v == ed && u == sta) continue;
        heap.push(v);
    }
    while(heap.size())
    {
        int v = heap.top();
        heap.pop();
        dfs(v, u, a);
    }
}

void solve()
{
    for(int i = 0; i < cir.size(); i ++ )
    {
        sta = cir[i], ed = cir[(i + 1) % cir.size()];
        per a;
        dfs(1, 1, a);
        ans.push_back(a);
    }
    sort(ans.begin(), ans.end());
    for(int i = 1; i <= n; i ++ ) printf("%d ", ans[0].a[i]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    if(m == n - 1) tree::dfs(1, 1);
    else
    {
        find_circle(1, 0);
        int _u = sta;
        while(_u != ed)
        {
            cir.push_back(_u);
            _u = pre[_u];
        }

        cir.push_back(ed);
        // for(auto u : cir)
        //     printf("%d ", u);

        solve();
    }

    return 0;
}