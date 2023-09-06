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
int a[N];
int n;
deque<int> L, R;
char ans[N], cur[N];

inline int find(int l, int r, int v)
{
    for(int i = l; i <= r; i ++ )
        if(a[i] == v) return i;
    return -1;
}

inline void check()
{
    int now = 2;
    while(1)
    {
        if(L.empty() && R.empty()) break;
        else if(L.size() && R.empty())
        {
            if(L.front() != L.back())
            {
                cur[1] = 'Z';
                break;
            }
            cur[now] = cur[2 * n - now + 1] = 'L';
            L.pop_front();
            L.pop_back();
        }
        else if(L.empty() && R.size())
        {
            if(R.front() != R.back())
            {
                cur[1] = 'Z';
                break;
            }
            cur[now] = cur[2 * n - now + 1] = 'R';
            R.pop_front();
            R.pop_back();
        }
        else
        {
            if(L.front() == L.back() && L.size() > 1)
            {
                cur[now] = cur[2 * n - now + 1] = 'L';
                L.pop_front();
                L.pop_back();
            }
            else if(L.front() == R.front())
            {
                // cout << "fauc" << endl;
                cur[now] = 'L';
                cur[2 * n - now + 1] = 'R';
                L.pop_front();
                R.pop_front();
            }
            else if(L.back() == R.back())
            {
                cur[now] = 'R';
                cur[2 * n - now + 1] = 'L';
                L.pop_back();
                R.pop_back();
            }
            else if(R.back() == R.front() && R.size() > 1)
            {
                cur[now] = cur[2 * n - now + 1] = 'R';
                R.pop_back();
                R.pop_front();
            }
            else 
            {
                cur[1] = 'Z';
                return;
            }
        }
        now ++;
    }
}

inline bool cmp()
{
    int id = 1;
    while(id <= 2 * n && ans[id] == cur[id]) id ++;
    return id <= 2 * n && cur[id] < ans[id];
}

inline void solve()
{
    L.clear();
    R.clear();
    ans[1] = 'Y';
    
    n = read();
    for(int i = 1; i <= 2 * n; i ++ ) 
        a[i] = read();

    int pos = find(2, 2 * n, a[1]);
    for(int i = 2; i < pos; i ++ ) 
    {
        L.push_back(a[i]);
        // cout << a[i] << ' ';
    }
    for(int i = pos + 1; i <= 2 * n; i ++ ) 
    {
        R.push_back(a[i]);
        // cout << a[i] << ' ';
    }

    cur[1] = cur[2 * n] = 'L';
    check();

    if(cmp())
    {
        for(int i = 1; i <= 2 * n; i ++ ) ans[i] = cur[i];
    }

    L.clear(), R.clear();
    pos = find(1, 2 * n - 1, a[n * 2]);
    cur[1] = 'R', cur[2 * n] = 'L';
    for(int i = 1; i < pos; i ++ ) L.push_back(a[i]);
    for(int i = pos + 1; i < 2 * n; i ++ ) R.push_back(a[i]);
    check();

    if(cmp())
    {
        for(int i = 1; i <= 2 * n; i ++ ) ans[i] = cur[i];
    }

    if(ans[1] == 'Y') puts("-1");
    else
    {
        for(int i = 1; i <= 2 * n; i ++ ) putchar(ans[i]);
        puts("");
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}