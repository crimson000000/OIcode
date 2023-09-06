#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int h[N], ne[N], w[N], e[N], idx;
double rec[N];
int dist[N];
bool st[N];
int n, m, s;

void add(int a, int b, int c, double d)
{
    e[idx] = b, w[idx] = c, rec[idx] = d, ne[idx] = h[a], h[a] = idx ++;
}

void spfa()
{
    queue<int> q;
    q.push(s);
    st[s] = true;
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                w[i] *= rec[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while(m -- )
    {
        int a, b, c;
        double d;
        cin >> a >> b >> c >> d;
        add(a, b, c, d);
    }

    cin >> s;
    spfa();
    int res = 0;
    for(int i = 1; i <= n; i ++ ) res = max(res, dist[i]);
    cout << res << endl;
    return 0;
}