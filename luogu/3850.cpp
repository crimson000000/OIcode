#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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
    int val, key, siz;
}t[N];
int root, cnt;

inline int New(int val)
{
    t[++ cnt].val = val;
    t[cnt].key = rand();
    t[cnt].siz = 1;
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

inline void split(int p, int siz, int &x, int &y)
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

int query(int pos)
{
    int p = root;
    pos = pos + 1;
    while(1)
    {
        if(t[t[p].l].siz + 1 == pos) return t[p].val;
        else if(t[t[p].l].siz + 1 > pos) p = t[p].l;
        else
        {
            pos -= t[t[p].l].siz + 1;
            p = t[p].r;
        }
    }
}

string s[N];
int n, m, q;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i ++ ) 
    {
        cin >> s[i];
        root = merge(root, New(i));
    }
    
    cin >> m;

    while(m -- )
    {
        n ++;
        int pos;
        cin >> s[n] >> pos;
        int x, y;
        
        split(root, pos, x, y);
        root = merge(merge(x, New(n)), y);
    }

    cin >> q;

    while(q -- )
    {
        int pos;
        cin >> pos;
        cout << s[query(pos)] << endl;
    }
    
    return 0;
}
