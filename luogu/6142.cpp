#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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
int h[N], e[N], ne[N], idx;
int n;
int mid;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool flag;
inline int dfs(int u, int fa)
{
    multiset<int> s;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        int t = dfs(v, u);
        s.insert(t + 1);
    }

    // printf("now is %d: ", u);
    // for(auto a : s) printf("%d ", a);
    // puts("");

    if((u == 1 && (s.size() & 1)) || (u != 1 && !(s.size() & 1))) s.insert(0);

    if(s.size() & 1)
    {
        int cnt = 0, top = 0;
        while(s.size())
        {
            auto it = s.lower_bound(0);
            int p = *it;
            s.erase(it);

            it = s.lower_bound(mid - p);
            if(it == s.end()) cnt ++, top = max(top, p);
            else
            {
                s.erase(it);
            }
        }
        if(cnt > 1) flag = false;
        return top;
    }
    else
    {
        while(s.size())
        {
            auto it = s.lower_bound(0);
            int p = *it;
            s.erase(it);

            it = s.lower_bound(mid - p);
            if(it == s.end()) flag = false;
            else
            {
                s.erase(it);
            }
        }
        return 0;
    }
}

inline bool check()
{
    flag = true;
    dfs(1, 1);
    return flag;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    int l = 0, r = 1e6;
    while(l < r)
    {
        mid = l + r + 1 >> 1;
        if(check()) l = mid;
        else r = mid - 1;
    }

    // for(int i = 0; i <= 10; i ++ )
    // {
    //     mid = i;
    //     cout << check() << endl;
    // }

    cout << l << endl;

    return 0;
}