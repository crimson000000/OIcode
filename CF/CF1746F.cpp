#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

mt19937 rnd(time(0));

const int N = 3e5 + 10;
const int M = 20;
int buc[N << 1];
int a[N], b[N];
int n, m;
vector<int> nums;

struct qu
{
    int op, l, r, k;
}q[N];

bool ans[N];

struct ta
{
    ll c[N];
    #define lowbit(x) x & -x
    void add(int x, ll v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    ll query(int x)
    {
        ll res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    void clear()
    {
        memset(c, 0, sizeof c);
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        nums.push_back(a[i]);
    }

    for(int i = 1; i <= m; i ++ ) 
    {
        int op = read();
        if(op == 1)
        {
            int p = read(), x = read();
            q[i] = {op, p, x, 0};
            nums.push_back(x);
        }
        else
        {
            int l = read(), r = read(), k = read();
            q[i] = {op, l, r, k};
            ans[i] = true;
        }
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
        // cout << a[i] << ' ';
    }

    for(int i = 1; i <= m; i ++ )
        if(q[i].op == 1)
            q[i].r = lower_bound(nums.begin(), nums.end(), q[i].r) - nums.begin() + 1;

    for(int T = 0; T <= 30; T ++ )
    {
        memcpy(b, a, sizeof a);
        bit.clear();
        for(int i = 1; i <= int(nums.size()); i ++ ) buc[i] = rnd();
        for(int i = 1; i <= n; i ++ )
            bit.add(i, buc[b[i]]);

        for(int i = 1; i <= m; i ++ )
        {
            int op = q[i].op;
            if(op == 1)
            {
                int p = q[i].l, x = q[i].r;
                bit.add(p, -buc[b[p]]);
                b[p] = x;
                bit.add(p, buc[b[p]]);
            }
            else
            {
                if(ans[i])
                {
                    int l = q[i].l, r = q[i].r, k = q[i].k;
                    if((r - l + 1) % k)
                    {
                        ans[i] = false;
                        continue;
                    }
                    ll sum = bit.query(r) - bit.query(l - 1);
                    if(sum % k)
                    {
                        ans[i] = false;
                        continue;
                    }
                }
            }
        }
    }

    for(int i = 1; i <= m; i ++ )
        if(q[i].op == 2)
            puts(ans[i] ? "YES" : "NO");

    return 0;
}