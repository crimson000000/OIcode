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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int d[N], dd[N];
int c[N], tt;
bitset<N> bad, in;
queue<int> q;
int n, m, k;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool check(double mid)
{
    in.reset();
    for(int i = 1; i <= n; i ++ ) dd[i] = d[i];
    while(q.size()) q.pop();
    for(int i = 1; i <= n; i ++ )
    {
        if(bad[i])
        {
            for(int j = h[i]; j != -1; j = ne[j])
            {
                int v = e[j];
                dd[v] --;
            }
        }
        else in[i] = true;
    }
    for(int i = 1; i <= tt; i ++ )
        if((double)dd[c[i]] < (double)d[c[i]] * mid)
        {
            q.push(c[i]);
            in[c[i]] = false;
        }
    
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(bad[v]) continue;
            dd[v] --;
            if((double)dd[v] < d[v] * mid && in[v]) 
            {
                q.push(v);
                in[v] = false;
            }
        }
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(bad[i]) continue;
        if(in[i]) return true;
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), k = read();
    for(int i = 1; i <= k; i ++ )
    {
        int x = read();
        bad[x] = true;
    }

    for(int i = 1; i <= n; i ++ )
        if(!bad[i])
            c[++ tt] = i;

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        d[a] ++, d[b] ++;
        dd[a] ++, dd[b] ++;
    }

    double l = 0, r = 1;
    while(r - l >= 1e-8)
    {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    check(l);

    int cnt = 0;
    for(int i = 1; i <= n; i ++ ) 
        if(in[i]) cnt ++;

    printf("%d\n", cnt);

    for(int i = 1; i <= n; i ++ )
        if(in[i])
            printf("%d ", i);

    return 0;
}