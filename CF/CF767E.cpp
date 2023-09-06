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
int n, m;
int c[N], w[N];
int nowc;
ll ang;
ll ans[2][N];

struct day
{
    int id;
    bool operator < (const day& a) const
    {
        return w[id] * (100 - c[id]) > w[a.id] * (100 - c[a.id]);
    }
};

priority_queue<day> heap;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    nowc = m;

    for(int i = 1; i <= n; i ++ ) 
    {
        c[i] = read();
        ans[0][i] = c[i] / 100;
        ans[1][i] = c[i] % 100;
        c[i] %= 100;
    }

    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        if(c[i]) heap.push({i});
        if(nowc < c[i])
        {
            int u = heap.top().id;
            heap.pop();
            ang += w[u] * (100 - c[u]);
            nowc += 100;
            nowc -= c[i];
            ans[0][u] ++;
            ans[1][u] = 0;
        }
        else nowc -= c[i];
    }

    cout << ang << endl;

    for(int i = 1; i <= n; i ++ )
        printf("%lld %lld\n", ans[0][i], ans[1][i]);

    return 0;
}