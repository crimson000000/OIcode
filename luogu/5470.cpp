#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
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
int a[N], b[N], s[N];
int id[N];
ll ans;
int n, k, l;

namespace nd
{
    struct nodeA
    {
        int id;
        nodeA(int _id): id(_id) {}
        bool operator < (const nodeA x) const
        {
            return a[id] < a[x.id];
        }
    };

    struct nodeB
    {
        int id;
        nodeB(int _id): id(_id) {}
        bool operator < (const nodeB x) const
        {
            return b[id] < b[x.id];
        }
    };

    struct nodeC
    {
        int id;
        nodeC(int _id): id(_id) {}
        bool operator < (const nodeC x) const
        {
            return a[id] + b[id] < a[x.id] + b[x.id];
        }
    };
}

using namespace nd;

// H1 放 a 里面没选的，F1 放 a 里面 b 已经跑了的
priority_queue<nodeA> H1, F1;
// H2 同理
priority_queue<nodeB> H2, F2;
// H3 放都没选的
priority_queue<nodeC> H3;

inline bool cmp1(int x, int y)
{
    return a[x] > a[y];
}

inline bool cmp2(int x, int y)
{
    return b[x] > b[y];
}

inline void work(int t)
{
    ans = 0;
    for(int i = 1; i <= n; i ++ ) id[i] = i;
    sort(id + 1, id + n + 1, cmp1);
    for(int i = 1; i <= t; i ++ )
        s[id[i]] ++, ans += a[id[i]];
    sort(id + 1, id + n + 1, cmp2);
    for(int i = 1; i <= t; i ++ )
        s[id[i]] += 2, ans += b[id[i]];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read(), k = read(), l = read();
        for(int i = 1; i <= n; i ++ ) a[i] = read();
        for(int i = 1; i <= n; i ++ ) b[i] = read(), s[i] = 0;

        work(k - l);
        
        while(H1.size()) H1.pop();
        while(H2.size()) H2.pop();
        while(H3.size()) H3.pop();
        while(F1.size()) F1.pop();
        while(F2.size()) F2.pop();

        int now = 0;
        for(int i = 1; i <= n; i ++ )
        {
            if(!s[i])
            {
                H1.emplace(i);
                H2.emplace(i);
                H3.emplace(i);
            }
            else if(s[i] == 1) H2.emplace(i), F2.emplace(i);
            else if(s[i] == 2) H1.emplace(i), F1.emplace(i);
            else now ++;
        }

        while(l -- )
        {
            while(H1.size() && (s[H1.top().id] & 1)) H1.pop();
            while(H2.size() && (s[H2.top().id] & 2)) H2.pop();
            while(F1.size() && (s[F1.top().id] != 2)) F1.pop();
            while(F2.size() && (s[F2.top().id] != 1)) F2.pop();
            while(H3.size() && s[H3.top().id]) H3.pop();

            if(now)
            {
                now --;
                int x = H1.top().id, y = H2.top().id;
                ans += a[x] + b[y];
                s[x] |= 1, s[y] |= 2;

                if(s[x] != 3) F2.emplace(x);
                if(s[y] != 3) F1.emplace(y);

                if(x == y) now ++;
                else
                {
                    if(s[x] == 3) now ++;
                    if(s[y] == 3) now ++;
                }

                continue;
            }

            int x = 0, y = 0;
            int v1 = 0, v2 = 0, v3 = 0;
            int vmax = 0;
            if(F2.size())
            {
                x = H1.top().id, y = F2.top().id;
                v1 = a[x] + b[y];
                // c1 = (s[x] != 3 ? 1 : 0);
            }
            if(F1.size())
            {
                x = F1.top().id, y = H2.top().id;
                v2 = a[x] + b[y];
                // c2 = (s[y] != 3 ? 1 : 0);
            }
            if(H3.size())
            {
                x = H3.top().id;
                v3 = a[x] + b[x];
            }

            vmax = max({v1, v2, v3});
            ans += vmax;

            // if(v1 == v2 && v1 == vmax)
            // {
            //     // cout << c1 << ' ' << c2 << endl;
            //     if(c1 >= c2)
            //     {
            //         x = H1.top().id, y = F2.top().id;
            //         s[x] |= 1, s[y] |= 2;
            //         if(s[x] != 3) F2.emplace(x);
            //         else now ++;
            //     }
            //     else
            //     {
            //         x = F1.top().id, y = H2.top().id;
            //         s[x] |= 1, s[y] |= 2;
            //         if(s[y] != 3) F1.emplace(y);
            //         else now ++;
            //     }
            //     continue;
            // }
            if(v1 == vmax)
            {
                x = H1.top().id, y = F2.top().id;
                s[x] |= 1, s[y] |= 2;
                if(s[x] != 3) F2.emplace(x);
                else now ++;
                continue;
            }
            if(v2 == vmax)
            {
                x = F1.top().id, y = H2.top().id;
                s[x] |= 1, s[y] |= 2;
                if(s[y] != 3) F1.emplace(y);
                else now ++;
                continue;
            }
            if(v3 == vmax)
            {
                x = H3.top().id;
                s[x] |= 3;
                H3.pop();
                continue;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
