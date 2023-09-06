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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int n, m, k;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int get(int a, int floor)
{
    return a + floor * n;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    dist[1] = 0;

    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int distance = t.first, ver = t.second;
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
        add(a, b, c), add(b, a, c);
        for(int t = 1; t <= k; t ++ )
        {
            add(get(a, t), get(b, t), c);
            add(get(b, t), get(a, t), c);
            add(get(a, t - 1), get(b, t), c / 2);
            add(get(b, t - 1), get(a, t), c / 2);
        }
    }

    for(int i = 0; i < k; i ++ )
        add(get(n, i), get(n, i + 1), 0);

    dijkstra();

    cout << dist[get(n, k)] << endl;
    // cout << dist[n] << endl;
    
    return 0;
}