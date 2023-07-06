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

const int N = 510;
struct node
{
    bitset<N> S;
    vector<int> V;
    int pos, val;
    bool operator < (const node& a) const
    {
        return val < a.val;
    }
} O;

int n, k, c, a[N][10];
priority_queue<node> heap;
inline void fix(node x)
{
    int tmp[10];
    memset(tmp, 0, sizeof tmp);
    x.pos = x.V.size();
    for(int i = 1; i <= x.pos; i ++ )
        for(int j = 1; j <= k; j ++ )
            tmp[j] = max(tmp[j], a[x.V[i - 1]][j]);
    for(int i = x.pos + 1; i <= k; i ++ )
    {
        int id = -1;
        for(int j = 1; j <= n; j ++ )
            if(x.S[j] && (id == -1 || a[id][i] <= a[j][i]))
                id = j;
        if(id == -1) return;
        for(int j = 1; j <= k; j ++ ) tmp[j] = max(tmp[j], a[id][j]);
        x.V.push_back(id);
        x.S[id] = false;
    }
    x.val = 0;
    for(int i = 1; i <= k; i ++ )
        x.val += tmp[i];
    heap.push(x);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), c = read();
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= k; j ++ )
            a[i][j] = read();
    
    O.S.set();
    fix(O);

    while(c -- )
    {
        auto x = heap.top();
        heap.pop();
        
        if(!c)
        {
            cout << x.val << endl;
            return 0;
        }

        for(int i = x.pos; i < k; i ++ )
        {
            node y = x;
            y.V.resize(i);
            y.S[x.V[i]] = false;
            for(int j = i + 1; j < k; j ++ ) y.S[x.V[j]] = true;
            fix(y);
        }
    }

    return 0;
}