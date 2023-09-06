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
int a[N], siz[N], p[N];
int n, m, ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    siz[a] ++;
}

inline void merge(int &x, int &y)
{
    if(x == y) return;
    if(siz[x] > siz[y]) swap(x, y);
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        ans -= (a[j - 1] == y) + (a[j + 1] == y);
    }
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        a[j] = y;
        if(ne[i] == -1)
        {
            ne[i] = h[y];
            h[y] = h[x];
            break;
        }
    }
    siz[y] += siz[x], siz[x] = 0;
    h[x] = -1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        add(a[i], i);
    }

    for(int i = 1; i <= n; i ++ )
        if(a[i] != a[i - 1])
            ans ++;

    for(int i = 0; i < N - 2; i ++ ) p[i] = i;

    while(m -- )
    {
        int op = read();
        if(op == 2) printf("%d\n", ans);
        else
        {
            int x = read(), y = read();
            merge(p[x], p[y]);
        }
    }

    return 0;
}