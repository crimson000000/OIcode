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

const int N = 1e5 + 10;
bool st[2];
unordered_map<ll, int> G;
set<int> unvis;
bitset<N> vis;
int n, m;

inline ll hsh(int a, int b)
{
    return a * N + b;
}

queue<int> q;
int cnt;
vector<int> ans;
inline void find_block()
{
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            cnt ++;
            int res = 1;
            q.push(i);
            unvis.erase(i);
            vis[i] = true;
            while(q.size())
            {
                int u = q.front();
                q.pop();

                for(auto it = unvis.begin(); it != unvis.end(); )
                {
                    int v = *it;
                    it ++;
                    if(G.count(hsh(u, v)) || G.count(hsh(v, u))) continue;
                    unvis.erase(v);
                    res ++;
                    vis[v] = true;
                    q.push(v);
                }
            }
            ans.push_back(res);
        }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        G[hsh(a, b)] = true;
    }

    for(int i = 1; i <= n; i ++ ) unvis.insert(i);

    find_block();
    
    sort(ans.begin(), ans.end());
    printf("%d\n", cnt);
    for(auto a : ans) printf("%d ", a);
    
    // bool ed[2];

    // puts("");
    // printf("%lf\n", (ed - st) * 1.0 / (1 << 20));

    return 0;
}
