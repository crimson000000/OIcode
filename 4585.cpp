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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;
int tim;
namespace trie
{
    int tr[N * 10][2], date[N * 10];
    int cnt;
    inline void insert(int p, int x, int d)
    {
        for(int i = 30; i >= 0; i -- )
        {
            int v = x >> i & 1;
            if(!tr[p][v]) tr[p][v] = ++ cnt;
            p = tr[p][v];
            date[p] = max(date[p], d);
        }
    }

    inline int query(int p, int x, int d)
    {
        int res = 0;
        for(int i = 30; i >= 0; i -- )
        {
            int v = x >> i & 1;
            if(tr[p][v ^ 1] && date[tr[p][v ^ 1]] >= d) 
            {
                p = tr[p][v ^ 1];
                res |= 1 << i;
            }
            else if(date[tr[p][v]] >= d) p = tr[p][v];
            else return res;
        }
        return res;
    }
}

struct node
{
    int l, r;
}t[N << 1];
int rt, cnt;

inline void insert(int &p, int l, int r, int pos, int x, int d)
{
    if(!p) p = ++ cnt;
    trie::insert(p, x, d);
    if(l == r) return;
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, l, mid, pos, x, d);
    else insert(t[p].r, mid + 1, r, pos, x, d);
}

inline int query(int p, int l, int r, int L, int R, int x, int d)
{
    if(!p) return 0;
    if(l >= L && r <= R) return trie::query(p, x, d);
    int mid = l + r >> 1;
    int ans = 0;
    if(L <= mid) ans = max(ans, query(t[p].l, l, mid, L, R, x, d));
    if(R > mid) ans = max(ans, query(t[p].r, mid + 1, r, L, R, x, d));
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    trie::cnt = n << 2;

    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        insert(rt, 1, n, i, x, INF);
    }

    for(int i = 1; i <= m; i ++ )
    {
        int op = read();
        if(op == 0)
        {
            int s = read(), v = read();
            tim ++;
            insert(rt, 1, n, s, v, tim);
        }
        else
        {
            int l = read(), r = read(), x = read(), d = read();
            printf("%d\n", query(rt, 1, n, l, r, x, tim - d + 1));
        }
    }
    
    return 0;
}
