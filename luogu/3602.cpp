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
struct seg
{
    int x, y;
    bool operator < (const seg& a) const
    {
        return x < a.x;
    }
}a[N], b[N];
multiset<int> t;
int n, m;
int ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    ans = n;
    for(int i = 1; i <= n; i ++ ) a[i].x = read(), a[i].y = read();
    for(int i = 1; i <= m; i ++ ) b[i].x = read(), b[i].y = read();

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    
    for(int i = 1, j = 1; i <= m; i ++ )
    {
        while(j <= n && a[j].x <= b[i].x)
        {
            t.insert(a[j].y);
            j ++;
        }
        while(t.size() && *(t.begin()) < b[i].x) t.erase(t.begin());
        while(t.size() > b[i].y) t.erase(-- t.end()), ans --;
    }

    cout << ans << endl;

    return 0;
}

// ねぇ、私、今、あなたの…