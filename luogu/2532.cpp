#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;

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

VI add(VI a, VI b)
{
    VI c;
    int t = 0;
    for(int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if(i < a.size()) t += a[i];
        if(i < b.size()) t += b[i];

        c.push_back(t % 10);
        t /= 10;
    }
    if(t) c.push_back(1);
    return c;
}

vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i ++ )
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;

    int t = 0;
    for (int i = 0; i < A.size() || t; i ++ )
    {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

VI div(VI a, int b)
{
    int r = 0;
    VI c;
    for(int i = a.size() - 1; i >= 0; i -- )
    {
        r = r * 10 + a[i];
        c.push_back(r / b);
        r %= b;
    }
    reverse(c.begin(), c.end());
    while(c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

void print(VI a)
{
    for(int i = a.size() - 1; i >= 0; i -- ) cout << a[i];
}

const int N = 1000;

int n;
VI f[N][N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;
    
    VI a;
    a.push_back(1);
    for(int i = n + 2; i <= 2 * n; i ++ ) a = mul(a, i);
    for(int i = 1; i <= n; i ++ ) a = div(a, i);

    print(a);

    return 0;
}
