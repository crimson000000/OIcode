#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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
int n;
ll a[N], w[N];
int h[N], e[N], ne[N], idx;
int din[N];
ll ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> q;
bitset<N> st;
inline bool topsort()
{
    for(int i = 0; i <= n; i ++ )
        if(!din[i])
        {
            q.push(i);
            st[i] = true;
        }
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            din[v] --;
            if(!din[v])
            {
                q.push(v);
                st[v] = true;
            }
        }
    }

    for(int i = 0; i <= n; i ++ )
        if(!st[i])
            return false;
    return true;
}

int p[N], siz[N];
inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

struct node
{
    ll x, w, siz;
    bool operator < (const node& a) const
    {
        return w * a.siz > a.w * siz;
    }
};
priority_queue<node> heap;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        add(a[i], i);
        din[i] ++;
    } 

    for(int i = 0; i <= n; i ++ ) p[i] = i, siz[i] = 1;

    if(!topsort())
    {
        puts("-1");
        return 0;
    }

    for(int i = 1; i <= n; i ++ )
    {
        w[i] = read();
        heap.push({i, w[i], 1});
    }

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int x = find(t.x);
        if(siz[x] != t.siz) continue;
        int y = find(a[x]);
        p[x] = y;
        ans += w[x] * siz[y];
        w[y] += w[x];
        siz[y] += siz[x];
        if(y) heap.push({y, w[y], siz[y]});
    }

    cout << ans << endl;

    return 0;
}