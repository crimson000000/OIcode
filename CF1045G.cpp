#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef double ld;

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
int n, k;
ll ans;
int x[N];
struct node
{
    int r, p, pos;
    int lp, rp;
}a[N], tmp[N];
vector<int> nums;

inline bool cmpr(node a, node b)
{
    return a.r > b.r;
}

struct ta
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int val)
    {
        for(; x <= N - 5; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

inline void cdq(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;

    cdq(l, mid), cdq(mid + 1, r);

    int L, R, x;
    for(L = l, R = l - 1, x = mid + 1; x <= r; x ++ )
    {
        while(L <= mid && a[L].p < a[x].p - k)
        {
            bit.add(a[L].pos, -1);
            L ++;
        }

        while(R < mid && a[R + 1].p <= a[x].p + k)
        {
            R ++;
            bit.add(a[R].pos, 1);
        }
        
        ans += bit.query(a[x].rp) - bit.query(a[x].lp - 1);
    }

    for(int i = L; i <= R; i ++ ) bit.add(a[i].pos, -1);

    int i = l, j = mid + 1, cur = 0;
    while(i <= mid && j <= r)
    {
        if(a[i].p <= a[j].p) tmp[++ cur] = a[i], i ++ ;
        else tmp[++ cur] = a[j], j ++ ;
    }
    while(i <= mid) tmp[++ cur] = a[i], i ++ ;
    while(j <= r) tmp[++ cur] = a[j], j ++ ;
    for(int i = l, j = 1; j <= cur; i ++, j ++ ) a[i] = tmp[j];
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), k = read();

    for(int i = 1; i <= n; i ++ )
    {
        x[i] = read(), a[i].r = read(), a[i].p = read();
        a[i].lp = x[i] - a[i].r;
        a[i].rp = x[i] + a[i].r;
        nums.push_back(x[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
    {
        a[i].pos = lower_bound(nums.begin(), nums.end(), x[i]) - nums.begin() + 1;
        a[i].lp = lower_bound(nums.begin(), nums.end(), x[i] - a[i].r) - nums.begin() + 1;
        a[i].rp = upper_bound(nums.begin(), nums.end(), x[i] + a[i].r) - nums.begin();
    }

    sort(a + 1, a + n + 1, cmpr);
    cdq(1, n);

    cout << ans << endl;

    return 0;
}
