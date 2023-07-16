#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 4010, S = 1 << 12;
int h[N], e[N << 2], ne[N << 2], w[N << 2], idx;
int f[S][N];
int ans[S];
int n, m, k;
int key[N];
vector<int> b[N];

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

queue<int> q;
bitset<N> st;
inline void spaf(int dist[])
{
    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + w[i])
            {
                dist[v] = dist[u] + w[i];
                if(!st[v])
                {
                    q.push(v);
                    st[v] = true;
                }
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
    memset(f, 0x3f, sizeof f);
    memset(ans, 0x3f, sizeof ans);

    n = read(), m = read(), k = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    for(int i = 1; i <= k; i ++ )
    {
        int c = read();
        key[i] = read();
        b[c].push_back(i - 1);
        f[(1 << i - 1)][key[i]] = 0;
    }

    for(int s = 1; s < (1 << k); s ++ )
    {
        for(int i = 1; i <= n; i ++ )
        {
            for(int st = s & (s - 1); st; st = (st - 1) & s)
                f[s][i] = min(f[s][i], f[st][i] + f[s ^ st][i]);

            if(f[s][i] != 0x3f3f3f3f)
            {
                q.push(i);
                st[i] = true;
            }
        }

        spaf(f[s]);
    }

    // cout << f[(1 << k) - 1][key[1]] << endl;

    for(int s = 0; s < (1 << k); s ++ )
    {
        bool flag = true;
        for(int i = 1; i <= k; i ++ )
        {
            if(b[i].size() < 2) continue;
            for(int j = 1; j < b[i].size(); j ++ )
            {
                int u = b[i][j - 1], v = b[i][j];
                if((s >> u & 1) ^ (s >> v & 1)) flag = false;
            }
        }

        if(!flag) continue;
        for(int i = 1; i <= n; i ++ )
            ans[s] = min(ans[s], f[s][i]);
    }

    for(int s = 1; s < (1 << k); s ++ )
        for(int st = s & (s - 1); st; st = (st - 1) & s)
            ans[s] = min(ans[s], ans[st] + ans[s ^ st]);

    cout << ans[(1 << k) - 1] << endl;
    
    return 0;
}
