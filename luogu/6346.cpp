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
struct peo
{
    ll a, b;
    bool operator < (const peo t) const 
    {
        if(a != t.a) return a < t.a;
        return b < t.b;
    }
}p[N];
int n;
ll res, maxn;
ll ans;
priority_queue<int, vector<int>, greater<int>> heap;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        res = maxn = ans = 0;
        while(heap.size()) heap.pop();
        
        n = read();
        for(int i = 1; i <= n; i ++ )
        {
            p[i].a = read(), p[i].b = read();
            ans += p[i].b;
        }
        
        sort(p + 1, p + 1 + n);

        for(int i = n; i; i -- )
        {
            res += p[i].b;
            heap.emplace(p[i].b);
            if(p[i].a > n - heap.size())
                res -= heap.top(), heap.pop();
            maxn = max(maxn, res);
        }

        cout << ans - maxn << endl;
    }

    return 0;
}
