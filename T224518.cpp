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

inline ll read1()
{
    ll x = 0, f = 1;
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

vector<bool> len;

void print(vector<bool> a)
{
    for(int i = a.size() - 1; i >= 0; i -- ) cout << a[i];
    puts("");
}

void add(vector<bool> &a, ll B)
{
    vector<bool> b;
    while(B) b.push_back(B & 1), B >>= 1;
    // print(b);
    int t = 0;
    for(int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if(i < a.size()) t += a[i];
        if(i < b.size()) t += b[i];

        if(i < a.size()) a[i] = t & 1;
        else a.push_back(t & 1);
        t >>= 1;
    }

    if(t) a.push_back(1);
    return;
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
        len.clear();
        len.push_back(0);
        int n = read();
        while(n -- )
        {
            int op;
            op = read();
            if(op == 1)
            {
                len.insert(len.begin(), 0);
            }
            else
            {
                ll d = read1();
                add(len, d);
            }
            // cout << "len:";
            // print(len);
        }

        while(len.back() == 0 && len.size() > 1) len.pop_back();

        for(int i = len.size() - 1; i >= 0; i -- ) cout << len[i];
        puts("");
    }
    
    return 0;
}
