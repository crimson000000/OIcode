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

const int N = 1e5 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N], cnt[N];
bool st[N];
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int v, int fa)
{
    st[v] = true;
    for(int i = h[v]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || st[j]) continue;
        st[j] = true;
        dfs(j, v);
    }
}

bool spfa()
{
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    for(int i = 1; i <= n; i ++ )
    {
        if(!st[i])
        {
            dfs(i, 0);
            q.push(i);
            dist[i] = 0;
            st[i] = true;
        }
    }
    memset(st, 0, sizeof st);
    while(!q.empty())
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
                if(cnt[j] >= n) return false;
                if(!st[j])
                {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();
    memset(h, -1, sizeof h); 

    while(m -- ) 
    {
        int a = read(), b = read(), c = read();
        add(b, a, c);
    }

    if(!spfa()) puts("NO");
    else
    {
        for(int i = 1; i <= n; i ++ ) cout << dist[i] << " ";
        puts("");
    }

    return 0;
}
