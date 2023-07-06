#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int N = 2010;
int h[N], e[N], ne[N], idx;
int n, start, ed;
int dist[N];
bool st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra(int s)
{
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    heap.push({0, s});
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
            if(dist[j] > distance + 1)
            {
                dist[j] = distance + 1;
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &start, &ed);

    for(int i = 1; i <= n; i ++ )
    {
        int h;
        scanf("%d", &h);
        if(i + h <= n) add(i, i + h);
        if(i - h > 0) add(i, i - h);
    }

    dijkstra(start);
    if(dist[ed] > 10000000) cout << -1 << endl;
    else cout << dist[ed] << endl;
}