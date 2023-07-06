#include <bits/stdc++.h>
#define LOCAL
using namespace std;
const int N = 4e6 + 10;
int h[N], e[N], ne[N], idx;
int a[N], pre[N];
int dist[N];
bool prime[N], st[N];
int n, s, t;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void build()
{
    for(int i = 1; i <= n; i ++ )
    {
        int t = a[i];
        for(int j = 2; j <= t / j; j ++ )
        {
            if(t % j == 0)
            {
                add(i, n + j), add(n + j, i);
            }
            while(t % j == 0) t /= j;
        }
        if(t > 1) add(i, n + t), add(n + t, i);
    }
}

void bfs(int s)
{
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    q.push(s);
    dist[s] = 1;
    while(q.size())
    {
        int t = q.front();
        q.pop();

        if(st[t]) continue;
        st[t] = true;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + 1)
            {
                dist[j] = dist[t] + 1;
                pre[j] = t;
                q.push(j);
            }
        }
    }
}

void print(int t)
{
    if(!t) return;
    print(pre[t]);
    if(t <= n) cout << t << ' ';
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif


    scanf("%d", &n);
    memset(h, -1, sizeof h);
     
    for(int i = 1; i <= n; i ++ )
        scanf("%d", &a[i]);
    
    scanf("%d%d", &s, &t);

    build();

    bfs(s);
    if(dist[t] == 0x3f3f3f3f) puts("-1");
    else
    {
        cout << dist[t] / 2 + 1 << endl;
        print(t);
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}