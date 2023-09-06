#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PII;

using VI = vector<int>;

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
int h[N], e[N], ne[N], w[N], idx;
int n, m;
int minn;
int fa[N];
int a[N];

vector<int> res, buc[N], tmp, que;
bitset<N> vis, done, have;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int find(int x)
{
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

int q[N], hh, tt;

inline void clear()
{
    for(auto w : tmp)
        buc[w].clear(); 
    tmp.clear();
    for(int i = 0; i <= tt; i ++ ) 
        have[a[q[i]]] = false;
    // have.reset();
    que.clear();
}

inline void update()
{
    if(que.size() < minn) res = que, minn = que.size();
    else if(que.size() == minn)
    {
        for(auto v : que)
            res.push_back(v);
    }
}

inline void bfs(int s)
{
    hh = 0, tt = -1;
    q[++ tt] = s;
    while(hh <= tt)
    {
        int u = q[hh ++ ];
        if(find(u) != s)
        {
            fa[s] = find(u);
            vis[find(u)] = true;
            clear();
            return;
        }

        if(vis[u]) continue;
        vis[u] = true;
        que.push_back(u);

        if(!have[a[u]]) 
        {
            have[a[u]] = true;
            for(auto v : buc[a[u]]) q[++ tt] = v;
        }

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(have[w[i]]) q[++ tt] = v;
            else
            {
                tmp.push_back(w[i]);
                buc[w[i]].push_back(v);
            }
        }
    }

    done[s] = 1;
    update();
    clear();
}

VI find_reachable(VI R, VI U, VI V, VI C)
{
    memset(h, -1, sizeof h);

    n = R.size(), m = U.size();
    minn = n + 1;

    for(int i = 0; i < n; i ++ ) a[i + 1] = R[i] + 1;
    for(int i = 0; i < m; i ++ )
    {
        int u = U[i] + 1, v = V[i] + 1, c = C[i] + 1;
        add(u, v, c);
        add(v, u, c);
    }

    for(int i = 1; i <= n; i ++ ) fa[i] = i;

    while(1)
    {
        bool flag = true;
        for(int i = 1; i <= n; i ++ ) vis[i] = 0;
        for(int i = 1; i <= n; i ++ )
            if(find(i) == i && !vis[i] && !done[i])
                bfs(i), flag = false;
        
        if(flag) break;
    }

    VI ans(n);
    for(auto x : res) 
    {
        ans[x - 1] = 1;
        // cout << x << endl;
    }

    // cout << minn << endl;
    return ans;
}

VI R, U, V, C;
signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        R.emplace_back(x);
    }

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        U.emplace_back(a);
        V.emplace_back(b);
        C.emplace_back(c);
    }

    auto ans = find_reachable(R, U, V, C);
    for(auto a : ans)
        printf("%d ", a);

    return 0;
}