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
struct zb
{
    ll a, b;
    ll c, d;
    bool operator < (const zb& t) const
    {
        if(c != t.c) return c > t.c;
        if(d != t.d) return d > t.d;
        if(a != t.a) return a > t.a;
        return b > t.b;
    } 
}p[N];
int n;
ll a, b;
ll ans1, ans2;

inline bool cmp(zb x, zb y)
{
    if(x.a != y.a) return x.a < y.a;
    if(x.b != y.b) return x.b < y.b;
    if(x.c != y.c) return x.c < y.c;
    return x.d < y.d;
}

priority_queue<zb> heap;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int jimmy_ta_ma_de_wsm_xia_ke_lai_ji_fang_a_wocaonimade = read();

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        p[i].a = read(), p[i].c = read();
        p[i].b = read(), p[i].d = read();
    }

    sort(p + 1, p + n + 1, cmp);
    a = 0;
    
    for(int i = 1; i <= n; i ++ )
    {
        if(p[i].a > a)
            ans1 += p[i].a - a, a = p[i].a;
        a += p[i].b;
    }
    
    cout << ans1 << ' ';

    for(int i = 1; i <= n; i ++ )
    {
        while(p[i].a > ans1)
        {
            if(b < heap.top().c)
            {
                ans2 += heap.top().c - b, b = heap.top().c;
            }
            b += heap.top().d, ans1 += heap.top().b;
            heap.pop();
        }
        if(p[i].a <= ans1)
        {
            heap.emplace(p[i]);
        }
        if(i == n)
        {
            while(heap.size())
            {
                if(b < heap.top().c)
                {
                    ans2 += heap.top().c - b, b = heap.top().c;
                }
                b += heap.top().d;
                heap.pop();
            }
        }
    }

    cout << ans2 << endl;

    return 0;
}
