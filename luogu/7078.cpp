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
struct snake
{
    int a, id;
    bool operator < (const snake& A) const
    {
        if(a != A.a) return a < A.a;
        return id < A.id;
    }

    bool operator > (const snake& A) const
    {
        return A < *this;
    }
};
int n;
int a[N];
deque<snake> q1, q2;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int _ = read();
    for(int cas = 1; cas <= _; cas ++ )
    {
        q1.clear();
        q2.clear();

        if(cas == 1)
        {
            n = read();
            for(int i = 1; i <= n; i ++ ) a[i] = read();
        }
        else
        {
            int k = read();
            while(k -- )
            {
                int x = read(), y = read();
                a[x] = y;
            }
        }

        for(int i = 1; i <= n; i ++ ) 
            q1.push_back({a[i], i});

        int ans;
        while(1)
        {
            if(q1.size() + q2.size() == 2)
            {
                ans = 1;
                break;
            }
            int x, y, id;
            y = q1.front().a, q1.pop_front();
            if(q2.empty() || (!q1.empty() && q1.back() > q2.back()))
                x = q1.back().a, id = q1.back().id, q1.pop_back();
            else x = q2.back().a, id = q2.back().id, q2.pop_back();
            snake now = {x - y, id};
            if(q1.empty() || now < q1.front())
            {
                ans = q1.size() + q2.size() + 2;
                int cnt = 0;
                while(1)
                {
                    cnt ++;
                    if(q1.size() + q2.size() + 1 == 2)
                    {
                        if(cnt % 2 == 0) ans --;
                        break;
                    }
                    int x, id;
                    if(q2.empty() || (!q1.empty() && q1.back() > q2.back()))
                        x = q1.back().a, id = q1.back().id, q1.pop_back();
                    else x = q2.back().a, id = q2.back().id, q2.pop_back();
                    now = {x - now.a, id};
                    if((q1.empty() || now < q1.front()) && (q2.empty() || now < q2.front()));
                    else 
                    {
                        if(cnt % 2 == 0) ans --;
                        break;
                    }
                }
                break;
            }
            else
            {
                q2.push_front(now);
            }
        }

        cout << ans << endl;
    }

    return 0;
}