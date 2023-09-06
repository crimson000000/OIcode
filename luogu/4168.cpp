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

const int N = 4e4 + 10, M = 45;
int n, m, lastans, t, block;
int a[N];
int cnt[M][M][N], L[N], R[N], pos[N];
int mode[M][M];
vector<int> nums;
int tot;

int get(int n)
{
    return nums[n];
}

void discretize()
{
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ ) 
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();

    // for(int i = 1; i <= n; i ++ ) cout << a[i] << ' ';
    // puts("");
    // for(int i = 1; i <= n; i ++ ) cout << get(a[i]) << ' ';
}

inline void init()
{
    block = pow(n, 1.0 / 3);
    t = n / block;
    // block = 6, t = 1;
    for(int i = 1; i <= block; i ++ )
    {
        L[i] = (i - 1) * t + 1;
        R[i] = i * t;
    }
    if(R[block] < n) block ++, L[block] = R[block - 1] + 1, R[block] = n;

    for(int i = 1; i <= block; i ++ )
        for(int j = L[i]; j <= R[i]; j ++ )
            pos[j] = i;

    for(int i = 1; i <= block; i ++ )
        for(int j = 1; j <= block; j ++ )
            mode[i][j] = 40005;

    for(int i = 1; i <= block; i ++ )
        for(int j = i; j <= block; j ++ )
            for(int k = L[i]; k <= R[j]; k ++ )
            {
                cnt[i][j][a[k]] ++;
                if(cnt[i][j][a[k]] > cnt[i][j][mode[i][j]] || (a[k] < mode[i][j] && cnt[i][j][a[k]] == cnt[i][j][mode[i][j]]))
                    mode[i][j] = a[k];
            }
    
    // for(int i = 1; i <= 6; i ++ )
    //     for(int j = i; j <= 6; j ++ )
    //     {
    //         printf("%d %d:", i, j);
    //         for(int k = 0; k < 3; k ++ )
    //             printf(" %d", cnt[i][j][k]);
    //         puts("");

    //         printf("mode in [%d, %d] is %d\n", i, j, mode[i][j]);
    //     }
}

int tt[N];
void query(int l, int r)
{
    if(pos[l] == pos[r] || pos[l] + 1 == pos[r])
    {
        int modeest = 0;
        for(int i = l; i <= r; i ++ )
        {
            tt[a[i]] ++;
            if(tt[a[i]] > tt[modeest] || (a[i] < modeest && tt[a[i]] == tt[modeest]))
                modeest = a[i];
        }
        lastans = get(modeest);
        cout << lastans << endl;
        memset(tt, 0, sizeof tt);
    }
    else
    {
        int LL = L[pos[l] + 1], RR = R[pos[r] - 1];
        int Lblock = pos[l] + 1, Rblock = pos[r] - 1;
        // printf("[%d, %d]\n", Lblock, Rblock);
        int last_mode = mode[Lblock][Rblock];
        for(int i = l; i < LL; i ++ )
        {
            cnt[Lblock][Rblock][a[i]] ++;
            if(cnt[Lblock][Rblock][a[i]] > cnt[Lblock][Rblock][mode[Lblock][Rblock]] || 
                (a[i] < mode[Lblock][Rblock] && cnt[Lblock][Rblock][a[i]] == cnt[Lblock][Rblock][mode[Lblock][Rblock]]))
                mode[Lblock][Rblock] = a[i];
        }
        for(int i = RR + 1; i <= r; i ++ )
        {
            cnt[Lblock][Rblock][a[i]] ++;
            if(cnt[Lblock][Rblock][a[i]] > cnt[Lblock][Rblock][mode[Lblock][Rblock]] || 
                (a[i] < mode[Lblock][Rblock] && cnt[Lblock][Rblock][a[i]] == cnt[Lblock][Rblock][mode[Lblock][Rblock]]))
                mode[Lblock][Rblock] = a[i];
        }

        // for(int i = 0; i < 3; i ++ )
        //     printf("%d ", cnt[Lblock][Rblock][i]);
        // puts("");

        lastans = get(mode[Lblock][Rblock]);
        cout << lastans << endl;
        for(int i = l; i < LL; i ++ )
            cnt[Lblock][Rblock][a[i]] --;
        for(int i = RR + 1; i <= r; i ++ )
            cnt[Lblock][Rblock][a[i]] --;
        mode[Lblock][Rblock] = last_mode;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        nums.push_back(a[i]);
    }

    discretize();

    init();

    while(m -- )
    {
        int l = read(), r = read();
        l = (l + lastans - 1) % n + 1, r = (r + lastans - 1) % n + 1;
        if(l > r) swap(l, r);
        // printf("l: %d, r: %d\n", l, r);
        query(l, r);
        
    }

    return 0;
}
