#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
ll a[N], pos[N], ans[N];
ll cntt[N], imt[N];
queue<ll> change;
vector<ll> nums;
int n, m;
ll imp[N], cnt[N];

struct query
{
    int op, l, r;
    bool operator < (const query& q) const
    {
        if(pos[l] == pos[q.l]) return r < q.r;
        return pos[l] < pos[q.l];
    }
}q[N];

inline ll get(int x)
{
    return nums[x];
}

inline ll calc(int l, int r)
{
    ll res = 0;
    for(int i = l; i <= r; i ++ ) cntt[a[i]] = imt[a[i]] = 0;
    for(int i = l; i <= r; i ++ )
    {
        imt[a[i]] -= get(a[i]) * cntt[a[i]];
        cntt[a[i]] ++;
        imt[a[i]] += get(a[i]) * cntt[a[i]];
        res = max(res, imt[a[i]]);
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        nums.push_back(a[i]);
        pos[i] = (i - 1) / _ + 1;
    }

    int bn = pos[n];

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for(int i = 1; i <= n; i ++ ) a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin(); 

    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        q[i] = {i, l, r};
    }

    sort(q + 1, q + 1 + m);

    for(int i = 1, j = 0; j <= bn; j ++ )
    {
        int br = min(n, _ * j), l = br + 1, r = l - 1, ANSIMP = 0;
        for(; pos[q[i].l] == j; i ++ )
        {
            if(pos[q[i].l] == pos[q[i].r])
            {
                ans[q[i].op] = calc(q[i].l, q[i].r);
                continue;
            }
            while(r < q[i].r)
            {
                r ++;
                change.push(a[r]);
                cnt[a[r]] ++;
                imp[a[r]] += get(a[r]);
                if(ANSIMP < imp[a[r]])
                {
                    ANSIMP = imp[a[r]];
                }
            }
            int lstimp = ANSIMP;
            while(l > q[i].l)
            {
                l --;
                change.push(a[l]);
                cnt[a[l]] ++;
                imp[a[l]] += get(a[l]);
                if(ANSIMP < imp[a[l]])
                {
                    ANSIMP = imp[a[l]];
                }
            }
            ans[q[i].op] = ANSIMP;
            ANSIMP = lstimp;
            while(l <= br)
            {
                cnt[a[l]] --;
                imp[a[l]] -= get(a[l]);
                l ++;
            }
        }
        while(change.size()) cnt[change.front()] = imp[change.front()] = 0, change.pop();
    }

    for(int i = 1; i <= m; i ++ )
        printf("%lld\n", ans[i]);
    
    return 0;
}
