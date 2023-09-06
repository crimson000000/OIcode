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

const int N = 1e6 + 10, M = 1e5 + 10, S = 55;

char s[N], t[20 * N];
int n;

namespace AC
{
    int tr[M * S][26];
    int fail[M * S];
    int cnt[M * S];
    int idx;

    void insert(char* s)
    {
        int p = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int q = s[i] - 'a';
            if(!tr[p][q]) tr[p][q] = ++ idx;
            p = tr[p][q];
        }
        cnt[p] ++;
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
                int j = tr[t][i];
                if(!j) tr[t][i] = tr[fail[t]][i];
                else
                {
                    fail[j] = tr[fail[t]][i];
                    q.push(j);
                }
            }
        }
    }

    int query(char *s)
    {
        int res = 0;
        for(int i = 1, j = 0; s[i]; i ++ )
        {
            int t = s[i] - 'a';
            j = tr[j][t];

            int p = j;
            while(p && cnt[j] != -1)
            {
                res += cnt[p];
                cnt[p] = -1;
                p = fail[p];
            }
        }
        return res;
    }
}

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
        AC::insert(s);
    }

    AC::build();

    scanf("%s", t + 1);
    
    cout << AC::query(t) << endl;

    return 0;
}
