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
    const int N = 2e6 + 10, M = 2e5 + 10;
    int tr[N][26];
    int fail[N];
    int id[N];
    int din[N];
    int mp[N];
    int val[N];
    int ans[N];
    int idx;

    inline void insert(char *s, int ident)
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
                int u = tr[t][i];
                if(!u) tr[t][i] = tr[fail[t]][i];
                else 
                {
                    fail[u] = tr[fail[t]][i];
                    din[fail[u]] ++;
                    q.push(u);
                }   
            }
        }
    }

    void query(char *s)
    {
        for(int i = 1, j = 0; s[i]; i ++ )
        {
            int t = s[i] - 'a';
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
            if(din[v] == 0) q.push(v);
        }
    }
}

const int N = 2e6 + 10, M = 2e5 + 10;
char t[N];
char s[M];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", s + 1);
        AC::insert(s, i);
    }

    AC::build();

    scanf("%s", t + 1);
    AC::query(t);

    AC::topsort();

    for(int i = 1; i <= n; i ++ ) cout << AC::ans[AC::mp[i]] << endl;
    
    return 0;
}
