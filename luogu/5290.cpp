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
int h[N], e[N], ne[N], idx;
int v[N];
vector<int> o;
priority_queue<int> heap[N];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void merge(int x, int y)
{
    if(heap[x].size() < heap[y].size()) swap(heap[x], heap[y]);
    while(heap[y].size())
    {
        o.push_back(max(heap[x].top(), heap[y].top()));
        heap[x].pop(), heap[y].pop();
    }
    while(o.size()) heap[x].push(o.back()), o.pop_back();
}

void dfs(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        merge(u, j);
    }
    heap[u].push(v[u]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= n; i ++ ) v[i] = read();
    for(int i = 2; i <= n; i ++ ) 
    {
        int x = read();
        add(x, i);
    }

    dfs(1);
    

    ll ans = 0;
    while(heap[1].size())
    {
        ans += heap[1].top();
        heap[1].pop();
    }

    cout << ans << endl;

    return 0;
}
