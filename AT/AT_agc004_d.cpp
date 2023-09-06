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
int to[N];
int h[N], e[N], ne[N], idx;
vector<int> cir;
int n, k;
int cnt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfs(int u, int fa, int dep)
{
    int res = dep;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        res = max(res, dfs(j, u, dep + 1));
    }
    if(to[u] != 1 && res - dep == k - 1)
    {
        cnt ++;
        return 0;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) to[i] = read();

    if(to[1] != 1) cnt ++, to[1] = 1;

    for(int i = 2; i <= n; i ++ )
    {
        add(i, to[i]);
        add(to[i], i);
    }

    dfs(1, 0, 0);

    cout << cnt << endl;

    return 0;
}