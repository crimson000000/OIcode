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

const int N = 10010, INF = 0x3f3f3f3f;
ll h[N], e[N], ne[N], w[N], idx;
ll d[N], pre[N], incf[N];
bool st[N];
int n, m, s, t;
ll flow;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

bool bfs()
{
    memset(st, 0, sizeof st);
    queue<int> q;
    q.push(s);
    st[s] = true;
    incf[s] = INF;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for(int i = h[x]; i != -1; i = ne[i])
        {
            if(w[i])
            {
                int j = e[i];
                if(st[j]) continue;
                incf[j] = min(w[i], incf[x]);
                pre[j] = i;
                q.push(j);
                st[j] = 1;
                if(j == t) return true;
            }
        }
    }
    return false;
}

void update()
{
    int x = t;
    while(x != s)
    {
        int i = pre[x];
        w[i] -= incf[t];
        w[i ^ 1] += incf[t];
        x = e[i ^ 1];
    }
    flow += incf[t];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    
    n = read(), m = read(), s = read(), t = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }
    
    while(bfs()) update();

    cout << flow << endl;

    return 0;
}
