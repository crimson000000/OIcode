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
multiset<string> s;
int cnt;
int a, b, c;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    a = read(), b = read(), c = read();

    while(a -- ) s.insert("a");
    while(b -- ) s.insert("b");
    while(c -- ) s.insert("c");

    while(s.size() > 1)
    {
        auto ita = s.begin(), itb = (-- s.end());
        s.insert((*ita) + (*itb)), s.erase(ita), s.erase(itb);
    }

    cout << *s.begin() << endl;

    return 0;
}
