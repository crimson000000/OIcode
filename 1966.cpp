#include <bits/stdc++.h>
#define int long long
using namespace std;
#define lowbit(x) (x) & -(x)
const int N = 1e5 + 10, mod = 1e8 - 3;
unordered_map<int, int> mp;
int a[N], b[N], c[N];
struct node
{
    int l, r;
    int key, size, val;
}t[N];
int cnt, root, n;
inline int New(int val)
{
    t[++ cnt].val = val;
    t[cnt].key = rand();
    t[cnt].size = 1;
    return cnt; 
}

inline void update(int p)
{
    t[p].size = t[t[p].l].size + t[t[p].r].size + 1;
}

void split(int p, int val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[p].val <= val)
        {
            x = p;
            split(t[p].r, val, t[p].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, val, x, t[p].l);
        }
        update(p);
    }
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        update(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        update(y);
        return y;
    }
}

int x, y, z;
inline void insert(int val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

int getrank(int val)
{
    split(root, val - 1, x, y);
    int res = t[x].size + 1;
    root = merge(x, y);
    return res;
}

void add(int x, int val)
{
    for(; x <= n; x += lowbit(x)) c[x] += val;
}

int query(int x)
{
    int res = 0;
    for(; x; x -= lowbit(x))
        res += c[x];
    return res;
}

void print()
{
    for(int i = 1; i <= n; i ++ ) cout << a[i] << ' ';
    puts("");
    for(int i = 1; i <= n; i ++ ) cout << b[i] << " ";
    puts("");
}

signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        insert(a[i]);
    }
    for(int i = 1; i <= n; i ++ )
    {
        int rank = getrank(a[i]);
        mp[rank] = a[i];
        a[i] = rank;
    }

    memset(t, 0, sizeof t);
    cnt = 0, root = 0;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> b[i];
        insert(b[i]);
    }
    for(int i = 1; i <= n; i ++ )
    {
        int rank = getrank(b[i]);
        b[i] = rank;
    }


    mp.clear();
    for(int i = 1, tot = 1; i <= n; i ++ )
        mp[a[i]] = tot ++;
    for(int i = 1; i <= n; i ++ )
        b[i] = mp[b[i]];

    int cnt = 0;
    for(int i = n; i > 0; i -- )
    {
        add(b[i], 1);
        cnt += query(b[i] - 1);
        cnt %= mod;
    }
    cout << cnt << endl;
}