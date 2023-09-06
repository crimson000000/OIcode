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

const int N = 20010 + 10, M = 4e5 + 10;
int h[N], e[M], ne[M], w[M], idx;
int dist[30][20010];
int f[2][21][200010];
int n, m, k, q;
int mp[N], ump[N], tot;
int now, cur;
int mmp[2][(1 << 21)], tt[2];
vector<int> pre[N], state[22];
int ans = 0x3f3f3f3f;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int popcount(int x)
{
    int cnt = 0;
    while(x)
    {
        x -= (x & -x);
        cnt ++;
    }
    return cnt;
}

priority_queue<PII, vector<PII>, greater<PII>> heap;
bitset<N> st;
inline void dijkstra(int s, int dist[])
{
    while(heap.size()) heap.pop();
    st.reset();
    for(int i = 1; i <= n; i ++ ) dist[i] = 0x3f3f3f3f;
    
    heap.push({0, s});
    dist[s] = 0;

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        int u = t.second;
        if(st[u]) continue;
        st[u] = true;

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + w[i])
            {
                dist[v] = dist[u] + w[i];
                heap.push({dist[v], v});
            }
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), k = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    q = read();

    for(int i = 1; i <= q; i ++ ) 
    {
        int u = read(), v = read();
        pre[v].emplace_back(u);
    }

    for(int i = 2; i <= k + 1; i ++ )
    {
        ump[tot] = i;
        mp[i] = tot ++;
        dijkstra(i, dist[mp[i]]);
    }

    // cout << tot << endl;

    for(int i = 1; i < (1 << tot); i ++ ) 
        state[popcount(i)].push_back(i);

    dijkstra(1, dist[25]);

    if(k == 0)
    {
        printf("%d\n", dist[25][n]);
        return 0;
    }

    now = 0, cur = 1;
    for(auto s : state[1])
        mmp[now][s] = tt[now] ++;

    memset(f, 0x3f, sizeof f);
    for(int i = 0; i < tot; i ++ )
    {
        int u = ump[i];
        if(u == n || !pre[u].size()) 
            f[now][i][mmp[now][1 << i]] = dist[25][u];
    }

    for(int siz = 1; siz < tot; siz ++ )
    {
        swap(now, cur);
        tt[now] = 0;
        for(auto s : state[siz + 1])
            mmp[now][s] = tt[now] ++;
        
        memset(f[now], 0x3f, sizeof f[now]);
        
        for(auto s : state[siz])
        {
            for(int i = 0; i < tot; i ++ )
            {
                bool flag = false;
                int v = ump[i];
                if(s >> i & 1) continue;
                for(auto p : pre[v])
                    if(!(s >> mp[p] & 1))
                        flag = true;

                if(flag) continue;

                int T = s | (1 << i);

                for(int j = 0; j < tot; j ++ )
                {
                    if(!(s >> j & 1)) continue;
                    
                    f[now][i][mmp[now][T]] = min(f[now][i][mmp[now][T]], 
                                    f[cur][j][mmp[cur][s]] + dist[j][v]);
                }

                if(T == (1 << tot) - 1) 
                    ans = min(ans, f[now][i][mmp[now][T]] + dist[i][n]);
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}
