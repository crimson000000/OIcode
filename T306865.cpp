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

const int N = 2e5 + 10;
int T, n, m;
struct Q
{
    int op, x;
}q[N];
bitset<N> st;
bool two = true, four = true;

bool check(int x)
{
    st.reset();
    for(register int i = 1; i <= x; i ++ )
    {
        if(!(q[i].op ^ 1)) st[q[i].x] = true;
        else 
        {
            for(register int j = 1; j <= n; j ++ )
            {
                if(!(j ^ q[i].x)) continue;
                st[j] = true;
            }
            bool flag = true;
            for(register int j = 1; j <= n; j ++ )
                flag &= st[j];
            if(flag) return true;
        }
    }
    bool flag = true;
    for(register int i = 1; i <= n; i ++ ) flag &= st[i];
    return flag;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    T = read();
    while(T -- )
    {
        n = read(), m = read();
        two = true;
        int xx;
        for(register int i = 1; i <= m; i ++ )
        {
            int op = read(), x = read();
            if(!(i ^ 1)) xx = x;
            else 
            {
                if(xx ^ x) four = false;
            }
            q[i] = {op, x};
            if(!(op ^ 1)) two = false;
        } 

        if(two)
        {
            int x = q[1].x;
            bool _ = false;
            for(register int i = 2; i <= m; i ++ )
            {
                if(q[i].x != x) 
                {
                    _ = true;
                    printf("%d\n", i);
                    break;
                }
            }
            if(!_) puts("-1");
        }
        else if(four)
        {
            bool diff = false;
            for(register int i = 2; i <= m; i ++ )
            {
                if(q[i].op ^ q[i - 1].op)
                {
                    diff = true;
                    printf("%d\n", i);
                    break;
                }
            }
            if(!diff) puts("-1");
        }
        else
        {
            int l = 0, r = m + 1;
            while(l < r)
            {
                int mid = l + r >> 1;
                if(!(mid ^ (m + 1)))
                {
                    l = m + 1;
                    break;
                }
                if(check(mid)) r = mid;
                else l = mid + 1;
            }
            if(!(l ^ (m + 1))) puts("-1");
            else printf("%d\n", l);
        }
    }

    return 0;
}