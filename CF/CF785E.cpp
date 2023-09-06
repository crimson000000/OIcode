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

const int N = 2e5 + 10, BLOCK = 10010;
int a[N], pos[N];
struct fhq
{
    struct node
    {
        int l, r;
        int key, val;
        int siz;
    }t[N << 1];
    int cnt;

    inline int New(int val)
    {
        t[++ cnt].val = val;
        t[cnt].siz = 1;
        t[cnt].key = rand();
        return cnt;
    }

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    }

    inline int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key < t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            pushup(x);
            return x;
        }
        else
        {
            t[y].l = merge(x, t[y].l);
            pushup(y);
            return y;
        }
    }

    inline void split(int p, int val, int &x, int &y)
    {
        if(!p) x = y = 0;
        else
        {
            if(t[p].val <= val)
            {
                x = p;
                split(t[p].r, val, t[x].r, y);
            }
            else
            {
                y = p;
                split(t[p].l, val, x, t[y].l);
            }
            pushup(p);
        }
    }

    int x, y, z;
    inline void insert(int &root, int val)
    {
        split(root, val, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline void del(int &root, int val)
    {
        split(root, val - 1, x, y);
        split(y, val, y, z);
        y = merge(t[y].l, t[y].r);
        root = merge(merge(x, y), z);
    }

    inline int lowersiz(int &root, int val)
    {
        split(root, val - 1, x, y);
        int ret = t[x].siz;
        root = merge(x, y);
        return ret;
    }

    inline int uppersiz(int &root, int val)
    {
        split(root, val, x, y);
        int ret = t[y].siz;
        root = merge(x, y);
        return ret;
    }
}FHQ;

struct Set
{
    int root;
    Set() {root = 0;}
    inline void insert(int val) {FHQ.insert(root, val);}
    inline void erase(int val) {FHQ.del(root, val);}
    inline int lowersiz(int val) {return FHQ.lowersiz(root, val);}
    inline int uppersiz(int val) {return FHQ.uppersiz(root, val);}

    inline void ldr(int p)
    {
        if(FHQ.t[p].l) ldr(FHQ.t[p].l);
        cout << FHQ.t[p].val << ' ';
        if(FHQ.t[p].r) ldr(FHQ.t[p].r);
    }

    inline void ldr() {ldr(root); puts("");}
};

struct block
{
    Set t;
    int l, r;

    inline void build()
    {
        for(int i = l; i <= r; i ++ ) t.insert(a[i]);
        // t.ldr();
    }
}b[BLOCK];
int n, k;
int B, T;
ll ans;

inline void change(int l, int r)
{
    if(a[l] < a[r]) ans ++;
    if(a[l] > a[r]) ans --;
    if(pos[l] == pos[r] || pos[l] == pos[r] - 1)
    {
        for(int i = l + 1; i < r; i ++ ) 
        {
            if(a[i] < a[l]) ans --;
            if(a[i] > a[l]) ans ++;
            if(a[i] < a[r]) ans ++;
            if(a[i] > a[r]) ans --;
        }
        if(pos[l] != pos[r])
        {
            b[pos[l]].t.erase(a[l]), b[pos[r]].t.erase(a[r]);
            b[pos[l]].t.insert(a[r]), b[pos[r]].t.insert(a[l]);
        }
        swap(a[l], a[r]);
    }
    else
    {
        int Lblock = pos[l], Rblock = pos[r];
        for(int i = l + 1; i <= b[Lblock].r; i ++ ) 
        {
            if(a[i] < a[l]) ans --;
            if(a[i] > a[l]) ans ++;
            if(a[i] < a[r]) ans ++;
            if(a[i] > a[r]) ans --;
        }
        for(int i = b[Rblock].l; i < r; i ++ )
        {
            if(a[i] < a[l]) ans --;
            if(a[i] > a[l]) ans ++;
            if(a[i] < a[r]) ans ++;
            if(a[i] > a[r]) ans --;
        }
        for(int i = Lblock + 1; i < Rblock; i ++ )
        {
            ans += b[i].t.uppersiz(a[l]);
            ans += b[i].t.lowersiz(a[r]);
            ans -= b[i].t.lowersiz(a[l]);
            ans -= b[i].t.uppersiz(a[r]);
        }
        b[pos[l]].t.erase(a[l]), b[pos[r]].t.erase(a[r]);
        b[pos[l]].t.insert(a[r]), b[pos[r]].t.insert(a[l]);
        // b[pos[l]].t.ldr();
        // b[pos[r]].t.ldr();
        swap(a[l], a[r]);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    B = max(sqrt((double)n * (double)log(n)), 1.0), T = n / B;

    for(int i = 1; i <= n; i ++ ) a[i] = i;

    for(int i = 1; i <= T; i ++ )
    {
        b[i].l = (i - 1) * B + 1;
        b[i].r = i * B;
        b[i].build();
    }

    if(b[T].r < n)
    {
        T ++;
        b[T].l = b[T - 1].r + 1;
        b[T].r = n;
        b[T].build();
    }

    for(int i = 1; i <= T; i ++ )
        for(int j = b[i].l; j <= b[i].r; j ++ )
            pos[j] = i;

    while(k -- )
    {
        int l = read(), r = read();
        if(l > r) swap(l, r);
        if(l != r) change(l, r);
        printf("%lld\n", ans);
        // for(int i = 1; i <= T; i ++ )
        //     b[i].t.ldr();
        // for(int i = 1; i <= n; i ++ ) cout << a[i] << ' ';
        // puts("");
    }

    return 0;
}