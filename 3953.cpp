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
int h[N], e[N], ne[N], w[N], idx;
int hs[N];
int dist[N];
int n, m, K, mod;

inline void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

priority_queue<PII, vector<PII>, greater<PII>> heap;
bitset<N> st;

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    st.reset();
    dist[1] = 0;
    heap.push({0, 1});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second;
        if(st[ver]) continue;
        st[ver] = true;
        
        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

int f[N >> 2][55];
bool flag;
bitset<55> vis[N];
int dp(int v, int k)
{
    if(k > K || k < 0) return 0;
    if(f[v][k] != -1) return f[v][k];
    f[v][k] = 0;
    vis[v][k] = true;
    for(int i = hs[v]; i != -1; i = ne[i])
    {
        int u = e[i];
        int x = dist[v] + k - w[i] - dist[u];
        if(x < 0 || x > K) continue;
        if(vis[u][x]) flag = true;
        f[v][k] = (f[v][k] + dp(u, x)) % mod;
    }
    vis[v][k] = false;
    return f[v][k];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        idx = 0;
        memset(h, -1, sizeof h);
        memset(hs, -1, sizeof hs);
        memset(f, -1, sizeof f);
        flag = false;

        n = read(), m = read(), K = read(), mod = read();

        for(int i = 1; i <= n; i ++ ) vis[i].reset();

        for(int i = 1; i <= m; i ++ )
        {
            int a = read(), b = read(), c = read();
            add(h, a, b, c);
            add(hs, b, a, c);
        }

        dijkstra();
        
        int ans = 0;
        for(int i = 0; i <= K; i ++ ) dp(n, i);

        if(flag)
        {
            puts("-1");
            continue;
        }

        memset(f, -1, sizeof f);
        f[1][0] = 1;

        for(int i = 0; i <= K; i ++ )
            ans = (ans + dp(n, i)) % mod;
        
        cout << ans << endl;
    }

    return 0;
}