#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

template <typename T>
inline T read()
{
    T x = 0, f = 1;
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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
ll w[N], dist[N];
bool on_tree[N], vis[N];
ll n, m, ans;

void add(int a, int b, ll c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u)
{
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        on_tree[i] = on_tree[i ^ 1] = true;
        dist[j] = dist[u] ^ w[i];
        dfs(j);
    }
}

ll d[100];
void insert(ll x)
{
    for(int i = 62; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                d[i] = x;
                break;
            }
            x ^= d[i];
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

    n = read<int>(), m = read<int>();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read<int>(), b = read<int>();
        ll c = read<ll>();
        add(a, b, c);
        add(b, a, c);
    }

    dfs(1);

    for(int i = 0; i < idx; i ++ )
    {
        if(on_tree[i]) continue;
        int u = e[i], v = e[i ^ 1];
        ll val = w[i];
        insert(val ^ dist[u] ^ dist[v]);
    }
    
    ans = dist[n];
    for(int i = 62; i >= 0; i -- )
        ans = max(ans, ans ^ d[i]);
    
    cout << ans << endl;
    
    return 0;
}
