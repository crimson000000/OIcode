#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 5e5 + 10;

inline int read1()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline ll read2()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
PII f[N][21];
ll a[N], s[N];
struct state
{
    int o, l, r, k;
    bool operator < (const state& V) const
    {
        return s[k] - s[o - 1] < s[V.k] - s[V.o - 1];
    }
}tmp1, tmp2;

int n, k, L, R;
ll ans = 0;
priority_queue<state> heap;

inline void ST_pre()
{
    for(int i = 1; i <= n; i ++ ) f[i][0] = {s[i], i};

    for(int i = 1; i < 21; i ++ )
        for(int j = 1; j + (1 << (i - 1)) <= n; j ++ )
            f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
}

inline PII getmin(int l, int r)
{
    if(l > r) swap(l, r);
    if(l <= 0) l = 1;
    int k = log2(r - l + 1);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif
    n = read1(), k = read1(), L = read1(), R = read1();

    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read2();
        s[i] = s[i - 1] + a[i];
    }

//    for(int i = 1; i <= n; i ++ ) cout << s[i] << " ";
//    cout << endl;

    ST_pre();

    for(int o = 1; o + L - 1 <= n; o ++ )
    {
        tmp1.o = o;
        tmp1.l = o + L - 1;
        tmp1.r = min(n, o + R - 1);
        tmp1.k = getmin(tmp1.l, tmp1.r).second;
        heap.push(tmp1);
    }

    for(int i = 1; i <= k; i ++ )
    {
        auto t = heap.top();
        heap.pop();
        ans += s[t.k] - s[t.o - 1];

//        printf("%d %d %d %d %d\n", t.o, t.k, t.l, t.r, ans);
        
        if(t.k != t.r)
        {
            tmp1 = t;
            tmp1.l = t.k + 1;
            tmp1.k = getmin(tmp1.l, tmp1.r).second;
            heap.push(tmp1);
        }
        if(t.k != t.l)
        {
            tmp1 = t;
            tmp1.r = t.k - 1;
            tmp1.k = getmin(tmp1.l, tmp1.r).second;
            heap.push(tmp1);
        }
    }

    cout << ans << endl;
    return 0;
}