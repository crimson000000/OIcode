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
int n, m, q, U, V, t;
double p;
int a[N];
struct Monotonic_queue
{
    queue<int> q1, q2, q3;
    int delta;

    inline void init()
    {
        for(int i = n; i; i -- ) q1.push(a[i]);
    }

    inline void update()
    {
        delta += q;
    }

    inline int size()
    {
        return q1.size() + q2.size() + q3.size();
    }

    inline void push(int val, int op)
    {
        val -= delta + q;
        if(op == 2) q2.push(val);
        if(op == 3) q3.push(val);
    }

    inline int top()
    {
        int res = -0x3f3f3f3f;
        if(!q1.empty()) res = max(res, q1.front());
        if(!q2.empty()) res = max(res, q2.front());
        if(!q3.empty()) res = max(res, q3.front());
        return res + delta;
    }

    inline void pop()
    {
        int id = 0, val = -0x3f3f3f3f;
        if(!q1.empty() && q1.front() > val) id = 1, val = q1.front();
        if(!q2.empty() && q2.front() > val) id = 2, val = q2.front();
        if(!q3.empty() && q3.front() > val) id = 3, val = q3.front();
        if(id == 1) q1.pop();
        if(id == 2) q2.pop();
        if(id == 3) q3.pop();
    }
}h;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read(), U = read(), V = read(), t = read();
    p = (double)U / V;
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    sort(a + 1, a + n + 1);
    h.init();

    int cnt = 0;
    for(int i = 1; i <= m; i ++ )
    {
        int u = h.top();
        h.pop();

        if(i % t == 0) printf("%d ", u);
        // cout << h.size() << endl;

        int u2 = p * u, u3 = u - u2;
        h.push(u2, 2), h.push(u3, 3);
        h.update();
        
        cnt ++;
    }

    puts("");

    cnt = 0;
    while(h.size())
    {
        cnt ++;
        int u = h.top();
        h.pop();
        if(cnt % t == 0) printf("%d ", u);
    }

    return 0;
}