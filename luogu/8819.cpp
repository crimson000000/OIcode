#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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
ull w[N], sum, nei[N], ns, fix[N], stne[N];
int n, m;
mt19937_64 rnd(chrono::_V2::steady_clock::now().time_since_epoch().count());

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) 
    {
        w[i] = rnd();
        // w[i] = 2 * (i - 1) + 1;
        // cout << w[i] << endl;
    }
    for(int i = 1; i <= n; i ++ ) sum += w[i];

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        ns += w[a];
        nei[b] += w[a];
        stne[b] += w[a];
    }

    // for(int i = 1; i <= n; i ++ ) cout << nei[i] << ' ';
    //     puts("");

    int q = read();
    while(q -- )
    {
        int op = read(), u = read(), v;
        if(op == 1)
        {
            v = read();
            nei[v] -= w[u];
            fix[v] += w[u];
            ns -= w[u];
        }
        else if(op == 2)
        {
            ns -= nei[u];
            fix[u] += nei[u];
            nei[u] = 0;
        }
        else if(op == 3)
        {
            v = read();
            nei[v] += w[u];
            fix[v] -= w[u];
            ns += w[u];
        }
        else
        {
            ns += fix[u];
            nei[u] = stne[u];
            fix[u] = 0;
        }
        // for(int i = 1; i <= n; i ++ ) cout << nei[i] << ' ';
        // puts("");
        if(ns == sum) puts("YES");
        else puts("NO");
    }

    return 0;
}

/*
只要动态统计每个点的出度就行了，每个点出度为 1 就行
怎么统计出度啊
加删一条边好说，现在就是点的问题了。
删一个点会让它的反向图中的邻居的出度都减少 1
必然不能数据结构维护吧
建反向图的话菊花图就能卡爆掉

看到标签是哈希
是不是可以每个点赋权值
记一个 sum 是所有点权值和
每个点的贡献为 出度*权值
先建反向图统计每个点邻居的值和
删掉这个点就可以直接减
这里复杂度应该是 O(m)
应该可过
开写吧

start at 14:56
*/