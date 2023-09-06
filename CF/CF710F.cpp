#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
int m;
struct ACAM
{
    int tr[N][26], cnt[N];
    int fail[N], idx;
    string data[N];
    int siz[N], fr[N];
    int stk[N], tt;
    int n;

    void insert(int r, char *s)
    {
        int p = r;
        int len = strlen(s + 1);
        for(int i = 1; i <= len; i ++ )
        {
            int c = s[i] - 'a';
            if(tr[p][c] == r) 
            {
                tr[p][c] = ++ idx;
                for(int j = 0; j < 26; j ++ ) tr[idx][j] = r;
            }
            p = tr[p][c];
        }
        cnt[p] ++;
    }

    void build(int p)
    {
        queue<int> q;
        fail[p] = p;
        for(int i = 0; i < 26; i ++ )
            if(tr[p][i] > p)
                q.push(tr[p][i]), fail[tr[p][i]] = p;
        
        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i ++ )
            {
                int v = tr[u][i];
                if(v == p) tr[u][i] = tr[fail[u]][i];
                else
                {
                    fail[v] = tr[fail[u]][i];
                    cnt[v] += cnt[fail[v]];
                    q.push(v);
                }
            }
        }
    }

    int query(int r, char *s)
    {
        int res = 0;
        int p = r;
        int len = strlen(s + 1);
        for(int i = 1; i <= len; i ++ )
        {
            int c = s[i] - 'a';
            p = tr[p][c];
            res += cnt[p];
        }
        return res;
    }

    void merge()
    {
        tt --;
        siz[tt] <<= 1;
        for(int i = stk[tt]; i <= idx; i ++ )
        {
            cnt[i] = fail[i] = 0;
            for(int j = 0; j < 26; j ++ ) tr[i][j] = 0;
        }
        idx = stk[tt];
        for(int i = 0; i < 26; i ++ ) tr[stk[tt]][i] = stk[tt];
        for(int i = fr[tt]; i <= n; i ++ ) insert(stk[tt], &data[i][0]);
        build(stk[tt]);
    }

    void Insert(char *s)
    {
        int len = strlen(s + 1);
        stk[++ tt] = ++ idx;
        for(int i = 0; i < 26; i ++ ) tr[idx][i] = idx;
        siz[tt] = 1;
        insert(idx, s);
        build(stk[tt]);
        fr[tt] = ++ n;
        data[n] = " ";
        for(int i = 1; i <= len; i ++ ) data[n] += s[i];
        while(siz[tt] == siz[tt - 1]) merge();
    }

    int Count(char *s)
    {
        int ans = 0;
        // cout << tt << endl;
        for(int i = 1; i <= tt; i ++ )
        {
            int p = stk[i];
            ans += query(p, s);
        }
        return ans;
    }
}Add, Del;
char tmp[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read();
    while(m -- )
    {
        int op = read();
        scanf("%s", tmp + 1);
        if(op == 1) Add.Insert(tmp);
        else if(op == 2) Del.Insert(tmp);
        else printf("%d\n", Add.Count(tmp) - Del.Count(tmp));
        fflush(stdout);
    }

    return 0;
}