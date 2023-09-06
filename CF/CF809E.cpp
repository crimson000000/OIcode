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

const int N = 1e6 + 10, mod = 1e9 + 7;
int h[N], e[N], ne[N], idx;
int pos[N];
int n;
int a[N];
ll f[N], F[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

int phi[N], miu[N];
int primes[N], cnt;
bitset<N> st;
void init(int n)
{
    phi[1] = 1, miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            miu[i] = -1;
            phi[i] = i - 1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                phi[t] = phi[i] * primes[j];
                break;
            }
            miu[t] = -miu[i];
            phi[t] = phi[i] * phi[primes[j]];
        }
        // cout << miu[i] << ' ';
    }
}

int fa[N], siz[N], son[N], dep[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
    }
}

int top[N], dfn[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

namespace VT
{
    int S[N];
    int cnt;
    vector<int> G[N];
    int stk[N], tt;
    bitset<N> st, on;
    queue<int> cn;
    ll sum[N];
    ll ans;

    void aded(int a, int b)
    {
        G[a].emplace_back(b);
        G[b].emplace_back(a);
        if(!st[a]) cn.push(a), st[a] = true;
        if(!st[b]) cn.push(b), st[b] = true;
    }

    void clear()
    {
        tt = 0;
        cnt = 0;
        while(cn.size())
        {
            int u = cn.front();
            cn.pop();
            on[u] = false;
            st[u] = false;
            sum[u] = 0;
            G[u].clear();
        }
    }

    void pushin(int id)
    {
        S[++ cnt] = id;
        on[id] = true;
    }

    void insert(int u)
    {
        int lc = lca(u, stk[tt]);
        if(u == lc) return;
        while(tt > 1 && dep[lc] <= dep[stk[tt - 1]])
        {
            aded(stk[tt], stk[tt - 1]);
            tt --;
        }
        if(lc != stk[tt])
        {
            aded(stk[tt], lc);
            stk[tt] = lc;
        }
        stk[++ tt] = u;
    }

    void build()
    {
        sort(S + 1, S + cnt + 1, [](int x, int y){
            return dfn[x] < dfn[y];
        });
        
        stk[tt = 1] = 1;
        for(int i = 1; i <= cnt; i ++ )
            insert(S[i]);

        while(tt > 1)
        {
            aded(stk[tt], stk[tt - 1]);
            tt --;
        }
    }

    void dp(int u, int fat)
    {
        if(on[u]) sum[u] = phi[a[u]];
        // cout << u << endl;
        for(auto v : G[u])
        {
            if(v == fat) continue;
            dp(v, u);
            ans = (ans + 4 * sum[u] * sum[v] % mod * dep[u] % mod) % mod;
            sum[u] = (sum[u] + sum[v]) % mod;
        }
        if(on[u]) ans = (ans + 2ll * phi[a[u]] * phi[a[u]] % mod * dep[u]) % mod;
    }

    ll solve()
    {
        ans = 0;
        build();
        dp(1, 1);
        return ans;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        pos[a[i]] = i;
    }
    init(n);

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(i > n / 2) break;
        for(int j = i; j <= n; j += i)
            VT::pushin(pos[j]);
        ll sum1 = 0, sum2 = 0;
        for(int j = i; j <= n; j += i)
        {
            sum1 = (sum1 + (ll)phi[j] * dep[pos[j]]) % mod;
            sum2 = (sum2 + phi[j]) % mod;
        }
        F[i] = 2 * sum1 * sum2 % mod;
        // cout << F[i] << endl;
        F[i] = (F[i] - VT::solve() % mod + mod) % mod;
        // cout << F[i] << endl;
        // puts("---");
        VT::clear();
    }
    
    // F[1] = 0;
    // for(int i = 1; i <= n; i ++ )
    //     for(int j = 1; j <= n; j ++ )
    //         F[1] = (F[1] + 1ll * phi[a[i]] * phi[a[j]] % mod * (dep[i] + dep[j] - 2 * dep[lca(i, j)]) % mod) % mod;
    
    // F[1] = 2 * F[1] % mod;
    // cout << F[1] << endl;

    for(int i = 1; i <= n; i ++ )
        for(int j = i; j <= n; j += i)
            f[i] = (f[i] + F[j] * miu[j / i] % mod + mod) % mod;
    
    ll ans = 0;
    for(int i = 1; i <= n; i ++ )
    {
        ans = (ans + i * f[i] % mod * qmi(phi[i], mod - 2, mod) % mod) % mod;
        // cout << f[i] << endl;
    }

    // cout << ans << endl;
    
    cout << ans * qmi((ll)n * (n - 1) % mod, mod - 2, mod) % mod << endl;

    return 0;
}