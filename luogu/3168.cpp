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

const int N = 1e6 + 10, M = 1e7;
int n, m;
ll lastans = 1;
int cntt[10 * N];
vector<int> ins[N];

struct node
{
    int l, r;
    int cnt;
    ll sum;
}t[N * 20];
int cnt, root[N];

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
}

inline void insert(int &p, int q, int l, int r, int pos, ll v)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].sum += v * pos;
        t[p].cnt += v;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, t[q].l, l, mid, pos, v);
    else insert(t[p].r, t[q].r, mid + 1, r, pos, v);
    pushup(p);
}

inline ll query(int p, int l, int r, int k)
{
    if(l == r) return (ll)l * k;
    int mid = l + r >> 1;
    if(k <= t[t[p].l].cnt) return query(t[p].l, l, mid, k);
    else return t[t[p].l].sum + query(t[p].r, mid + 1, r, k - t[t[p].l].cnt);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = read();
    for(int i = 1; i <= m; i ++ )
    {
        int s = read(), t = read(), w = read();
        ins[s].emplace_back(w);
        ins[t + 1].emplace_back(-w);
    }

    for(int i = 1; i <= n; i ++ )
    {
        root[i] = root[i - 1];
        for(auto v : ins[i])
            insert(root[i], root[i], 1, M, abs(v), v > 0 ? 1 : -1);
    }

    for(int T = 1; T <= n; T ++ )
    {
        ll x = read(), a = read(), b = read(), c = read();
        ll k = 1 + (a * lastans + b) % c;
        if(k > t[root[x]].cnt) printf("%lld\n", lastans = t[root[x]].sum);
        else printf("%lld\n", lastans = query(root[x], 1, M, k));
    }

    return 0;
}
