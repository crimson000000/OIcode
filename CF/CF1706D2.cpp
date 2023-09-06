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

const int N = 1e5 + 10;
int cnt[N], a[N];
vector<int> ql[N], qr[N];
int pl[N], pr[N];
int n, m, k;

inline void solve()
{
    for(int i = 1; i <= n; i ++ ) cnt[i] = 0;
    n = read(), k = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        m = max(m, a[i]);
    }
    for(int i = 1; i <= m; i ++ )
    {
        vector<int>().swap(ql[i]);
        vector<int>().swap(qr[i]);
    }
    for(int i = 1; i <= n; i ++ )
    {
        pl[i] = 1, ql[a[i]].push_back(i);
        pr[i] = 1, qr[a[i]].push_back(i);
    }
    int tot = 0;
    int ans = 0x3f3f3f3f;
    for(int l = m, r = m; l >= 0; l -- )
    {
        for(auto x : ql[l])
        {
            if(!cnt[x]) tot ++;
            cnt[x] ++;
            pl[x] = (a[x] / (a[x] / pl[x])) + 1;
            if(pl[x] <= min(a[x], k)) ql[a[x] / pl[x]].push_back(x);
        }
        vector<int>().swap(ql[l]);
        while(tot == n && r >= l)
        {
            ans = min(ans, r - l);
            for(auto i : qr[r])
            {
                cnt[i] --;
                if(!cnt[i]) tot --;
                pr[i] = (a[i] / (a[i] / pr[i])) + 1;
                if(pr[i] <= min(a[i], k)) qr[a[i] / pr[i]].push_back(i);
            }
            vector<int>().swap(qr[r]);
            r --;
        }
    }
    printf("%d\n", ans);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}
