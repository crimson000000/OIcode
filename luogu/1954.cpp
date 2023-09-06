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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
int K[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct cmp
{
    bool operator () (const int a, const int b)
    {
        return K[a] < K[b];
    }
};

int din[N], din_copy[N];
vector<int> ans;
priority_queue<int, vector<int>, cmp> heap;

inline void topsort()
{
    for(int i = 1; i <= n; i ++ )
        if(!din[i]) 
            heap.emplace(i);
    while(heap.size())
    {
        int u = heap.top();
        ans.emplace_back(u);
        heap.pop();

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            din[v] --;
            if(!din[v]) heap.emplace(v);
        }
    }
}

inline int get(int cant)
{
    // for(int i = h[cant]; i != -1; i = ne[i])
    //     din[e[i]] --;

    while(heap.size()) heap.pop();

    for(int i = 1; i <= n; i ++ )
        if(!din[i] && i != cant)
            heap.emplace(i);

    for(int t = n; t; t -- )
    {
        if(heap.empty()) return t;
        int u = heap.top();
        if(K[u] < t) 
        {
            return t;
        }
        heap.pop();

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            din[v] --;
            if(!din[v] && v != cant) 
                heap.emplace(v);
        }
    }
    return 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) K[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(b, a);
        din[a] ++;
    }

    for(int i = 1; i <= n; i ++ ) din_copy[i] = din[i];

    topsort();

    for(int i = ans.size() - 1; i >= 0; i -- )
        printf("%d ", ans[i]);
    puts("");

    for(int u = 1; u <= n; u ++ )
    {
        for(int i = 1; i <= n; i ++ ) din[i] = din_copy[i];
        printf("%d ", get(u));
    }

    return 0;
}