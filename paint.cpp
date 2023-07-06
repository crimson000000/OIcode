#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e5 + 10;
PII a[N], b[N];
int n, m, q;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();

    while(T -- )
    {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        n = read(), m = read(), q = read();
        for(int i = 1; i <= q; i ++ )
        {
            int op = read(), x = read(), c = read();
            if(op == 0)
            {
                a[x] = {c, i};
            }
            else
            {
                b[i] = {c, i};
            }
        }

        for(int i = 1; i <= n; i ++ )
        {
            for(int j = 1; j <= m; j ++ )
            {
                auto row = a[i], col = b[j];
                if(row.second > col.second) printf("%d ", row.first);
                else printf("%d ", col.first);
            }
            puts("");
        }
    }
    
    return 0;
}
