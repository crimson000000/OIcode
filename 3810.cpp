#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) x & -x
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

const int N = 2e5 + 10;

namespace arr
{
    int mx;
    int c[N];

    inline void add(int x, int val)
    {
        for(; x <= mx; x += lowbit(x))
            c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}

struct ele
{
    int a, b, c, cnt, ans;
}e[N], ue[N];

int ans[N];
int m, top, n, mv;

bool cmp1(ele a, ele b)
{
    if(a.a == b.a)
    {
        if(a.b == b.b) return a.c < b.c;
        return a.b < b.b;
    }
    return a.a < b.a;
}

bool cmp2(ele a, ele b)
{
    if(a.b == b.b) return a.c < b.c;
    return a.b < b.b;
}

void solve(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    solve(l, mid), solve(mid + 1, r);

    sort(ue + l, ue + mid + 1, cmp2);
    sort(ue + mid + 1, ue + r + 1, cmp2);

    int i = l, j = mid + 1;
    while(j <= r)
    {
        while(i <= mid && ue[i].b <= ue[j].b)
        {
            arr::add(ue[i].c, ue[i].cnt);
            i ++;
        }
        ue[j].ans += arr::query(ue[j].c);
        j ++;
    }

    for(int k = l; k < i; k ++ ) arr::add(ue[k].c, -ue[k].cnt);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), mv = read();
    arr::mx = mv;

    for(int i = 1; i <= n; i ++ )
    {
        int a = read(), b = read(), c = read();
        e[i] = {a, b, c, 0, 0};
    }

    sort(e + 1, e + 1 + n, cmp1);
    for(int i = 1; i <= n; i ++ )
    {
        top ++;
        if(e[i].a != e[i + 1].a || e[i].b != e[i + 1].b || e[i].c != e[i + 1].c)
        {
            m ++;
            ue[m] = {e[i].a, e[i].b, e[i].c, top, 0};
            top = 0;
        }
    }

    solve(1, m);

    for(int i = 1; i <= m; i ++ ) ans[ue[i].ans + ue[i].cnt - 1] += ue[i].cnt;
    for(int i = 0; i < n; i ++ ) printf("%d\n", ans[i]);
    
    return 0;
}
