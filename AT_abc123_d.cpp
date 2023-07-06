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
ll a[N], b[N], c[N];
int x, y, z, K;
struct node
{
    int i, j, k;
    bool operator < (const node& t) const
    {
        return a[i] + b[j] + c[k] < a[t.i] + b[t.j] + c[t.k];
    }
};
map<pair<pair<int, int>, int>, bool> mp;
priority_queue<node> heap;

inline ll sum(node t)
{
    return a[t.i] + b[t.j] + c[t.k];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    x = read(), y = read(), z = read(), K = read();
    for(int i = 1; i <= x; i ++ ) a[i] = read();
    for(int i = 1; i <= y; i ++ ) b[i] = read();
    for(int i = 1; i <= z; i ++ ) c[i] = read();
    
    sort(a + 1, a + 1 + x);
    reverse(a + 1, a + 1 + x);
    sort(b + 1, b + 1 + y);
    reverse(b + 1, b + 1 + y);
    sort(c + 1, c + 1 + z);
    reverse(c + 1, c + 1 + z);

    heap.push({1, 1, 1});
    while(K -- )
    {
        auto t = heap.top();
        heap.pop();
        cout << sum(t) << endl;
        int i = t.i, j = t.j, k = t.k;
        if(!mp.count({{i + 1, j}, k}) && i + 1 <= x) heap.push({i + 1, j, k}), mp[{{i + 1, j}, k}] = true;
        if(!mp.count({{i, j + 1}, k}) && j + 1 <= y) heap.push({i, j + 1, k}), mp[{{i, j + 1}, k}] = true;
        if(!mp.count({{i, j}, k + 1}) && k + 1 <= z) heap.push({i, j, k + 1}), mp[{{i, j}, k + 1}] = true;
    }

    return 0;
}
