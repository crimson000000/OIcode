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
    int fail[N];
    int id[N];
    int mp[N];
    int val[N], ans[N];
    int din[N];
    int idx;

    void insert(char *s, int ident)
    {
        int p = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int t = s[i] - 'a';
            if(!tr[p][t]) tr[p][t] = ++ idx;
            p = tr[p][t];
        }
        if(!id[p]) id[p] = ident;
        mp[ident] = id[p];
    }

    void build()
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
                    din[fail[p]] ++;
                }
            }
        }
    }

    void query(char *s)
    {
        for(int i = 1, j = 0; s[i]; i ++ )
        {
            int t = s[i] - 'a';
            if(t >= 26 || t < 0) 
            {
                j = 0;
                continue;
            }
            j = tr[j][t];
            val[j] ++;
        }
    }

    void topsort()
    {
        queue<int> q;

        for(int i = 1; i <= idx; i ++ )
            if(!din[i])
                q.push(i);
        
        while(q.size())
        {
            int t = q.front();
            q.pop();

            ans[id[t]] = val[t];
            int v = fail[t];
            din[v] --;
            val[v] += val[t];
            if(!din[v]) q.push(v);
        }
    }
}

const int N = 1e6 + 10;
int n;
char s[N], t[N * 2];
int cnt;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", s + 1);
        AC::insert(s, i);

        int len = strlen(s + 1);
        for(int i = 1; i <= len; i ++ ) t[++ cnt] = s[i];
        t[++ cnt] = '#';
    }

    AC::build();
    AC::query(t);
    AC::topsort();

    using namespace AC;
    for(int i = 1; i <= n; i ++ ) std::cout << ans[mp[i]] << endl;
    
    return 0;
}
