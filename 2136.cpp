#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N], cnt[N];
bool st[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int spfa(int s, int t)
{
    queue<int> q;
    q.push(s);
    memset(dist, 0x3f, sizeof dist);
    st[s] = true;
    dist[s] = 0;
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j] >= n) return 1145141919;
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return dist[t];
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, -c);
    }

    int t2 = spfa(1, n);
    int t1 = spfa(n, 1);

    if(t2 == 1145141919) puts("Forever love");
    else cout << min(t1, t2) << endl;
    return 0;
}