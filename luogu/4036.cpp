#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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

const int N = 2e5 + 10, P = 131;
ull pp[N];
char s[N];
int n, m;
struct fhq
{
    struct node
    {
        int l, r;
        char ch;
        ull Hash;
        int siz, key;
    }t[N];
    int root, cnt;

    inline int New(char ch)
    {
        t[++ cnt].ch = ch;
        t[cnt].siz = 1;
        t[cnt].key = rand();
        t[cnt].Hash = ch;
        return cnt;
    }

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
        t[p].Hash = t[t[p].r].Hash + t[p].ch * pp[t[t[p].r].siz] + t[t[p].l].Hash * pp[t[t[p].r].siz + 1];
    }

    int merge(int x, int y)
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

    void split(int p, int siz, int &x, int &y)
    {
        if(!p) x = y = 0;
        else
        {
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

    int x, y, z;
    inline void insert(int p, char ch)
    {
        split(root, p, x, y);
        root = merge(merge(x, New(ch)), y);
    }

    inline void change(int p, char ch)
    {
        split(root, p - 1, x, y);
        split(y, 1, y, z);
        root = merge(merge(x, New(ch)), z);
    }

    inline ull gethash(int l, int r)
    {
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        ll res = t[y].Hash;
        root = merge(merge(x, y), z);
        return res;
    }

    int build(int l, int r)
    {
        if(l == r) return New(s[l]);
        int mid = l + r >> 1;
        int x = merge(build(l, mid), build(mid + 1, r));
        return x;
    }

    void ldr(int p)
    {
        if(!p) return;
        ldr(t[p].l);
        cout << t[p].ch;
        ldr(t[p].r);
    }
}t1, t2;

bool check(int x, int y, int mid)
{
    return t1.gethash(x, x + mid - 1) == t2.gethash(y, y + mid - 1);
}

int query(int x, int y)
{
    int l = 0, r = min(n - x + 1, n - y + 1);
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(x, y, mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    pp[0] = 1;
    for(int i = 1; i <= 100000; i ++ ) pp[i] = pp[i - 1] * P;

    scanf("%s", s + 1);
    n = strlen(s + 1);
    t1.root = t1.build(1, n);
    t2.root = t2.build(1, n);

    m = read();
    while(m -- )
    {
        char op[5];
        scanf("%s", op);

        if(op[0] == 'Q')
        {
            int x = read(), y = read();
            printf("%d\n", query(x, y));
        }
        else if(op[0] == 'R')
        {
            int x = read();
            char in[5];
            scanf("%s", in);
            t1.change(x, in[0]);
            t2.change(x, in[0]);
        }
        else
        {
            int x = read();
            char in[5];
            scanf("%s", in);
            n ++;
            t1.insert(x, in[0]);
            t2.insert(x, in[0]);
        }
    }
    
    return 0;
}