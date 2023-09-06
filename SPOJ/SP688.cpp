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

const int N = 1e6 + 10;
int a[N], nxt[N], lst[N];
int cnt;
bitset<N> vis;
int n, k, p;

struct aww
{
    int x;
    bool operator < (const aww& a) const
    {
        return nxt[x] < nxt[a.x];
    }
};
priority_queue<aww> heap;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        while(heap.size()) heap.pop();
        vis.reset();
        cnt = 0;

        int n = read(), k = read(), p = read();
        for(int i = 1; i <= p; i ++ ) 
        {
            a[i] = read();
            lst[a[i]] = p + 1;
        }

        for(int i = p; i; i -- )
        {
            nxt[i] = lst[a[i]];
            lst[a[i]] = i;
        }

        for(int i = 1; i <= p; i ++ )
        {
            if(!vis[a[i]])
            {
                if(heap.size() == k)
                {
                    vis[a[heap.top().x]] = false;
                    heap.pop();
                }
                heap.push({i});
                vis[a[i]] = true;
                cnt ++;
            }
            else
            {
                k ++;
                heap.push({i});
            }
        }

        cout << cnt << endl;
    }

    return 0;
}