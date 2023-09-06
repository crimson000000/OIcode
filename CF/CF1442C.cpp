#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long, int> PII;

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

const int N = 1e7 + 10, mod = 998244353, M = 10000000;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int a[N], b[N];
int h[N], e[N], ne[N], w[N], idx;
ll dist[N];
bool st[N];
int n, m;

void init()
{
    memset(h, -1, sizeof h);
    memset(st, 0, sizeof st);
    idx = 0;
}

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int get(int x, int floor)
{
    return x + floor * n;
}

void build1(int floor, int p)
{
    for(int i = 1; i <= m; i ++ )
    {
        if(p == 1) add(get(a[i], floor), get(b[i], floor), 1);
        else add(get(b[i], floor), get(a[i], floor), 1);
    }
}

void build2(int floor, int nxtf, int cost)
{
    for(int i = 1; i <= n; i ++ )
        add(get(i, floor), get(i, nxtf), cost);
}

void dijkstra(int u)
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, u});
    dist[u] = 0;

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        ll distance = t.first;
        int ver = t.second;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

ll qmi(ll a, ll k)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
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
        a[i] = read(), b[i] = read();

    for(int i = 1; i <= 21; i ++ )
    {
        if(i & 1) build1(i - 1, 1);
        else build1(i - 1, -1);
    }

    for(int i = 0; i <= 19; i ++ )
        build2(i, i + 1, 1 << i);

    dijkstra(1);

    ll ans1 = INF;
    for(int i = 0; i <= 19; i ++ )
        ans1 = min(ans1, dist[get(n, i)]);

    init();
    build1(0, 1);
    build1(1, -1);
    build2(0, 1, M);
    build2(1, 0, M);

    dijkstra(1);

    ll ans2 = 0;
    ll k = min(dist[n], dist[n * 2]);
    // cout << dist[n] << ' ' << dist[n * 2] << endl;
    // cout << 0x3f3f3f3f3f3f3f3f << endl;
    // cout << INF % mod << endl;

    if(k / M > 19)
    {
        ans2 = (qmi(2, k / M) + k % M - 1 + mod) % mod;
        cout << ans2 << endl;
    }
    else
    {
        ans2 = ((1ll << (k / M)) + k % M - 1);
        cout << min(ans2, ans1) % mod << endl;
    }
    
    return 0;
}
