#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
int f[N], sum[N];
int fa[N];
bitset<N> tag;
int n, st, rt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void dfs(int u, int fat)
{
    fa[u] = fat;
    int son = 0;
    for(int i = h[u]; i != -1; i = ne[i]) 
        if(e[i] != fat)
            son ++;
    sum[u] = sum[fat] + son - 1 + (u == st);
    int max1 = 0, max2 = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fat) continue;
        dfs(v, u);
        if(f[v] > max1) max2 = max1, max1 = f[v];
        else if(f[v] > max2) max2 = f[v];
    }
    f[u] = max2 + son;
}

inline bool check(int mid)
{
    int cnt = 1;
    for(int u = st; u != rt; u = fa[u], cnt ++ )
    {
        int tmp = 0;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(tag[v] || f[v] + sum[u] <= mid) continue;
            if(!cnt) return false;
            cnt --;
            tmp ++;
        }
        mid -= tmp;
    }
    return mid >= 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), rt = read(), st = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs(rt, 0);

    for(int i = st; i; i = fa[i]) tag[i] = true;

    int l = 0, r = 1e7;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(mid)) r = mid - 1;
        else l = mid;
    }

    cout << l << endl;
    
    return 0;
}