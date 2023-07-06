#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second

typedef pair<int, int> PII;
typedef pair<double, int> PID;
const int N = 1e5 + 10;
const double eps = 1e-15;
int n, m, s, t;
int h[N], e[N], ne[N], idx;
double w[N];
int pre[N];
double dist[N];
bool st[N];
PII q[N];

struct Ver
{
    int type, ver;
    double distance;
    bool operator > (const Ver& W) const
    {
        return distance > W.distance;
    }
};

double get_dist(PII a, PII b)
{
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt((double)dx * dx + dy * dy);
}

void add(int a, int b, double c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra(int x, int y)
{
    for(int i = 0; i <= N; i ++ ) dist[i] = 1e20;

    priority_queue<PID, vector<PID>, greater<PID>> heap;
    memset(st, 0, sizeof st);
    dist[1] = 0;
    heap.push({0.0, 1});

    while(!heap.empty())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second; 
        double distance = t.first;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if((ver == x && j == y) || (ver == y && j == x))
                continue;
            if(dist[j] > distance + w[i])
            {
                if(x == -1 && y == -1) pre[j] = ver;
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i ++ ) scanf("%d%d", &q[i].x, &q[i].y);

    while(m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        
        double c = get_dist(q[a], q[b]);
        add(a, b, c), add(b, a, c);
//        printf("%d and %d : %lf\n", a, b, c);
    }

    dijkstra(-1, -1);
    double ans = 1e20;
    for(int i = n; i != 1; i = pre[i])
    {
        dijkstra(i, pre[i]);
        ans = min(ans, dist[n]);
    }

    if(ans > 1e10) cout << -1 << endl;
    else printf("%.2f\n", ans);

    return 0;
}