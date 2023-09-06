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
int root[N], idx;
int n, k;
ll a[N], s[N];

struct nd
{
    int ch[2], cnt, id;
}tr[N * 50];

void insert(int &p, int q, ll x, int pos, int idd)
{
    p = ++ idx;
    tr[p] = tr[q];
    tr[p].cnt ++;
    if(pos < 0)
    {
        tr[p].id = idd;
        return;
    }
    int v = x >> pos & 1;
    insert(tr[p].ch[v], tr[q].ch[v], x, pos - 1, idd);
}

ll query(int p, int q, ll x, int pos)
{
    if(pos == -1) return tr[p].id;
    int v = x >> pos & 1;
    if(tr[tr[p].ch[v ^ 1]].cnt - tr[tr[q].ch[v ^ 1]].cnt > 0)
        return query(tr[p].ch[v ^ 1], tr[q].ch[v ^ 1], x, pos - 1);
    else return query(tr[p].ch[v], tr[q].ch[v], x, pos - 1);
}

struct node
{
    int l, r, x, id;
    ll val;
    node(int _l = 0, int _r = 0, int _x = 0)
    {
        l = _l, r = _r, x = _x;
        id = query(root[r], root[l - 1], s[x], 31);
        val = s[x] ^ s[id - 1];
    }

    bool operator < (const node& a) const
    {
        return val < a.val;
    }
};

priority_queue<node> heap;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        s[i] = a[i];
        s[i] = s[i - 1] ^ a[i];
        insert(root[i], root[i - 1], s[i - 1], 31, i);
    }

    for(int i = 1; i <= n; i ++ ) heap.push(node(1, i, i));

    while(k -- )
    {
        auto t = heap.top();
        heap.pop();
        ans += t.val;
        if(t.l < t.id) heap.push(node(t.l, t.id - 1, t.x));
        if(t.r > t.id) heap.push(node(t.id + 1, t.r, t.x));
    }

    cout << ans << endl;
    
    return 0;
}
