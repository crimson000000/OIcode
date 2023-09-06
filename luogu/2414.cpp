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
char s[N], t[N];
int m, n;

struct query
{
    int x, i;
};
vector<query> q[N];
int tr[N][26], fail[N], idx;
int fa[N], a[N];
int h[N], e[N], ne[N], cnt;
int ans[N];

inline void insert(char *s)
{
    int len = strlen(s + 1);
    int p = 0;
    for(int i = 1; i <= len; i ++ )
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            int u = s[i] - 'a';
            if(!tr[p][u]) tr[p][u] = ++ idx, fa[idx] = p;
            p = tr[p][u];
        }
        if(s[i] == 'P') a[++ n] = p;
        if(s[i] == 'B') p = fa[p];
    }
} 

void add(int a, int b)
{
    ++ cnt;
    e[cnt] = b, ne[cnt] = h[a], h[a] = cnt;
}

int Index;
int out[N], dfn[N];
void dfs(int u, int f)
{
    dfn[u] = ++ Index;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs(j, u);
    }
    out[u] = Index;
}

queue<int> qq;
void build()
{
    for(int i = 0; i < 26; i ++ )
        if(tr[0][i])
            qq.push(tr[0][i]);
    while(qq.size())
    {
        int u = qq.front();
        qq.pop();
        for(int i = 0; i < 26; i ++ )
        {
            int v = tr[u][i];
            if(!v) tr[u][i] = tr[fail[u]][i];
            else 
            {
                fail[v] = tr[fail[u]][i];
                qq.push(v);
            }
        }
    }

    for(int i = 1; i <= idx; i ++ )
        add(i, fail[i]), add(fail[i], i);
    dfs(0, 0);
}

struct bitarray
{
    int c[N];
    #define lowbit(x) x & -x
    
    inline void add(int x, int val)
    {
        for(; x <= Index; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    scanf("%s", s + 1);
    int len = strlen(s + 1);
    insert(s);
    build();
    m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read();
        q[y].push_back({x, i});
    }

    for(int i = 1, j = 0, p = 0; i <= len; i ++ )
    {
        if(s[i] == 'P')
        {   
            j ++;
            for(auto t : q[j])
            {
                int x = t.x, id = t.i;
                ans[id] = bit.query(out[a[x]]) - bit.query(dfn[a[x]] - 1);
            }
        }
        else if(s[i] == 'B')
        {
            bit.add(dfn[p], -1);
            p = fa[p];
        }
        else
        {
            p = tr[p][s[i] - 'a'];
            bit.add(dfn[p], 1);
        }
    }

    for(int i = 1; i <= m; i ++ ) printf("%d\n", ans[i]);

    return 0;
}
