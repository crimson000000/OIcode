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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct node
{
    int l, r;
    int val, siz, key;
    bool rev;
    int minn;
}t[N];
int cnt, root;

inline int New(int val)
{
    t[++ cnt].val = val;
    t[cnt].siz = 1;
    t[cnt].l = t[cnt].r = 0;
    t[cnt].rev = false;
    t[cnt].key = rand();
    t[cnt].minn = val;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    t[p].minn = t[p].val;
    if(t[p].l) t[p].minn = min(t[p].minn, t[t[p].l].minn);
    if(t[p].r) t[p].minn = min(t[p].minn, t[t[p].r].minn);
}

inline void reverse(int p)
{
    t[p].rev ^= 1;
    swap(t[p].l, t[p].r);
}

inline void pushdown(int p)
{
    if(t[p].rev)
    {    
        if(t[p].l) reverse(t[p].l);
        if(t[p].r) reverse(t[p].r); 
        t[p].rev = 0;
    }
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key > t[y].key)
    {
        pushdown(x);
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void split(int p, int siz, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[t[p].l].siz + 1 <= siz)
        {
            x = p;
            split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, siz, x, t[y].l);
        }
        pushup(p);
    }
}

int find_min(int p)
{
    int k = 1;
    while(1)
    {
        pushdown(p);
        if(t[p].l && t[t[p].l].minn == t[p].minn) 
        {
            // cout << p << ':' << t[p].l << endl;
            p = t[p].l;
        }
        else if(t[p].r && t[t[p].r].minn == t[p].minn) k += t[t[p].l].siz + 1, p = t[p].r;
        else return k + t[t[p].l].siz;
    }
}

int n, m;
int x, y, z;
int a[N], cntt[N];
vector<int> nums;

int build(int l, int r)
{
    if(l == r) return New(a[l]);
    int mid = l + r >> 1;
    int x = merge(build(l, mid), build(mid + 1, r));
    return x;
}

void ldr(int p)
{
    if(!p) return;
    pushdown(p);
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

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
        a[i] += cntt[a[i]] ++;
    }

    // for(int i = 1; i <= n; i ++ ) root = merge(root, New(a[i]));
    // ldr(root);
    root = build(1, n);

    for(int i = 1; i <= n; i ++ )
    {
        int rk = find_min(root);
        // cout << rk << endl;
        split(root, rk, x, y);
        split(x, rk - 1, x, z);
        reverse(x);
        root = merge(x, y);
        cout << rk + i - 1 << ' ';
    }
    
    return 0;
}
