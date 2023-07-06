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
int sa[N], cnt[N], rk[N], id[N], oldrk[N], height[N];
int a[N];
multiset<int> t;
int ans;
int n, k, m, p;

inline bool cmp(int x, int y, int w)
{
    return (oldrk[x] == oldrk[y]) && (oldrk[x + w] == oldrk[y + w]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    k --;
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        rk[i] = a[i];
    }

    m = N - 2;
    for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
    for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = n; i; i -- ) sa[cnt[rk[i]] -- ] = i;
    swap(oldrk, rk);
    for(int i = 1; i <= n; i ++ )
    {
        if(cmp(sa[i], sa[i - 1], 0))
            rk[sa[i]] = p;
        else rk[sa[i]] = ++ p;
    }

    for(int w = 1; w < n; w <<= 1)
    {
        m = p;
        p = 0;
        for(int i = n; i > n - w; i -- ) id[++ p] = i;
        for(int i = 1; i <= n; i ++ )
            if(sa[i] > w)
                id[++ p] = sa[i] - w;
        
        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= n; i ++ ) cnt[rk[id[i]]] ++;
        for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = n; i; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];

        p = 0;
        swap(rk, oldrk);
        for(int i = 1; i <= n; i ++ )
        {
            if(cmp(sa[i], sa[i - 1], w))
                rk[sa[i]] = p;
            else rk[sa[i]] = ++ p;
        }
    }

    for(int i = 1, j = 0; i <= n; i ++ )
    {
        if(j) j --;
        while(a[i + j] == a[sa[rk[i] - 1] + j]) j ++;
        height[rk[i]] = j;
    }

    for(int i = 1; i <= n; i ++ )
    {
        t.insert(height[i]);
        if(i > k) t.erase(t.find(height[i - k]));
        ans = max(ans, *t.begin());
    }

    cout << ans << endl;

    return 0;
}