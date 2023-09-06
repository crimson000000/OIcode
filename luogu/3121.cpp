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
char s[N], T[N];
int t[N][26];
int fail[N], dep[N];
int stk[N], tt;
int match[N];
int n;
int idx;

inline void insert(char *s)
{
    int p = 0, len = strlen(s);
    for(int i = 0; s[i]; i ++ )
    {
        int u = s[i] - 'a';
        if(!t[p][u]) t[p][u] = ++ idx;
        p = t[p][u];
    } 
    dep[p] = len;
}

queue<int> q;
void build()
{
    for(int i = 0; i < 26; i ++ )
        if(t[0][i])
            q.push(t[0][i]);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < 26; i ++ )
        {
            int p = t[u][i];
            if(!p) t[u][i] = t[fail[u]][i];
            else
            {
                fail[p] = t[fail[u]][i];
                q.push(p);
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", T);
    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", s);
        insert(s);
    }

    build();

    int p = 0, len = strlen(T);

    for(int i = 0; i < len; i ++ )
    {
        int u = T[i] - 'a';
        p = match[i] = t[p][u];
        stk[++ tt] = i;
        if(dep[p])
        {
            tt -= dep[p];
            p = match[stk[tt]];
        }
    }

    for(int i = 1; i <= tt; i ++ ) cout << T[stk[i]];
    puts("");

    return 0;
}
