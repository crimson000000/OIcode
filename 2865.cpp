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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e5 + 10;
int h[N], e[N], ne[N], w[N], idx;
ll dist[N][2];
bool st[N][2];
int n, m;

struct node
{
    ll dis;
    int ver, type;
    bool operator > (const node &W) const 
    {
        return dis > W.dis;
    }
};

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra()
{
    priority_queue<node, vector<node>, greater<node>> heap;
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1][0] = 0;
    heap.push({0, 1, 0});

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        ll distance = t.dis;
        int ver = t.ver, type = t.type;
        if(st[ver][type]) continue;
        st[ver][type] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j][0] > distance + w[i])
            {
                dist[j][1] = dist[j][0];
                dist[j][0] = distance + w[i];
                heap.push({dist[j][0], j, 0});
                heap.push({dist[j][1], j, 1});
            }
            else if(dist[j][1] > distance + w[i])
            {
                dist[j][1] = distance + w[i];
                heap.push({dist[j][1], j, 1});
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
    scanf("%d%d", &n, &m);

    while(m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    dijkstra();

    cout << dist[n][1] << endl;

    return 0;
}