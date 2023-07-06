#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int n, m, k;
ll w[N], p[N];
int h[N], e[N], ne[N], id[N], idx;
ll sum;

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

struct ed
{
    int u, v, id;
    bool operator < (const ed & a) const
    {
        return w[u] + w[v] < w[a.u] + w[a.v];
    }
}edge[N];

inline void add(int a, int b, int i)
{
    e[idx] = b, ne[idx] = h[a], id[idx] = i, h[a] = idx ++;
}

bool kruskal()
{
    sort(e + 1, e + m + 1);
    int cnt = n - 1;
    for(int i = 1; i <= m; i ++ )
    {
        int a = edge[i].u, b = edge[i].v, id = edge[i].id;
        if(find(a) == find(b)) continue;
        p[find(a)] = find(b);
        add(a, b, id), add(b, a, id);
        cnt --;
        if(!cnt) return true;
    }
    return false;
}

queue<int> ans1;
stack<int> ans2;
void dfs(int u, int fa, int idd)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u, id[i]);
    }
    if(u == 1) return;
    if(w[u] >= k)
    {
        w[fa] = w[u] + w[fa] - k;
        ans1.push(idd);
    }
    else
    {
        ans2.push(idd);
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

    for(int i = 1; i <= n; i ++ ) 
    {
        w[i] = read(), p[i] = i;
        sum += w[i];
    }
    
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        edge[i] = {a, b, i};
    }

    if(!kruskal() || sum < (ll)(n - 1) * k)
    {
        puts("NO");
        return 0;
    }

    puts("YES");

    dfs(1, 0, 0);

    while(ans1.size()) 
    {
        printf("%d\n", ans1.front());
        ans1.pop();
    }

    while(ans2.size())
    {
        printf("%d\n", ans2.top());
        ans2.pop();
    }

    return 0;
}
