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
int n, t;
struct job
{
    int t, b;
    bool operator < (const job& a) const
    {
        return t > a.t;
    }
};

struct jobb
{
    int t, b;
    bool operator < (const jobb& a) const
    {
        return t + b < a.t + a.b;
    }
};
priority_queue<job> heap;
priority_queue<jobb> heap2;

inline bool cmp(job a, job b)
{
    return a.t + a.b < b.t + b.b;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int _ = read();
    while(_ -- )
    {
        while(heap.size()) heap.pop();
        while(heap2.size()) heap2.pop();

        n = read(), t = read();
        for(int i = 1; i <= n; i ++ )
        {
            int a = read(), b = read();
            if(b >= 0) heap.push({a, b});
            else heap2.push({a, b});
        }

        bool flag = false;
        while(heap.size())
        {
            int ti = heap.top().t;
            int bi = heap.top().b;
            heap.pop();

            if(t <= ti)
            {
                flag = true;
                break;
            }

            t += bi;
        }

        if(!flag)
        {
            while(heap2.size())
            {
                int ti = heap2.top().t;
                int bi = heap2.top().b;
                heap2.pop();

                if(t <= ti)
                {
                    flag = true;
                    break;
                }

                t += bi;

                if(t <= 0)
                {
                    flag = true;
                    break;
                }
            }
        }

        if(flag) puts("-1s");
        else puts("+1s");
    }

    return 0;
}