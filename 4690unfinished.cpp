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

const int N = 1e5 + 10;
int a[N];
bitset<N> st;

struct node
{
    int l, r;
    mutable int val;
    bool operator < (const node& W) const
    {
        return l < W.l;
    }
};

struct query
{
    int op, l, r, v;
}q[N];

set<node> t;

auto split(int x)
{
    auto it = t.lower_bound((node){x, 0, 0});
    if(it -> l == x && it != t.end()) return it;
    it --;
    int l = it -> l, r = it -> r, v = it -> val;
    t.erase(it);
    t.insert((node){l, x - 1, v});
    return t.insert((node){x, r, v}).first;
}

void assign(int l, int r, int val)
{
    auto itr = split(r + 1), itl = split(l);
    t.erase(itl, itr);
    t.insert((node){l, r, val});
}

int get(int l, int r)
{
    auto itr = split(r + 1), itl = split(l);
    int cnt = 0;
    for(; itl != itr; itl ++ )
    {
        int v = itl -> val;
        if(!st[v]) cnt ++;
        st[v] = true;
    }
    st.reset();
    return cnt;
}

void print()
{
    for(auto u : t)
    {
        for(int i = u.l; i <= u.r; i ++ )
            cout << u.val << ' ';
    }
    puts("");
}

int n, m;
vector<int> nums;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(register int i = 1; i <= n; i ++ ) a[i] = read(), nums.push_back(a[i]);

    t.insert((node){n + 1, n + 1, 0});
    for(int i = 0; i < m; i ++ )
    {
        int op = read(), l = read(), r = read();
        if(op == 1)
        {
            int x = read();
            nums.push_back(x);
            q[i] = {op, l, r, x};
        }
        else q[i] = {op, l, r, 9};
    } 
    
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(register int i = 1; i <= n; i ++ ) 
    {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
        t.insert((node){i, i, a[i]});
    }

    for(int i = 0; i < m; i ++ )
        if(q[i].op == 1)
            q[i].v = lower_bound(nums.begin(), nums.end(), q[i].v) - nums.begin();
    
    t.insert((node){n + 1, n + 1, 0});

    for(int i = 0; i < m; i ++ )
    {
        if(q[i].op == 1)
        {
            assign(q[i].l, q[i].r, q[i].v);
        }
        else printf("%d\n", get(q[i].l, q[i].r));
    }
    
    return 0;
}
