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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int a[N], pos[N];
queue<int> change;
vector<int> nums;
int t[N];
int n, m, bn;
int st[N], ma[N], ans[N], last[N];

struct query
{
    int op, l, r;
    bool operator < (const query& Q) const
    {
        if(pos[l] == pos[Q.l]) return r < Q.r;
        return pos[l] < pos[Q.l];
    }
}q[N];

int calc(int l, int r)
{
    int res = 0;
    for(int i = l; i <= r; i ++ ) last[a[i]] = 0;
    for(int i = l; i <= r; i ++ ) 
        if(!last[a[i]]) last[a[i]] = i;
        else res = max(res, i - last[a[i]]);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        nums.push_back(a[i]);
        pos[i] = (i - 1) / _ + 1;
    }

    bn = pos[n];

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for(int i = 1; i <= n; i ++ ) a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
    
    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        q[i] = {i, l, r};
    }

    sort(q + 1, q + m + 1);
    for(int i = 1, j = 0; i <= m; j ++ )
    {
        int br = min(n, j * _), l = br + 1, r = l - 1, cnt = 0;
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
                ma[a[r]] = r;
                if(!st[a[r]]) st[a[r]] = r, change.push(a[r]);
                cnt = max(cnt, r - st[a[r]]);
            }
            int tp = cnt;
            while(l > q[i].l)
            {
                l --;
                if(ma[a[l]]) cnt = max(cnt, ma[a[l]] - l);
                else ma[a[l]] = l;
            }
            ans[q[i].op] = cnt;
            while(l <= br)
            {
                if(ma[a[l]] == l) ma[a[l]] = 0;
                l ++;
            }
            cnt = tp;
        }
        while(change.size()) st[change.front()] = ma[change.front()] = false, change.pop();
    }

    for(int i = 1; i <= m; i ++ ) printf("%d\n", ans[i]);
    
    return 0;
}
