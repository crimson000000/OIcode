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

const int N = 1e6 + 10, SQRTN = 1000;
int B, T;
int a[N];
struct block
{
    int l, r;
}b[N];
int pos[N];
int n, m, c;
int f[SQRTN][SQRTN];
int cnt[100010];
vector<int> app[100010];
int lastans;
bitset<N> st;

queue<int> que;
inline int query(int l, int r)
{
    if(pos[l] == pos[r] || pos[l] == pos[r] - 1)
    {
        ll ans = 0;
        for(register int i = l; i <= r; i ++ ) cnt[a[i]] ++;
        for(register int i = l; i <= r; i ++ )
            if(!(cnt[a[i]] & 1) && !st[a[i]])
                ans ++, st[a[i]] = true;
        for(register int i = l; i <= r; i ++ ) cnt[a[i]] = 0, st[a[i]] = false;;
        return ans;
    }
    else
    {
        int ans = f[pos[l] + 1][pos[r] - 1];
        
        int Lblock = pos[l], Rblock = pos[r];
        int L = b[Lblock + 1].l, R = b[Rblock - 1].r;
        for(register int i = l; i <= b[Lblock].r; i ++ )
            if(!st[a[i]])
            {
                que.push(a[i]);
                st[a[i]] = true;
            }

        for(register int i = b[Rblock].l; i <= r; i ++ )
            if(!st[a[i]])
            {
                que.push(a[i]);
                st[a[i]] = true;
            }

        while(que.size())
        {
            int v = que.front();
            que.pop();

            int cnt_in_block = upper_bound(app[v].begin(), app[v].end(), R) - 
                                lower_bound(app[v].begin(), app[v].end(), L);
            int cnt_all = upper_bound(app[v].begin(), app[v].end(), r) - 
                        lower_bound(app[v].begin(), app[v].end(), l);
            
            // printf("%d : [%d %d]: %d, %d\n", v, L, R, cnt_in_block, cnt_all);

            if(!cnt_in_block) cnt_in_block = 1;
            
            if((cnt_in_block & 1) && (cnt_all & 1)) continue;
            if((cnt_in_block & 1) && !(cnt_all & 1)) ans ++;
            if(!(cnt_in_block & 1) && (cnt_all & 1)) ans --;
            if(!(cnt_in_block & 1) && !(cnt_all & 1)) continue;
        }

        for(register int i = l; i <= b[Lblock].r; i ++ ) st[a[i]] = false;
        for(register int i = b[Rblock].l; i <= r; i ++ ) st[a[i]] = false; 
        
        return ans;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), c = read(), m = read();
    B = pow(n, 0.4), T = n / B;

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        app[a[i]].push_back(i);
    }

    for(register int i = 1; i <= T; i ++ )
    {
        b[i].l = (i - 1) * B + 1;
        b[i].r = i * B;
    }

    if(b[T].r < n) 
    {
        T ++;
        b[T].l = b[T - 1].r + 1, b[T].r = n;
    }

    for(register int i = 1; i <= T; i ++ )
        for(register int j = b[i].l; j <= b[i].r; j ++ )
            pos[j] = i;

    int nowl, nowr;
    for(register int i = 1; i <= T; i ++ )
    {
        nowl = b[i].l, nowr = b[i].l - 1;
        memset(cnt, 0, sizeof cnt);
        for(register int j = i; j <= T; j ++ )
        {
            f[i][j] = f[i][j - 1];
            while(nowr < b[j].r) 
            {
                nowr ++;
                cnt[a[nowr]] ++;
                if((cnt[a[nowr]] & 1) && cnt[a[nowr]] != 1) f[i][j] --;
                if(!(cnt[a[nowr]] & 1)) f[i][j] ++;
            }
        }
    }

    // for(int i = 1; i <= T; i ++ )
    //     for(int j = i; j <= T; j ++ )
    //         printf("[%d %d]: %d\n", b[i].l, b[j].r, f[i][j]);

    memset(cnt, 0, sizeof cnt);

    while(m -- )
    {
        int l = read(), r = read();
        l = (l + lastans) % n + 1, r = (r + lastans) % n + 1;
        if(l > r) swap(l, r);
        // printf("[%d %d]\n", l, r);
        lastans = query(l, r);
        printf("%d\n", lastans);
    }

    return 0;
}