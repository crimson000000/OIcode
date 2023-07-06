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
    bool A;
    bool operator < (const edge& e) const
    {
        return c < e.c || (c == e.c && A < e.A);
    }
}A[N], B[N], ed[N];
int deg[N];
int acnt, bcnt;
int cnt, ans;

int n, m, s, k;

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

inline void check(int mid)
{
    for(int i = 1; i <= acnt; i ++ ) A[i].c += mid;
    merge(A, B, acnt, bcnt, ed);
    for(int i = 1; i <= acnt; i ++ ) A[i].c -= mid;
    // for(int i = 1; i <= acnt; i ++ ) ed[i] = {A[i].a, A[i].b, A[i].c + mid, true};
    // for(int i = 1; i <= bcnt; i ++ ) ed[i + acnt] = B[i];
    // sort(ed + 1, ed + m + 1);

    for(int i = 1; i <= n; i ++ ) p[i] = i;

    cnt = ans = 0;
    int cntt = 0;
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(find(a) == find(b)) continue;
        ans += c;
        p[find(a)] = find(b);
        cntt ++;
        if(ed[i].A) cnt ++;
    }

    if(cntt != n - 1)
    {
        puts("Impossible");
        exit(0);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), s = read(), k = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        deg[a] ++, deg[b] ++;
        if(a == s || b == s)
            A[++ acnt] = {a, b, c, true};
        else B[++ bcnt] = {a, b, c, false};
    }

    if(deg[s] < k) 
    {
        puts("Impossible");
        exit(0);
    }

    sort(A + 1, A + acnt + 1);
    sort(B + 1, B + bcnt + 1);

    int l = -1e9, r = 1e9;
    if(check(r), cnt > k) 
    {
        puts("Impossible");
        exit(0);
    }
    // while(l < r)
    // {
    //     int mid = l + r + 1 >> 1;
    //     check(mid);
    //     if(cnt < k) r = mid - 1;
    //     else l = mid;
    // } 
    int anss;
    while(l <= r)
    {
        int mid = l + r >> 1;
        check(mid);
        if(cnt <= k) r = mid-1,anss=mid;
        else l = mid + 1;
    } 
    check(anss);
    printf("%d\n", ans - k * anss); 
    // check(l);
    // printf("%d\n", ans - k * l);

    return 0;
}