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
struct edge
{
    int a, b, c;
    bool black;
    bool operator < (const edge& e) const
    {
        return (c < e.c) || ((c == e.c) && black < e.black);
    }
}bl[N], wh[N], ed[N];
int bcnt, wcnt;

int n, m, k;

template <class T>
inline void merge(T a[], T b[], int sa, int sb, T c[])
{
    int i = 1, j = 1, k = 1;
    while(i <= sa && j <= sb)
    {
        if(a[i] < b[j]) c[k ++ ] = a[i ++ ];
        else c[k ++ ] = b[j ++ ];
    }
    while(i <= sa) c[k ++ ] = a[i ++ ];
    while(j <= sb) c[k ++ ] = b[j ++ ];
}

int p[N];
inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline bool check(int mid)
{
    for(int i = 1; i <= wcnt; i ++ ) wh[i].c -= mid;
    merge(bl, wh, bcnt, wcnt, ed);
    // for(int i = 1; i <= m; i ++ ) printf("%d ", ed[i].c);
    // puts("");
    for(int i = 1; i <= n; i ++ ) p[i] = i;

    int cnt = 0;
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(find(a) == find(b)) continue;
        p[find(a)] = find(b);
        if(!ed[i].black) cnt ++;
    }

    for(int i = 1; i <= wcnt; i ++ ) wh[i].c += mid;
    return cnt >= k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read() + 1, b = read() + 1, c = read(), d = read();
        if(d == 0) wh[++ wcnt] = {a, b, c, false};
        else bl[++ bcnt] = {a, b, c, true};
    }

    sort(wh + 1, wh + wcnt + 1);
    sort(bl + 1, bl + bcnt + 1);

    int l = -100, r = 100;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }

    for(int i = 1; i <= wcnt; i ++ ) wh[i].c -= l;
    merge(bl, wh, bcnt, wcnt, ed);
    for(int i = 1; i <= n; i ++ ) p[i] = i;

    int res = 0;
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(find(a) == find(b)) continue;
        p[find(a)] = find(b);
        res += c;
    }

    printf("%d\n", res + k * l);

    return 0;
}