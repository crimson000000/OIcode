#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bitset<N> st;
queue<int> q;
int n, m;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int cnt[N];
inline bool spaf(int s)
{
    memset(dist, 0x3f, sizeof dist);
    st[s] = true;
    q.push(s);
    dist[s] = 0;
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
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > n) return false;
                if(!st[v])
                {
                    st[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
} 

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) 
    {
        int a = read(), b = read(), c = read();
        add(b, a, c);
    }

    for(int i = 1; i <= n; i ++ ) add(0, i, 0);

    if(!spaf(0)) puts("NO");
    else 
    {
        for(int i = 1; i <= n; i ++ ) printf("%d ", dist[i]);
    }

    return 0;
}
