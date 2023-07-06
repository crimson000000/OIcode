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

const int N = 1e5 + 10;
char s[N];
int n;
int lg2[N];
int f[N], g[N];

struct SA
{
    int sa[N], rk[N], oldrk[N], cnt[N], id[N], height[N];
    int f[17][N];

    void clear()
    {
        memset(sa, 0, sizeof sa);
        memset(rk, 0, sizeof rk);
        memset(oldrk, 0, sizeof oldrk);
        memset(cnt, 0, sizeof cnt);
        memset(id, 0, sizeof id);
        memset(height, 0, sizeof height);
        memset(f[0], 0, sizeof f[0]);
    }

    inline bool cmp(int x, int y, int w)
    {
        return (oldrk[x] == oldrk[y]) && (oldrk[x + w] == oldrk[y + w]);
    }

    void build(int n)
    {
        int m = 127, p = 0;
        for(int i = 1; i <= n; i ++ ) rk[i] = s[i];
        for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
        for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i -- ) sa[cnt[rk[i]] -- ] = i;

        swap(rk, oldrk);
        for(int i = 1; i <= n; i ++ )
        {
            rk[sa[i]] = cmp(sa[i], sa[i - 1], 0) ? p : ++ p; 
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
            for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];
            
            swap(rk, oldrk);
            p = 0;
            for(int i = 1; i <= n; i ++ )
            {
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++ p;
            }
        }

        // int m, p, i, w;
        // m = 127;
        // for(int i = 1; i <= n; i ++ ) rk[i] = s[i];

        // for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
        // for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        // for(int i = n; i >= 1; i -- ) sa[cnt[rk[i]] -- ] = i;
        // memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        // for(p = 0, i = 1; i <= n; i ++ )
        // {
        //     if(oldrk[sa[i]] == oldrk[sa[i - 1]])
        //         rk[sa[i]] = p;
        //     else rk[sa[i]] = ++ p;
        // }

        // for(w = 1; w < n; w <<= 1)
        // {
        //     m = p;
        //     for(p = 0, i = n; i > n - w; i -- ) id[++ p] = i;
        //     for(i = 1; i <= n; i ++ )
        //         if(sa[i] > w)
        //             id[++ p] = sa[i] - w;

        //     // memset(cnt, 0, sizeof cnt);
        //     // memcpy(id + 1, sa + 1, n * sizeof(int));
        //     // for(int i = 1; i <= n; i ++ ) ++ cnt[rk[id[i] + w]];
        //     // for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        //     // for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i] + w]] -- ] = id[i];

        //     memset(cnt, 0, sizeof cnt);
        //     for(int i = 1; i <= n; i ++ ) ++ cnt[rk[id[i]]];
        //     for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        //     for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];

        //     memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        //     for(p = 0, i = 1; i <= n; i ++ )
        //     {
        //         if(oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
        //             rk[sa[i]] = p;
        //         else rk[sa[i]] = ++ p;
        //     }
        // }

        for(int i = 1, j = 0; i <= n; i ++ )
        {
            if(j) j --;
            while(s[i + j] == s[sa[rk[i] - 1] + j]) j ++;
            height[rk[i]] = j;
        }
        
        for(int i = 1; i <= n; i ++ ) f[0][i] = height[i];
        for(int i = 1; i <= 16; i ++ )
            for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
                f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
    }

    inline int query(int l, int r)
    {
        int k = lg2[r - l + 1];
        return min(f[k][l], f[k][r - (1 << k) + 1]);
    }

    inline int lcp(int a, int b)
    {
        int l = rk[a], r = rk[b];
        if(l > r) swap(l, r);
        l ++;
        return query(l, r);
    }
}sa1, sa2;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    lg2[0] = -1;
    for(int i = 1; i < N; i ++ ) lg2[i] = lg2[i >> 1] + 1;

    int T = read();
    while(T -- )
    {
        sa1.clear();
        sa2.clear();

        scanf("%s", s + 1);
        
        n = strlen(s + 1);
        sa1.build(n);

        reverse(s + 1, s + n + 1);
        sa2.build(n);

        // for(int i = 1; i <= n; i ++ ) cout << sa1.sa[i] << ' ';
        
        for(int i = 0; i <= n; i ++ ) f[i] = g[i] = 0;
        for(int w = 1; w <= (n >> 1); w ++ )
        {
            for(int i = w; i <= n; i += w)
            {
                int l = i, r = i + w;
                int lcp = min(w, sa1.lcp(l, r));
                int lcs = min(w - 1, sa2.lcp(n - l + 2, n - r + 2));
                if(lcp + lcs >= w)
                {
                    int cov = lcp + lcs - w + 1;
                    f[r + lcp - cov] ++, f[r + lcp] --;
                    g[l - lcs] ++, g[l - lcs + cov] --;
                }
            }
        }
        for(int i = 1; i <= n; i ++ ) f[i] += f[i - 1], g[i] += g[i - 1];
        ll ans = 0;
        for(int i = 1; i < n; i ++ ) ans += f[i] * g[i + 1];
        printf("%lld\n", ans);
    }

    return 0;
}
