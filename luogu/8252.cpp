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

const int N = 1e6 + 10;
int n;
int vis[N];

struct peo
{
    int k, id;
    vector<int> a;
    bool operator < (const peo & x) const
    {
        return k > x.k;
    }
}p[N];

inline void solve()
{
    for(int i = 1; i <= n; i ++ ) vis[i] = 0;
    for(int i = 1; i <= n; i ++ ) p[i].a.clear();

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        p[i].k = read();
        p[i].id = i;
        for(int j = 0; j < p[i].k; j ++ )
        {
            int x = read();
            p[i].a.push_back(x);
        }
        if(p[i].k) sort(p[i].a.begin(), p[i].a.end());
    }

    sort(p + 1, p + n + 1);
    bool suc = false;
    for(int i = 1; i <= n && !suc; i ++ )
    {
        // for(int j = 1; j <= n; j ++ ) cout << vis[i] << ' ';
        // puts("");
        int f1 = 0;
        for(auto x : p[i].a)
        {
            if(vis[x])
            {
                f1 = vis[x];
                break;
            }
        }

        if(!f1)
        {
            for(auto x : p[i].a) vis[x] = i;
            continue;
        }

        for(auto x : p[i].a)
        {
            if(vis[x] != f1)
            {
                puts("YES");
                printf("%d %d\n", p[i].id, p[max(vis[x], f1)].id);
                suc = true;
                break;
            }
        }

        for(auto x : p[i].a) vis[x] = i;
    }

    if(!suc) puts("NO");
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
/*
感觉只会 n3/w 的大暴力/kk
怎么感觉和量子通信这么像
感觉应该不一样，那个只有 16 位
应该不是手写bitset
估计就找性质构造吧
异或哈希只能判断相等吧
*/