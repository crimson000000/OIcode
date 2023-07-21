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
int sa[N], rk[N], oldrk[N], id[N], cnt[N], height[N];
int f[20][N];
int a[N];
set<int> s;
vector<int> nums;
ll ans;
int n, m, p, w;

inline void build()
{
    m = n;
    for(int i = 1; i <= n; i ++ ) rk[i] = a[i];
    for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
    for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i -- ) sa[cnt[rk[i]] -- ] = i;
    swap(rk, oldrk);
    for(int i = 1; i <= n; i ++ )
    {
        if(oldrk[sa[i]] == oldrk[sa[i - 1]]) 
            rk[sa[i]] = p;
        else rk[sa[i]] = ++ p;
    }

    for(w = 1; w < n; w <<= 1)
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
        for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];
        swap(rk, oldrk);
        p = 0;
        
        for(int i = 1; i <= n; i ++ )
        {
            if(oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
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

    // for(int i = 1; i <= n; i ++ ) cout << height[i] << ' ';
    // puts("");

    for(int i = 1; i <= n; i ++ ) f[0][i] = height[i];
    for(int i = 1; i <= 18; i ++ )
        for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
            f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
}

inline int query(int l, int r)
{
    int t = log2(r - l + 1);
    return min(f[t][l], f[t][r - (1 << t) + 1]);
}

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
        nums.emplace_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
    }

    reverse(a + 1, a + n + 1);

    build();

    for(int i = n; i >= 1; i -- )
    {
        s.insert(rk[i]);
        auto it = s.find(rk[i]);
        int k = 0;
        if(it != s.begin())
        {
            int p = *(-- it);
            k = query(p + 1, rk[i]);
            it ++;
        }
        it ++;
        if(it != s.end())
        {
            int p = *it;
            k = max(k, query(rk[i] + 1, p));
        }
        ans += n + 1 - i - k;
        printf("%lld\n", ans);
    }

    return 0;
}
