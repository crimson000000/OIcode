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

const int N = 2e6 + 10, M = 1010;
deque<int> stk[M];
int a[N];
int id[M * 2], sp;
queue<int> q;
vector<PII> ans;
int n, m, k;

inline void init(int n)
{
    for(int i = 1; i <= n; i ++ ) stk[i].clear();
    ans.clear();
    while(q.size()) q.pop();
    for(int i = 1; i <= k; i ++ ) id[i] = 0;

    sp = n;
    for(int i = 1; i < n; i ++ )
    {
        q.push(i);
        q.push(i);
    }
}

inline void push(int x)
{
    ans.emplace_back(x, 0);
}

inline void del(int x, int y)
{
    ans.emplace_back(x, y);
}

inline bool act(int x)
{
    int s = id[x];
    if(!s)
    {
        if(q.empty()) return false;
        id[x] = s = q.front();
        q.pop();
        push(s);
        stk[s].push_back(x);
    }
    else
    {
        id[x] = 0;
        q.push(s);
        if(x == stk[s].back())
        {
            push(s);
            stk[s].pop_back();
        }
        else
        {
            push(sp);
            del(sp, s);
            stk[s].pop_front();
        }
    }
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read(), m = read(), k = read();
        init(n);

        for(int i = 1; i <= m; i ++ ) a[i] = read();

        for(int i = 1; i <= m; i ++ )
        {
            if(!act(a[i]))
            {
                int p = a[i];
                int r = i + 1, x = a[r];
                while(r <= m && x != p && x == stk[id[x]].back())
                {
                    ++ r, x = a[r];
                }

                if(x == p)
                {
                    push(sp);
                    for(int j = i + 1; j < r; j ++ )
                        act(a[j]);
                    push(sp);
                }
                else
                {
                    int s = id[x], y = stk[s].back();
                    bool even = true;
                    for(int j = i + 1; j < r; j ++ )
                        if(a[j] == y)
                            even ^= 1;
                    
                    if(even)
                    {
                        push(s);
                        stk[s].push_back(p);
                        for(int j = i + 1; j < r; j ++ )
                            if(a[j] == y)
                                push(sp);
                            else act(a[j]);
                        
                        push(sp);
                        del(s, sp);
                        stk[s].pop_front();

                        id[x] = 0;
                        id[p] = s;
                    }
                    else
                    {
                        push(sp);
                        stk[sp].push_back(p);
                        for(int j = i + 1; j < r; j ++ )
                            if(a[j] == y)
                                push(s);
                            else act(a[j]);
                        push(s);
                        stk[s].clear();

                        id[x] = 0, id[y] = 0;
                        id[p] = sp;
                        q.push(sp);
                        sp = s;
                    }
                }

                i = r;
            }
        }

        printf("%d\n", ans.size());
        for(auto u : ans)
        {
            if(u.second == 0) printf("1 %d\n", u.first);
            else printf("2 %d %d\n", u.first, u.second);
        }
    }

    return 0;
}