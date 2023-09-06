#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
using ull = unsigned long long;

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

const int N = 2e7 + 10, M = 1e6 + 10;
int n, m;
char s[N];
char t[N];

inline char transform(char a)
{
    if(a == 'E') return 'a';
    if(a == 'S') return 'b';
    if(a == 'W') return 'c';
    return 'd';
}

inline void trans(char *s)
{
    for(int i = 1; s[i]; i ++ )
        s[i] = transform(s[i]);
}

struct suffixautomaton
{
    int link[N], tr[N][4];
    int len[N];
    int idx, last;

    inline void init()
    {
        link[0] = -1;
        idx = last = 0;
    }

    inline void build(char *s)
    {
        for(int i = 1; s[i]; i ++ )
        {
            int cur = ++ idx, p = last, c = s[i] - 'a';
            len[cur] = len[p] + 1;
            while(p != -1 && !tr[p][c])
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
                    link[copy] = link[q];
                    len[copy] = len[p] + 1;
                    for(int i = 0; i < 4; i ++ ) tr[copy][i] = tr[q][i];
                    while(p != -1 && tr[p][c] == q)
                    {
                        tr[p][c] = copy;
                        p = link[p];
                    }
                    link[q] = link[cur] = copy;
                }
            }
            last = cur;
        }
    }

    inline void dfs(char *t)
    {
        int p = 0;
        int len = 1;
        for(; t[len]; len ++ )
        {
            int c = t[len] - 'a';
            if(tr[p][c]) p = tr[p][c];
            else break;
        }
        printf("%d\n", len - 1);
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    scanf("%s", s + 1);

    trans(s);

    SAM.init();
    SAM.build(s);

    while(m -- )
    {
        scanf("%s", t + 1);
        trans(t);
        SAM.dfs(t);
    }

    return 0;
}