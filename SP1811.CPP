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
char a[N], b[N];
struct suffixautomaton
{
    int link[N], tr[N][26];
    int len[N];
    int idx, last;

    inline void init()
    {
        memset(link, 0, sizeof link);
        memset(tr, 0, sizeof tr);
        memset(len, 0, sizeof len);
        idx = last = 0;
        link[0] = -1;
    }

    inline void extend(char *s)
    {
        int n = strlen(s + 1);
        for(int i = 1; i <= n; i ++ )
        {
            int p = last, cur = ++ idx, c = s[i] - 'a';
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
                    len[copy] = len[p] + 1;
                    link[copy] = link[q];
                    for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
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

    inline int lCS(char *s)
    {
        int l = 0, v = 0;
        int res = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int c = s[i] - 'a';
            while(v && !tr[v][c])
            {
                v = link[v];
                l = len[v];
            }
            if(tr[v][c])
            {
                v = tr[v][c];
                l ++;
            }
            res = max(res, l);
        }
        return res;
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", a + 1, b + 1);
    SAM.init();
    SAM.extend(a);
    cout << SAM.lCS(b) << endl;
    
    return 0;
}
