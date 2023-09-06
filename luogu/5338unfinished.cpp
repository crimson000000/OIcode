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

const int N = 2e6 + 10;
struct P
{
    int ac, time, id;
    bool operator <= (const P& p) const
    {
        if(ac != p.ac) return ac >= p.ac;
        return time <= p.time;
    }
}

struct node
{
    int l, r;
    int key, siz;
    P val;
}t[N];
int root, cnt;

inline int New(int ac, int t, int id)
{
    t[++ cnt].val = {ac, t, id};
    t[cnt].key = rand();
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
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

void split(int p, P val, int &x, int &y)
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

inline void change(int id, int time)
{
    int p = root;
    
}

void init()
{
    memset(t, 0, sizeof t);
    root = cnt = 0;
}

typedef unsigned int ui ;
ui randNum( ui& seed , ui last , const ui m){ 
    seed = seed * 17 + last ; return seed % m + 1; 
}

int T;
ui n, m, seed, last = 7;
int x, y, z;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> T;
    while(T -- )
    {
        init();
        cin >> m >> n >> seed;
        while(n -- )
        {
            int a = randNum(seed, last, m), b = randNum(seed, last, m);
            if(!find(a))
            {
                split(root, (P){1, b, a}, x, y);
                cout << t[x].siz << endl;
                root = merge(merge(x, New(1, b, a)), y);
            }
            else
            {
                change(a, b);
            }
        }
    }
    
    return 0;
}
