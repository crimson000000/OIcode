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
int n, m, c, k;
int deg[N][11];
struct LCT
{
    struct lct
    {
        int ch[2];
        int fa, siz, val;
        int maxn;
        bool rev;
    }t[N];

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz;
        t[p].maxn = max(max(t[t[p].ch[0]].maxn, t[t[p].ch[1]].maxn), t[p].val);
    }

    inline void connect(int p, int fa, int s)
    {
        t[p].fa = fa;
        t[fa].ch[s] = p;
    }

    inline bool ident(int p, int fa)
    {
        return t[fa].ch[1] == p; 
    }
    
    inline bool is_root(int p)
    {
        return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
    }

    inline void reverse(int p)
    {
        swap(t[p].ch[0], t[p].ch[1]);
        t[p].rev ^= 1;
    }

    inline void pushdown(int p)
    {
        if(t[p].rev)
        {
            if(t[p].ch[0]) reverse(t[p].ch[0]);
            if(t[p].ch[1]) reverse(t[p].ch[1]);
            t[p].rev = 0;
        }
    }

    inline void pushdown_all(int p)
    {
        if(!is_root(p)) pushdown_all(t[p].fa);
        pushdown(p);
    }

    inline void rotate(int p)
    {
        int f = t[p].fa, ff = t[f].fa, k = ident(p, f);
        connect(t[p].ch[k ^ 1], f, k);
        t[p].fa = ff;
        if(!is_root(f)) t[ff].ch[ident(f, ff)] = p;
        connect(f, p, k ^ 1);
        pushup(f), pushup(p);
    }

    inline void spaly(int p)
    {
        pushdown_all(p);
        while(!is_root(p))
        {
            int f = t[p].fa, ff = t[f].fa;
            if(!is_root(f))
                if(ident(p, f) ^ ident(f, ff))
                    rotate(p);
                else rotate(f);
            rotate(p);
        }
    }

    inline void access(int x)
    {
        for(int y = 0; x; x = t[x].fa)
        {
            spaly(x);
            t[x].ch[1] = y;
            pushup(x);
            y = x;
        }
    }

    inline void make_root(int x)
    {
        access(x);
        spaly(x);
        reverse(x);
    }

    inline int find_root(int x)
    {
        access(x);
        spaly(x);
        int p = x;
        while(t[p].ch[0])
        {
            pushdown(p);
            p = t[p].ch[0];
        }
        spaly(p);
        return p;
    }

    inline bool link(int x, int y)
    {
        make_root(x);
        if(find_root(y) == x) return false;
        t[x].fa = y;
        return true;
    }
    
    inline bool cut(int x, int y)
    {
        make_root(x);
        if(find_root(y) != x || t[y].fa != x || t[y].ch[0]) return false;
        t[y].fa = t[x].ch[1] = 0;
        pushup(x);
        return true;
    }

    inline void split(int x, int y)
    {
        make_root(x);
        access(y);
        spaly(y);
    }
}tree[11];

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read(), c = read(), k = read();

    for(int i = 1; i <= n; i ++ )
    {
        int v = read();
        for(int j = 0; j < c; j ++ )
        {
            tree[j].t[i].val = tree[j].t[i].maxn = v;
            tree[j].t[i].siz = 1;
        }
    }    

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        tree[c].link(a, b);
        deg[a][c] ++, deg[b][c] ++;
    }

    while(k -- )
    {
        int op = read();
        if(op == 0)
        {
            int x = read(), y = read();
            for(int i = 0; i < c; i ++ )
            {
                tree[i].spaly(x);
                tree[i].t[x].val = y;
                tree[i].pushup(x);
            }
        }
        else if(op == 1)
        {
            int u = read(), v = read(), w = read();
            
            int col = -1;
            for(int i = 0; i < c; i ++ )
                if(tree[i].cut(u, v))
                {
                    col = i;
                    break;
                }
                
            deg[u][col] --, deg[v][col] --;
            if(col == -1)
            {
                deg[u][col] ++, deg[v][col] ++;
                puts("No such edge.");
                continue;
            }

            if(deg[u][w] == 2 || deg[v][w] == 2)
            {
                puts("Error 1.");
                deg[u][col] ++, deg[v][col] ++;
                tree[col].link(u, v);
                continue;
            }

            if(tree[w].find_root(u) == tree[w].find_root(v))
            {
                puts("Error 2.");
                tree[col].link(u, v);
                continue;
            }
            
            tree[w].link(u, v);

            
            deg[u][w] ++, deg[v][w] ++;
            puts("Success.");
        }
        else
        {
            int w = read(), u = read(), v = read();
            if(tree[w].find_root(u) != tree[w].find_root(v)) puts("-1");
            else
            {
                tree[w].split(u, v);
                printf("%d\n", tree[w].t[v].maxn);
            }
        }

        // for(int i = 0; i < c; i ++ )
        // {
        //     printf("the color is %d: ", i);
        //     for(int j = 1; j <= n; j ++ )
        //         printf("%d ", deg[j][i]);
        //     puts("");
        // }
    }

    return 0;
}
