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

const int N = 5e5 + 10;
ll ans[N];
int n, a[N];
struct suffixautomaton
{
    int link[N];
    map<int, int> tr[N];
    int len[N];
    int last, idx;
    vector<int> G[N];

    inline void init()
    {
        memset(link, 0, sizeof link);
        memset(len, 0, sizeof len);
        last = idx = 0;
        len[0] = 0;
        link[0] = -1;
    } 

    inline void extend(int c, int i)
    {
        int p = last, cur = ++ idx;
        len[cur] = len[p] + 1;
        while(p != -1 && !tr[p].count(c))
        {
            tr[p][c] = cur;
            p = link[p];
        }
        if(p == -1) link[cur] = 0;
        else
        {
            int q = tr[p][c];
            if(len[q] == len[p] + 1) link[cur] = q;
            else
            {
                int copy = ++ idx;
                len[copy] = len[p] + 1;
                link[copy] = link[q];
                tr[copy] = tr[q];
                while(p != -1 && tr[p].count(c) && tr[p][c] == q)
                {
                    tr[p][c] = copy;
                    p = link[p];
                }
                link[q] = link[cur] = copy;
            }
        }
        last = cur;
        ans[i] = ans[i - 1] + len[cur] - len[link[cur]];
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    SAM.init();
    for(int i = 1; i <= n; i ++ )
    {
        SAM.extend(a[i], i);
        printf("%lld\n", ans[i]);
    }

    return 0;
}
