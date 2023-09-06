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
int h[N], e[N], ne[N], w[N], idx;
int n, m;
bool flag;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++; 
}

struct node
{
    int top, cnt;
};

node dfs(int u, int fa, int mid)
{
    multiset<int> s;
    int cnt = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        auto son = dfs(v, u, mid);
        if(w[i] + son.top >= mid)
        {
            cnt ++;
        }
        else s.insert(w[i] + son.top);
        cnt += son.cnt;
    }

    int top = 0;
    while(s.size())
    {
        auto it = s.upper_bound(0);
        int p = *it;
        s.erase(it);
        
        it = s.lower_bound(mid - p);
        if(it == s.end()) top = max(top, p);
        else 
        {
            s.erase(it);
            cnt ++;
        }
    }
    if(cnt >= m) flag = true;
    return {top, cnt};
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    int l = 0, r = 1e9;
    while(l < r)
    {
        int mid = l + r >> 1;
        flag = false;
        dfs(1, 1, mid);
        if(flag) l = mid + 1;
        else r = mid;
    }

    cout << l - 1 << endl;

    return 0;
}