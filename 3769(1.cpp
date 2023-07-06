#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 1e5 + 10;
struct ele
{
    int ok, a, b, c, d, w;
    int id, ans;
}e[N], e1[N];
int top;
vector<int> nums, nums2;
int pos1[N], pos2[N];
int n;

inline bool cmpa(ele a, ele b)
{
    if(a.a != b.a) return a.a < b.a;
    if(a.b != b.b) return a.b < b.b;
    if(a.c != b.c) return a.c < b.c;
    return a.d < b.d;
}

inline bool cmpb(ele a, ele b)
{
    if(a.b != b.b) return a.b < b.b;
    if(a.a != b.a) return a.a < b.a;
    if(a.c != b.c) return a.c < b.c;
    return a.d < b.d;
}

inline bool cmpc(ele a, ele b)
{
    return a.c < b.c;
}

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] = max(c[x], val);
    }

    inline void clear(int x)
    {
        for(; x <= n; x += lowbit(x)) c[x] = 0;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res = max(res, c[x]);
        return res;
    }
} bit;

void cdq2(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq2(l, mid);

    sort(e + l, e + mid + 1, cmpc);
    sort(e + mid + 1, e + r + 1, cmpc);

    for(int i = l, j = mid + 1; j <= r; j ++ )
    {
        while(i <= mid && e[i].c <= e[j].c)
        {
            if(e[i].ok) bit.add(e[i].d, e[i].ans);
            i ++;
        }
        if(!e[j].ok) e[j].ans = max(e[j].ans, bit.query(e[j].d) + e[j].w);
    }

    for(int i = l; i <= r; i ++ ) bit.clear(e[i].d);
    for(int i = l; i <= r; i ++ ) e1[pos2[e[i].id]] = e[i];
    for(int i = l; i <= r; i ++ ) e[i] = e1[i];
    cdq2(mid + 1, r);
}

void cdq1(int l, int r)
{
    if(l == r) return;

    int mid = l + r >> 1;
    cdq1(l, mid);
    
    for(int i = l; i <= r; i ++ )
        e[i].ok = (i <= mid);

    sort(e + l, e + r + 1, cmpb);
    for(int i = l; i <= r; i ++ ) pos2[e[i].id] = i;

    cdq2(l, r);
    
    for(int i = l; i <= r; i ++ ) e1[pos1[e[i].id]] = e[i];
    for(int i = l; i <= r; i ++ ) e[i] = e1[i];

    cdq1(mid + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int a = read(), b = read(), c = read(), d = read();
        e[i] = {0, a, b, c, d, 1, 0, 0};
        nums.push_back(d);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    
    for(int i = 1; i <= n; i ++ )
        e[i].d = lower_bound(nums.begin(), nums.end(), e[i].d) - nums.begin() + 1;

    sort(e + 1, e + n + 1, cmpa);
    top = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(e[i].a != e[i - 1].a || e[i].b != e[i - 1].b || e[i].c != e[i - 1].c || e[i].d != e[i - 1].d)
            e[++ top] = e[i];
        else e[top].w += e[i].w;          
    }
    
    // cout << top << endl;

    for(int i = 1; i <= top; i ++ )
    {
        e[i].id = i;
        e[i].ans = e[i].w;
        pos1[e[i].id] = i;
        // printf("%d %d %d %d %d\n", e[i].a, e[i].b, e[i].c, e[i].d, e[i].w);
    }
    
    cdq1(1, top);

    int maxn = 0;
    for(int i = 1; i <= n; i ++ ) maxn = max(maxn, e[i].ans);
    cout << maxn << endl;

    return 0;
}
