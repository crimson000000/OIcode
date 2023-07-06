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

namespace AC
{
    const int N = 1e6 + 10;
    int tr[N][26];
    int fail[N], id[N], cnt[N];
    int val[N];
    int idx;

    void init()
    {
        memset(tr, 0, sizeof tr);
        memset(fail, 0, sizeof fail);
        memset(id, 0, sizeof id);
        memset(val, 0, sizeof val);
        memset(cnt, 0, sizeof cnt);
        idx = 0;
    }

    inline void insert(char *s, int ident)
    {
        int p = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int t = s[i] - 'a';
            if(!tr[p][t]) tr[p][t] = ++ idx;
            p = tr[p][t];
        }
        id[p] = ident;
    }

    inline void build()
    {
        queue<int> q;
        for(int i = 0; i < 26; i ++ )
            if(tr[0][i])
                q.push(tr[0][i]);
        
        while(q.size())
        {
            int t = q.front();
            q.pop();

            for(int i = 0; i < 26; i ++ )
            {
                int p = tr[t][i];
                if(!p) tr[t][i] = tr[fail[t]][i];
                else
                {
                    fail[p] = tr[fail[t]][i];
                    q.push(p);
                }
            }
        }
    }

    int query(char *s)
    {
        int j = 0, res = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int t = s[i] - 'a';
            j = tr[j][t];

            int p = j;
            while(p)
            {
                val[p] ++ ;
                p = fail[p];
            }
        }

        for(int i = 0; i <= idx; i ++ ) 
            if(id[i])
                cnt[id[i]] = val[i], res = max(res, val[i]);
        
        return res;
    }
}

const int N = 1100, M = 1e6 + 10;
char s[N][N];
char t[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(scanf("%d", &n), n)
    {
        AC::init();
        for(int i = 1; i <= n; i ++ )
        {
            scanf("%s", s[i] + 1);
            AC::insert(s[i], i);
        }

        AC::build();

        scanf("%s", t + 1);

        int maxn = AC::query(t);

        cout << maxn << endl;

        for(int i = 1; i <= n; i ++ )
            if(AC::cnt[i] == maxn)
            {
                printf("%s\n", s[i] + 1);
            }
    }
    
    return 0;
}
