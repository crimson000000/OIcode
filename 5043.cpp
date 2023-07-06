#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
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

const int N = 1010 + 10;
int h[N], e[N], ne[N], idx;
vector<unsigned long long> ans[N];
int m, n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline ll hh(ll x)
{
    return x * x * x * 1237123 + 19260817;
}

inline ll f(ll x)
{
    ll cur = hh(x & ((1ull << 31) - 1)) + hh(x >> 31);
    return cur;
}

ll hsh(int x, int fa)
{
    ll res = 0;
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        ll val = hsh(j, x);
        res += f(val);
    }
    return res + 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        memset(h, -1, sizeof h);
        memset(ne, 0, sizeof ne);
        memset(e, 0, sizeof e);
        idx = 0;
        n = read();
        for(int j = 1; j <= n; j ++ )
        {
            int x = read();
            if(x) add(x, j), add(j, x);
        }
        for(int j = 1; j <= n; j ++ ) 
        {
            // cout << hsh(j, j) << ' ';
            ans[i].push_back(hsh(j, j));
        }
        // puts("");

        sort(ans[i].begin(), ans[i].end());
        // for(int i = 1; i <= m; i ++ )
        // {
            // for(auto t : ans[i])
            //     cout << t << ' ';
            // puts("");
        // }

        for(int j = 1; j <= i; j ++ )
        {
            // for(auto t : ans[j])
            //     cout << t << ' ';
            // puts("");
            if(ans[i].size() != ans[j].size()) continue;
            bool flag = true;
            for(int u = 0; u < n; u ++ )
            {
                // cout << ans[i][u] << ' ' << ans[j][u] << endl;
                if(ans[i][u] != ans[j][u])
                {
                    flag = false;
                    break;
                }
            }
        

            if(flag)
            {
                printf("%d\n", j);
                break;
            }
        }
    }

    // for(int i = 1; i <= m; i ++ )
    // {
    //     for(auto t : ans[i])
    //         cout << t << ' ';
    //     puts("");
    // }
    return 0;
}