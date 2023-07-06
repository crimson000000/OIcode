#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> PII;
const int N = 1e5 + 10, M = 4e5 + 10;
int h[N], e[M], ne[M], idx;
ll dist[N], w[N], d[N];
bool st[N], danger[N], zom[N];
int n, m, k, s;
ll p, q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void bfs()
{
    queue<int> q;
    for(int i = 1; i <= n; i ++ )
        if(zom[i]) q.push(i);

    while(!q.empty())
    {
        int t = q.front();
        q.pop();

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(d[j]) continue;
            d[j] = d[t] + 1;
            if(d[j] <= s) {
                danger[j] = true;
                q.push(j);
            }
        }
    }
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int ver = t.second; 
        ll distance = t.first;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(zom[j]) continue;
            if(dist[j] > dist[ver] + w[j])
            {
                dist[j] = dist[ver] + w[j];
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d%lld%lld", &n, &m, &k, &s, &p, &q);
    memset(h, -1, sizeof h);

    while(k -- )
    {
        int a;
        scanf("%d", &a);
        danger[a] = true;
        zom[a] = true;
    }

    while(m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    bfs();

    for(int i = 2; i < n; i ++ )
        if (danger[i]) w[i] = q;
        else w[i] = p;

    w[1] = w[n] = 0;

//    for(int i = 1; i <= n; i ++ ) printf("%d : %d\n", i, w[i]);
    
    dijkstra();

    cout << dist[n] << endl;

    return 0;
}