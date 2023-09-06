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

const int N = 1e6 + 10, mod = 1e9 + 7;
const int M = 1e5 + 10, B = 380;
int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];

struct base
{
    int a[6];
    base() {memset(a, 0, sizeof a);}

    inline bool insert(int x)
    {
        for(int i = 4; i >= 0; i -- )
        {
            if(!(x >> i & 1)) continue;
            if(!a[i])
            {
                a[i] = x;
                for(int j = 0; j < i; j ++ ) if(a[i] >> j & 1) a[i] ^= a[j];
                for(int j = i + 1; j <= 4; j ++ ) if(a[j] >> i & 1) a[j] ^= a[i];
                return true;
            }
            else x ^= a[i];
        }
        return false;
    }

    inline int hash()
    {
        return ((a[4] << 10) | (a[3] << 6) | (a[2] << 3) | (a[1] << 1) | a[0]);
    }
}b[N], c[N], emp;
int trans[514][514];

int hsh[N], num;
inline void dfs_base(base x)
{
    int hs = x.hash();
    // cout << hs << endl;
    if(hsh[hs]) return;
    hsh[hs] = ++ num;
    b[num] = x;
    for(int i = 1; i <= 31; i ++ )
    {
        base tmp = x;
        if(tmp.insert(i))
            dfs_base(tmp);
    }
} 

inline void init()
{
    for(int i = 1; i <= num; i ++ )
        for(int j = 1; j <= num; j ++ )
        {
            base t = b[i];
            bool ok = true;

            // cout << i << ' ' << j << endl;
            for(int k = 0; k < 5; k ++ )
                if(b[j].a[k])
                {
                    ok &= t.insert(b[j].a[k]);
                    // cout << ok << endl;
                }

            if(ok) trans[i][j] = hsh[t.hash()];
        }
}

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

bitset<N> ok, tw;
int bcnt, blo[N], p[N], val[N];
int dfn[N], tim;
int dp[M][B];

inline void dfs(int u, int fa)
{
    dfn[u] = ++ tim;
    blo[u] = bcnt;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == 1) continue;
        if(!blo[v])
        {
            dist[v] = dist[u] ^ w[i];
            dfs(v, u);
        }
        else if(v != fa && dfn[u] > dfn[v])
        {
            ok[bcnt] = ok[bcnt] & c[bcnt].insert(dist[u] ^ dist[v] ^ w[i]);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    // cout << emp.hash() << endl;

    memset(h, -1, sizeof h);

    n = read(), m = read();

    // base a;
    // a.insert(n);
    // cout << a.insert(m) << endl;
    // cout << a.insert(4) << endl;
    dfs_base(emp);

    init();

    // for(int i = 1; i <= num; i ++ )
    //     for(int j = 1; j <= num; j ++ )
    //         if(trans[i][j] != trans[j][i])
    //         {
    //             puts("fuc");
    //         }
    // cout << num << endl;
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    for(int i = h[1]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(!blo[v])
        {
            bcnt ++;
            ok[bcnt] = true;
            blo[v] = bcnt;
            p[bcnt] = v;
            val[bcnt] = w[i];
            dfs(v, 1);
        }
        else
        {
            for(int j = h[v]; j != -1; j = ne[j])
            {
                int o = e[j];
                if(p[blo[v]] == o)
                {
                    tw[blo[v]] = true;
                    val[blo[v]] ^= w[i] ^ w[j];
                    break;
                }
            }
        }
    }

    dp[0][hsh[0]] = 1;
    for(int i = 1; i <= bcnt; i ++ )
    {
        for(int j = 1; j <= num; j ++ ) dp[i][j] = dp[i - 1][j];
        if(!ok[i]) continue;
        if(!tw[i])
        {
            int id = hsh[c[i].hash()];
            for(int j = 1; j <= num; j ++ )
                if(trans[id][j])
                    dp[i][trans[id][j]] = (dp[i][trans[id][j]] + dp[i - 1][j]) % mod;
        }
        else
        {
            int id1 = hsh[c[i].hash()];
            bool ok = c[i].insert(val[i]);
            int id2 = hsh[c[i].hash()];
            for(int j = 1; j <= num; j ++ )
            {
                if(trans[j][id1])
                    dp[i][trans[j][id1]] = (dp[i][trans[id1][j]] + 2 * dp[i - 1][j] % mod) % mod;
                if(ok && trans[j][id2])
                    dp[i][trans[j][id2]] = (dp[i][trans[id2][j]] + dp[i - 1][j]) % mod;
            }
        }
    }

    ll ans = 0;
    for(int i = 1; i <= num; i ++ )
        ans = (ans + dp[bcnt][i]) % mod;
    
    cout << ans << endl;

    return 0;
}
