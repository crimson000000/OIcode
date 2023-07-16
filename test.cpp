// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 3 * 1e4 + 10;
const int M = 130;
typedef unsigned int uit;
const uit mod = 10007;
int n;
int m;
int q;
uit iv[mod + 10];
uit ans[M];
char opt[20];
int rot;
inline void fwt(uit *a, const uit &o) // fwt
{
    for (int k = 1; k < m; k <<= 1)
        for (int s = 0; s < m; s += (k << 1))
            for (int i = s; i < s + k; i++)
            {
                uit a0 = a[i];
                uit a1 = a[i + k];
                a[i] = (a0 + a1) * o % mod;
                a[i + k] = (a0 + mod - a1) * o % mod;
            }
}
struct poly // 多项式类
{
    uit f[M];
    inline uit &operator[](const int &x) { return f[x]; }
    friend poly operator*(poly a, poly b)
    {
        poly c;
        for (int i = 0; i < m; i++)
            c[i] = a[i] * b[i] % mod;
        return c;
    }
    friend poly operator/(poly a, poly b)
    {
        poly c;
        for (int i = 0; i < m; i++)
            c[i] = a[i] * iv[b[i]] % mod;
        return c;
    }
    friend poly operator+(poly a, poly b)
    {
        poly c;
        for (int i = 0; i < m; i++)
            c[i] = (a[i] + b[i]) % mod;
        return c;
    }
    friend poly operator-(poly a, poly b)
    {
        poly c;
        for (int i = 0; i < m; i++)
            c[i] = (a[i] + mod - b[i]) % mod;
        return c;
    }
    void operator+=(const poly &b)
    {
        for (int i = 0; i < m; i++)
            f[i] = (f[i] + b.f[i]) % mod;
    }
    void operator-=(const poly &b)
    {
        for (int i = 0; i < m; i++)
            f[i] = (f[i] + mod - b.f[i]) % mod;
    }
    inline void setone()
    {
        for (int i = 0; i < m; i++)
            f[i] = 1;
    }
} we[N], one;
struct mar // 矩阵类
{
    poly mp[2][2];
    inline poly *operator[](const int &x) { return mp[x]; }
    friend mar operator*(mar a, mar b)
    {
        mar c;
        c[0][0] = a[0][0] * b[0][0];
        c[0][1] = a[0][0] * b[0][1] + a[0][1];
        c[1][0] = a[1][0] * b[0][0] + b[1][0];
        c[1][1] = a[1][0] * b[0][1] + a[1][1] + b[1][1];
        return c;
    }
};
int v[2 * N];
int x[2 * N];
int ct;
int al[N];
int siz[N];
int h[N];
inline void add(int u, int V)
{
    v[++ct] = V;
    x[ct] = al[u];
    al[u] = ct;
}
inline int dfs(int u) // 轻重链剖分
{
    siz[u] = 1;
    for (int i = al[u]; i; i = x[i])
        if (siz[v[i]] == 0)
        {
            siz[u] += dfs(v[i]);
            if (siz[h[u]] < siz[v[i]])
                h[u] = v[i];
        }
    return siz[u];
}
struct data // 用来维护轻边的结构体
{
    int fz[M];
    uit fv[M];
    inline void wt(const int &i, const int &x)
    {
        if (x == 0)
            fz[i] = fv[i] = 1;
        else
            fz[i] = 0, fv[i] = x;
    }
    void operator*=(const poly &b)
    {
        for (int i = 0; i < m; i++)
            fz[i] += (b.f[i] == 0);
        for (int i = 0; i < m; i++)
            fv[i] = fv[i] * (b.f[i] ? b.f[i] : 1) % mod;
    }
    void operator/=(const poly &b)
    {
        for (int i = 0; i < m; i++)
            fz[i] -= (b.f[i] == 0);
        for (int i = 0; i < m; i++)
            fv[i] = fv[i] * iv[b.f[i]] % mod;
    }
};
inline void cpy(poly &a, const data &b)
{
    for (int i = 0; i < m; i++)
        a[i] = b.fz[i] ? 0 : b.fv[i];
}
struct global_balanced_tree // 全局平衡二叉树
{
    int s[N][2];
    int fa[N];
    int lsiz[N];
    int st[N];
    int tp;
    mar w[N];
    mar mul[N];
    data lt[N];
    poly lh[N];
    inline void udw(const int &p)
    {
        cpy(w[p][0][0], lt[p]);
        w[p][1][1] = w[p][1][0] = w[p][0][1] = w[p][0][0];
        w[p][1][1] += lh[p];
    }
    inline void ud(const int &p) { mul[p] = mul[s[p][0]] * w[p] * mul[s[p][1]]; }
    inline void ins(const int &u, const int &v)
    {
        lt[u] *= (mul[v][1][0] + one);
        lh[u] += mul[v][1][1];
    }
    inline void del(const int &u, const int &v)
    {
        lt[u] /= (mul[v][1][0] + one);
        lh[u] -= mul[v][1][1];
    }
    inline bool isr(const int &u) { return (s[fa[u]][0] != u) && (s[fa[u]][1] != u); }
    inline int subbuild(int l, int r) // 一条重链递归建树
    {
        if (l == r)
        {
            ud(st[l]);
            return st[l];
        }
        if (l > r)
        {
            return 0;
        }
        int tot = 0;
        for (int i = l; i <= r; i++)
            tot += lsiz[st[i]];
        for (int i = l, nsiz = lsiz[st[i]]; i <= r; i++, nsiz += lsiz[st[i]])
            if (2 * nsiz >= tot)
            {
                s[st[i]][0] = subbuild(l, i - 1);
                s[st[i]][1] = subbuild(i + 1, r);
                fa[s[st[i]][0]] = st[i];
                fa[s[st[i]][1]] = st[i];
                ud(st[i]);
                return st[i];
            }
    }
    inline int build(int p) // 链分治
    {
        for (int i = p; i; i = h[i])
            lsiz[i] = siz[i] - siz[h[i]];
        for (int i = p; i; i = h[i])
            for (int j = al[i]; j; j = x[j])
                if (lsiz[v[j]] == 0)
                {
                    int ls = build(v[j]);
                    fa[ls] = i;
                    ins(i, ls);
                }
        for (int i = p; i; i = h[i])
            udw(i);
        tp = 0;
        for (int i = p; i; i = h[i])
            st[++tp] = i;
        reverse(st + 1, st + tp + 1);
        return subbuild(1, tp);
    }
    inline void modify(int u, const int &w1) // 修改，每次跳一条轻边
    {
        lt[u] /= we[u];
        for (int i = 0; i < m; i++)
            we[u][i] = 0;
        we[u][w1] = 1;
        fwt(we[u].f, 1);
        lt[u] *= we[u];
        udw(u);
        for (int p = u; p; p = fa[p])
            if (isr(p) && fa[p])
            {
                del(fa[p], p);
                ud(p);
                ins(fa[p], p);
                udw(fa[p]);
            }
            else
                ud(p);
        for (int i = 0; i < m; i++)
            ans[i] = mul[rot][1][1][i];
        fwt(ans, 5004);
    }
    inline void ih() // 初始化
    {
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < m; j++)
                lt[i].wt(j, we[i][j]);
        w[0][0][0].setone();
        mul[0][0][0].setone();
    }
} gbt;
int main()
{
    iv[0] = 1;
    iv[1] = 1;
    for (int i = 2; i < mod; i++)
        iv[i] = (mod - mod / i) * iv[mod % i] % mod;
    scanf("%d%d", &n, &m);
    one.setone();
    for (int i = 1, w; i <= n; i++)
    {
        scanf("%d", &w), we[i][w] = 1, fwt(we[i].f, 1);
    }
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs(1);
    gbt.ih();
    rot = gbt.build(1);
    for (int i = 0; i < m; i++)
        ans[i] = gbt.mul[rot][1][1][i];
    fwt(ans, 5004);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%s", opt);
        if (opt[0] == 'Q')
        {
            int t;
            scanf("%d", &t);
            printf("%d\n", ans[t]);
        }
        else
        {
            int w;
            int u;
            scanf("%d%d", &u, &w);
            gbt.modify(u, w);
        }
    }
    return 0; // 拜拜程序~
}
