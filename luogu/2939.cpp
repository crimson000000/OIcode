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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int n, m, k;

inline int get(int a, int floor)
{
    return a + floor * n;
}

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read(), k = read();
    while(m -- )
    {
        int a = read(), b = read(), c = read();
        for(int i = 0; i <= k; i ++ )
            add(get(a, i), get(b, i), c), add(get(b, i), get(a, i), c);
        for(int i = 0; i < k; i ++ )
            add(get(a, i), get(b, i + 1), 0), add(get(b, i), get(a, i + 1), 0);
    }

    for(int i = 0; i < k; i ++ )
        add(get(n, i), get(n, i + 1), 0);

    dijkstra();

    int ans = 0x3f3f3f3f;
    for(int i = 0; i <= k; i ++ ) ans = min(ans, dist[get(n, i)]);
    cout << ans << endl;
    
    return 0;
}
