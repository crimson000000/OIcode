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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;

struct List
{
    int w, l, r;
}e[N];

struct Node
{
    int val, id;
    bool operator < (const Node& a) const
    {
        return val > a.val;
    }
};
priority_queue<Node> heap;
bitset<N> vis;
ll ans;
int n, k;

inline void del(int x)
{
    e[x].l = e[e[x].l].l;
    e[x].r = e[e[x].r].r;
    e[e[x].l].r = x;
    e[e[x].r].l = x;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    int lst = read();
    for(int i = 1; i < n; i ++ )
    {
        int nw = read();
        e[i].w = nw - lst;
        lst = nw;
        e[i].l = i - 1, e[i].r = i + 1;
        heap.push({e[i].w, i});
    }

    e[0].w = e[n].w = INF;

    while(k -- )
    {
        while(vis[heap.top().id]) heap.pop();

        auto now = heap.top();
        heap.pop();
        ans += now.val;

        vis[e[now.id].l] = vis[e[now.id].r] = true;
        e[now.id].w = e[e[now.id].l].w + e[e[now.id].r].w - e[now.id].w;
        heap.push({e[now.id].w, now.id});
        del(now.id);
    }

    cout << ans << endl;

    return 0;
}
