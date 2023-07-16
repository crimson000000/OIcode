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

const int N = 210, S = 1 << 13;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int h[N], e[N << 5], ne[N << 5], idx;
int a[N];
int f[S][N];
PII pre[S][N];
int key[N];
int n, m, K;
int ans[N][N];

inline int id(int x, int y)
{
    return (x - 1) * m + y;
}

inline PII get(int id)
{
    int x = id / m + 1, y = id % m;
    if(!y) y += m, x --;
    return {x, y};
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> q;
bitset<N> st;

void spaf(int s)
{
    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(f[s][v] > f[s][u] + a[v])
            {
                f[s][v] = f[s][u] + a[v];
                pre[s][v] = {s, u};
                if(!st[v])
                {
                    st[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

void dfs(int s, int id)
{
    if(!pre[s][id].first) return;
    auto t = get(id);
    ans[t.first][t.second] = 1;
    if(pre[s][id].second == id)
        dfs(s ^ pre[s][id].first, id);
    dfs(pre[s][id].first, pre[s][id].second);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    memset(f, 0x3f, sizeof f);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            a[id(i, j)] = read();
            if(!a[id(i, j)])
            {
                key[K] = id(i, j);
                f[(1 << K)][key[K]] = 0;
                K ++;
            }
        }

    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= m; j ++ )
            for(int k = 0; k < 4; k ++ )
            {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || x > n || y < 1 || y > m) continue;
                add(id(i, j), id(x, y));
            }
    
    for(int s = 1; s < (1 << K); s ++ )
    {
        for(int i = 1; i <= n * m; i ++ )
        {
            for(int st = s & (s - 1); st; st = s & (st - 1))
                if(f[s][i] > f[st][i] + f[s ^ st][i] - a[i])
                {
                    f[s][i] = f[st][i] + f[s ^ st][i] - a[i];
                    pre[s][i] = {st, i};
                }

            if(f[s][i] != 0x3f3f3f3f)
            {
                q.push(i);
                st[i] = true;
            }
        }

        spaf(s);
    }

    if(K) cout << f[(1 << K) - 1][key[0]] << endl;
    else puts("0");
    dfs((1 << K) - 1, key[0]);
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
        {
            if(!a[id(i, j)]) putchar('x');
            else if(ans[i][j]) putchar('o');
            else putchar('_');
        }
        puts("");
    }

    return 0;
}
