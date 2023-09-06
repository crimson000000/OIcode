#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
int tr[N][26], fail[N];
int idx, val[N], node[N];
char s[N], t[N];
vector<int> G[N];
bitset<N> del;
int n, m;

struct ta
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int v)
    {
        for(; x < N; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    inline void exadd(int l, int r, int v)
    {
        add(l, v), add(r + 1, -v);
    }
}bit;

inline void insert(char *s, int id)
{
    int p = 0;
    for(int i = 1; s[i]; i ++ )
    {
        int u = s[i] - 'a';
        if(!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    }
    val[p] ++;
    node[id] = p;
}

queue<int> q;
inline void build()
{
    for(int i = 0; i < 26; i ++ )
        if(tr[0][i])
            q.push(tr[0][i]);
    
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < 26; i ++ )
        {
            int v = tr[u][i];
            if(!v) tr[u][i] = tr[fail[u]][i];
            else
            {
                fail[v] = tr[fail[u]][i];
                val[v] += val[fail[v]];
                q.push(v);
            }
        }
    }

    for(int i = 1; i <= idx; i ++ ) G[fail[i]].push_back(i);
}

int L[N], R[N], tim;
inline void dfs(int u)
{
    L[u] = ++ tim;
    for(auto v : G[u]) dfs(v);
    R[u] = tim;
}

inline void init()
{
    for(int i = 1; i <= idx; i ++ )
    {
        bit.exadd(L[i], L[i], val[i]);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = read();
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", t + 1);
        insert(t, i);
    }

    build();
    dfs(0);
    init();

    while(m -- )
    {
        scanf("%s", s);
        if(s[0] == '+')
        {
            int x = 0;
            for(int i = 1; s[i]; i ++ )
                x = x * 10 + s[i] - '0';
            int u = node[x];
            if(!del[x]) continue;
            del[x] = 0;
            bit.exadd(L[u], R[u], 1);
        }
        else if(s[0] == '-')
        {
            int x = 0;
            for(int i = 1; s[i]; i ++ )
                x = x * 10 + s[i] - '0';
            int u = node[x];
            if(del[x]) continue;
            del[x] = 1;
            bit.exadd(L[u], R[u], -1);
        }
        else
        {
            int p = 0, ans = 0;
            for(int i = 1; s[i]; i ++ )
            {
                int c = s[i] - 'a';
                p = tr[p][c];
                ans += bit.query(L[p]);
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}