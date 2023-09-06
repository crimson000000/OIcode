#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 1e6 + 10;

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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

int p[N], a[N];
int ne[N];
vector<int> nums;
int n, m;
int cnt[N];

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int v)
    {
        for(; x <= N - 5; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    inline void clear(int x)
    {
        for(; x <= n; x += lowbit(x)) c[x] = 0;
    }

    inline void change_p(int l, int r, int v)
    {
        for(int i = l; i <= r; i ++ ) add(p[i], v);
    }

    inline void change_a(int l, int r, int v)
    {
        for(int i = l; i <= r; i ++ ) add(a[i], v);
    }
}bit;

int ans[N], tt;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = read();
    for(int i = 1; i <= m; i ++ )
    {
        int x = read();
        p[x] = i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        nums.emplace_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ ) 
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
    
    for(int i = 1; i <= m; i ++ )
    {
        cnt[i] = bit.query(p[i]);
        bit.add(p[i], 1);
    }

    cnt[m + 1] = 0x3f3f3f3f;

    memset(bit.c, 0, sizeof bit.c);

    for(int i = 2, j = 0; i <= m; i ++ )
    {
        while(j && bit.query(p[i]) != cnt[j + 1]) 
        {
            bit.change_p(i - j, i - ne[j] - 1, -1);
            j = ne[j];
        }
        if(bit.query(p[i]) == cnt[j + 1]) j ++, bit.add(p[i], 1);
        ne[i] = j;
    }

    memset(bit.c, 0, sizeof bit.c);

    for(int i = 1, j = 0; i <= n; i ++ )
    {
        while(j && bit.query(a[i]) != cnt[j + 1])
        {
            bit.change_a(i - j, i - ne[j] - 1, -1);
            j = ne[j];
        }
        if(bit.query(a[i]) == cnt[j + 1]) j ++, bit.add(a[i], 1);
        if(j == m) 
        {
            ans[++ tt] = i - m + 1;
        }
    }

    printf("%d\n", tt);
    for(int i = 1; i <= tt; i ++ )
        printf("%d ", ans[i]);
    puts("");

    return 0;
}