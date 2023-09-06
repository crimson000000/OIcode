#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e6 + 10;
int n, s, m;
ll a[N], f[N];
int h[N << 1], e[N << 2], ne[N << 2], w[N << 2], idx;
int din[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    din[b] ++;
}

struct node
{
    int l, r;
    int cnt;
}t[N << 2];
int pos[N];
int tot;

int place[N];
void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].cnt = ++ tot;
    if(l == r)
    {
        pos[l] = t[p].cnt;
        place[t[p].cnt] = l;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    add(t[p << 1].cnt, t[p].cnt, 0);
    add(t[p << 1 | 1].cnt, t[p].cnt, 0);
}

void Add(int p, int l, int r, int id)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        add(t[p].cnt, id, 1);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) Add(p << 1, l, r, id);
    if(r > mid) Add(p << 1 | 1, l, r, id);
}

queue<int> q;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), s = read(), m = read();
    for(int i = 1; i <= s; i ++ )
    {
        int p = read(), d = read();
        a[p] = d;
    }

    build(1, 1, n);

    while(m -- )
    {
        int l = read(), r = read(), k = read();
        int New = ++ tot;
        for(int i = 1; i <= k; i ++ )
        {
            int x = read();
            add(New, pos[x], 0);
            // cout << l << ' ' << x - 1 << endl;
            if(x > l) Add(1, l, x - 1, New);
            l = x + 1;
        }
        if(l <= r) Add(1, l, r, New);
    }

    for(int i = 1; i <= tot; i ++ )
    {
        f[i] = 1;
        if(place[i] && a[place[i]])
            f[i] = max(f[i], a[place[i]]);
        if(!din[i])
            q.push(i);
    }
    
    while(q.size())
    {
        int u = q.front();
        // cout << u << endl;
        q.pop();

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            f[v] = max(f[v], f[u] + w[i]);
            if(place[v] && a[place[v]])
            {
                if(f[v] > a[place[v]]) 
                {
                    puts("NIE");
                    return 0;
                }
                f[v] = max(f[v], a[place[v]]);
            }
            din[v] --;
            if(!din[v]) q.push(v);
        }
    }

    for(int i = 1; i <= tot; i ++ ) 
        if(din[i])
        {
            // cout << "fuc" << endl;
            puts("NIE");
            return 0;
        }

    for(int i = 1; i <= n; i ++ )
        if(f[pos[i]] > 1000000000)
        {
            puts("NIE");
            return 0;
        }

    puts("TAK");
    for(int i = 1; i <= n; i ++ ) 
        printf("%lld ", f[pos[i]]);

    return 0;
}