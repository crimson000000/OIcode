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
struct edge
{
    int a, b, c;
    bool operator < (const edge& e) const
    {
        return c < e.c;
    }
}ed[N];
set<int> G[N], unvis;
bitset<N> vis;
int n, m;
ll reblo;
queue<int> q;
int type[N];
ll ans;
int x;

struct UniSet
{
    int fa[N];
    inline int find(int x)
    {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }
}uni;

inline void find_block()
{
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            q.emplace(i);
            vis[i] = true;
            unvis.erase(i);
            uni.fa[i] = i;
            while(q.size())
            {
                int u = q.front();
                q.pop();

                for(auto it = unvis.begin(); it != unvis.end();)
                {
                    int v = *it;
                    it ++;
                    if(G[u].count(v)) continue;
                    uni.fa[v] = u;
                    unvis.erase(v);
                    vis[v] = true;
                    q.emplace(v);
                    reblo --;
                }
            }
        }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    reblo = (ll)n * (n - 1) / 2 - m;

    for(int i = 1; i <= n; i ++ ) unvis.insert(i);

    for(int i = 1; i <= m; i ++ )
    {
        ed[i].a = read(), ed[i].b = read(), ed[i].c = read();
        G[ed[i].a].insert(ed[i].b);
        G[ed[i].b].insert(ed[i].a);
        x ^= ed[i].c;
    }

    find_block();

    sort(ed + 1, ed + m + 1);

    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(uni.find(a) == uni.find(b)) continue;
        uni.fa[uni.find(a)] = uni.find(b);
        ans += c;
        type[i] = 1;
    }

    if(reblo > 0)
    {
        printf("%lld\n", ans);
        return 0;
    }

    for(int i = 1; i <= n; i ++ ) uni.fa[i] = i;

    int minn = 0x3f3f3f3f;
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(uni.find(a) == uni.find(b)) continue;
        uni.fa[uni.find(a)] = uni.find(b);
        if(!type[i]) 
        {
            minn = c;
            break;
        }
    }

    printf("%lld\n", ans + min(x, minn));

    return 0;
}
