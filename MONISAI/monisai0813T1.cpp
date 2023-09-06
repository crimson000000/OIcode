#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using PII = pair<int, int>;

namespace IO
{
    const int sz = 1 << 22;
    char a[sz + 5], b[sz + 5], *p1 = a, *p2 = a, *t = b, p[105];
    inline char gc()
    {
        return p1 == p2 ? (p2 = (p1 = a) + fread(a, 1, sz, stdin), p1 == p2 ? EOF : *p1++) : *p1++;
    }
    template <class T>
    void read(T &x)
    {
        x = 0;
        char c = gc();
        for (; c < '0' || c > '9'; c = gc())
            ;
        for (; c >= '0' && c <= '9'; c = gc())
            x = x * 10 + (c - '0');
    }
    inline void flush() { fwrite(b, 1, t - b, stdout), t = b; }
    inline void pc(char x)
    {
        *t++ = x;
        if (t - b == sz)
            flush();
    }
    template <class T>
    void write(T x, char c = '\n')
    {
        if (x == 0)
            pc('0');
        int t = 0;
        for (; x; x /= 10)
            p[++t] = x % 10 + '0';
        for (; t; --t)
            pc(p[t]);
        pc(c);
    }
    struct F
    {
        ~F() { flush(); }
    } f;
}
using IO::read;
using IO::write;

const int N = 1e7 + 10;
int n, x, y, z;
int m0, m1;
int c[N];

struct node
{
    int c, id;
}stk[N];
int tt;
int ext[N];

ll sum;
ll ans;

inline void aaaread()
{
    read(n);
    for(int i = 0; i < n; i ++ ) read(c[i]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    read(n), read(x), read(y), read(z);

    read(m0), read(m1);
    read(c[0]), read(c[1]);

    for(int i = 2; i < n; i ++ )
    {
        if(i & 1) c[i] = ((ll)c[i - 1] * x + (ll)c[i - 2] * y + z) % m1 + 1;
        else c[i] = ((ll)c[i - 1] * x + (ll)c[i - 2] * y + z) % m0 + 1;
    }

    // aaaread();

    // for(int i = 0; i < n; i ++ ) cout << c[i] << ' ';
    // puts("");

    for(int i = 0; i < n; i ++ )
    { 
        if(!(i & 1))
        {
            stk[++ tt] = {c[i], i};
        }
        else
        {
            ll now = c[i];
            while(tt > 0 && now >= stk[tt].c) 
            {
                ans += stk[tt].c;
                now -= stk[tt].c;
                int lstid = stk[tt].id;
                tt --;
                if(tt && now) ans += ext[lstid - 1];
                // cout << ans << "++++" << endl;
            }

            // cout << ans << "_---------" << endl;;

            if(tt > 0 && now)
            {
                ans += now;
                stk[tt].c -= now;
                ext[i] = 1;
            }
            else if(tt == 0 && now)
            {
                int lstid = stk[tt + 1].id;
                // cout << lstid << endl;
                ans += ext[lstid - 1];
                ext[i] = 0;
            }
            else if(tt == 0 && !now)
            {
                int lstid = stk[tt + 1].id;
                ans += ext[lstid - 1];
                ext[i] = ext[lstid - 1] + 1;
            }
            else if(tt > 0 && !now)
            {
                // cout << "yeag" << endl;
                int lstid = stk[tt + 1].id;
                ext[i] = ext[lstid - 1] + 1;
                ans += ext[lstid - 1];
            }
        }
        // for(int i = 1; i <= tt; i ++ )
        //     printf("[%d %d], ", stk[i].c, stk[i].id);
        // // puts("");

        // cout << ans << endl;
    }

    // for(int i = 0; i < n; i ++ ) cout << ext[i] << ' ';
    // puts("");

    write(ans);

    return 0;
} 