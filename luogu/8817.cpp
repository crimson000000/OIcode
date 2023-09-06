#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e6 + 10, M = 2510;
int h[N], e[N], ne[N], idx;
ll w[N];
int d[M][M];
vector<int> f[M];
ll ans;
int n, m, k;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> q;
bitset<M> ok[M];
inline void bfs(int s, int d[])
{
    q.push(s);
    d[s] = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();

        if(u != s)
        {
            ok[s][u] = true;
            if(s != 1 && ok[1][u])
            {
                f[s].push_back(u);
                sort(f[s].begin(), f[s].end(), [](int x, int y){
                    return w[x] > w[y];
                });
                if(f[s].size() > 3) f[s].pop_back();
            }
        }

        if(d[u] == k + 1) continue;
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(d[v] == 0x3f3f3f3f)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read(), k = read();
    for(int i = 2; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    memset(d, 0x3f, sizeof d);
    for(int i = 1; i <= n; i ++ )
        bfs(i, d[i]);

    for(int b = 2; b <= n; b ++ )
        for(int c = 2; c <= n; c ++ )
        {
            if(!ok[b][c]) continue;
            for(auto a : f[b])
                for(auto d : f[c])
                    if(a != c && b != d && a != d)
                        ans = max(ans, w[a] + w[b] + w[c] + w[d]);
        }

    cout << ans << endl;

    return 0;
}