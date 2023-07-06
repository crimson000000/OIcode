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

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
int dep[N];
bitset<N> vis;
int n;
int ans;

struct cmp
{
    bool operator () (int &a, int &b) const 
    {
        return dep[a] < dep[b];
    }
};

priority_queue<int, vector<int>, cmp> heap;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++; 
}

int fa[N];
inline void dfs(int u, int f, int d)
{
    dep[u] = d;
    fa[u] = f;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs(v, u, d + 1);
    }
}

inline void clear(int u, int d)
{
    if(d > 2) return;
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        clear(e[i], d + 1);
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
    for(int i = 2; i <= n; i ++ )
    {
        int x = read();
        add(i, x), add(x, i);
    }

    dfs(1, 1, 0);
    for(int i = 1; i <= n; i ++ )
        heap.push(i);
    
    while(heap.size())
    {
        int x;
        while(heap.size() && vis[heap.top()]) heap.pop();
        if(!heap.size()) break;
        x = heap.top();
        clear(fa[fa[x]], 0);
        ans ++;
    }

    cout << ans << endl;

    return 0;
}