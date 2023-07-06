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
int a[N];
int n;

struct treearray
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }
    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

vector<int> nums;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;

    for(int i = n; i; i -- )
    {
        ans += bit.query(a[i] - 1);
        bit.add(a[i], 1);
    }

    printf("%lld\n", ans);

    int m = read();
    while(m -- )
    {
        int l = read(), r = read();
        if(l > r) swap(l, r);
        for(int i = l; i < r; i ++ )
        {
            ans += (a[i] > a[l]);
            ans += (a[i] < a[r]);
            ans -= (a[i] < a[l]);
            ans -= (a[i] > a[r]);
        }
        swap(a[l], a[r]);
        printf("%lld\n", ans);
    }

    return 0;
}
