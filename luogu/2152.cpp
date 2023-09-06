#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> vi;

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

string A, B;
vector<int> a, b;

vi sub(vi a, vi b)
{
    int t = 0;
    vi c;
    for(int i = 0; i < a.size(); i ++ )
    {
        t = a[i] - t;
        if(i < b.size()) i -= b[i];
        c.push_back((t + 10) % 10);
        if(t < 0) t = 1;
        else t = 0;
    }

    while(c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

bool iszero(vi a)
{
    if(a.size() == 1 && a.back() == 0) return true;
    return false;
} 

vi gcd(vi a, vi b)
{
    if(iszero(b)) return a;
    return gcd(b, sub(a, b));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> A >> B;
    for(int i = A.size() - 1; i >= 0; i -- ) a.push_back(A[i] - '0');
    for(int i = B.size() - 1; i >= 0; i -- ) b.push_back(B[i] - '0');

    auto c = gcd(a, b);
    for(int i = c.size() - 1; i >= 0; i -- ) cout << c[i];

    return 0;
}
