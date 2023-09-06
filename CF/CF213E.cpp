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

const int N = 1e6 + 10, P = 131, mod = 998244353;
int pos[N];
struct node
{
    int l, r;
    int key;
    ll Hash;
    int pos, val;
    int siz;
}t[N];
ll mi[N];
int b[N], a[N];
int root, cnt;
ll a_Hash, a_add;
int n, m;

inline int New(int pos, int val)
{
    t[++ cnt].pos = pos;
    t[cnt].val = val;
    t[cnt].key = rand();
    t[cnt].Hash = val;
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    t[p].Hash = (t[t[p].l].Hash * mi[t[t[p].r].siz + 1] % mod + 
                t[p].val * mi[t[t[p].r].siz] % mod + 
                t[t[p].r].Hash) % mod;
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

inline void split(int p, int pos, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[p].pos <= pos)
        {
            x = p;
            split(t[p].r, pos, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, pos, x, t[y].l);
        }
        pushup(p);
    }
}

int x, y, z;
inline void insert(int pos, int val)
{
    split(root, pos, x, y);
    root = merge(merge(x, New(pos, val)), y);
}

inline void del(int pos)
{
    split(root, pos - 1, x, y);
    split(y, pos, y, z);
    root = merge(x, z);
}

void ldr(int p)
{
    if(!p) return;
    ldr(t[p].l);
    cout << t[p].val << ' ';
    ldr(t[p].r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    mi[0] = 1;
    for(int i = 1; i <= n + m; i ++ ) mi[i] = mi[i - 1] * P % mod;

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        a_Hash = (a_Hash * P % mod + a[i]) % mod;
        a_add = (a_add + mi[i - 1]) % mod;
    }

    for(int i = 1; i <= m; i ++ )
    {
        b[i] = read();
        pos[b[i]] = i;
    }

    for(int i = 1; i < n; i ++ ) insert(pos[i], i);
    
    int cnt = 0;
    for(int x = 0; x <= m - n; x ++ )
    {
        if(x) del(pos[x]);
        insert(pos[n + x], n + x);
        if(t[root].Hash == (a_Hash + x * a_add) % mod) cnt ++;
        // cout << t[root].Hash << ' ' << a_Hash << endl;
        // ldr(root);
        // puts("");
    }

    cout << cnt << endl;

    return 0;
}