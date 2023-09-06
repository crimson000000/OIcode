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
char s[N], T[N];
int n, m, q;
struct node
{
    int l, r;
}t[N * 10];
int root[N], cnt;

void insert(int &p, int l, int r, int pos)
{
    if(!p) p = ++ cnt;
    if(l == r) return;
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, l, mid, pos);
    else insert(t[p].r, mid + 1, r, pos);
}

bool query(int p, int l, int r, int L, int R)
{
    if(!p || L > R) return false;
    if(l >= L && r <= R) return true;
    int mid = l + r >> 1;
    if(L <= mid && query(t[p].l, l, mid, L, R)) return true;
    if(R > mid && query(t[p].r, mid + 1, r, L, R)) return true;
    return false;
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    int p = ++ cnt;
    t[p].l = merge(t[x].l, t[y].l);
    t[p].r = merge(t[x].r, t[y].r);
    return p;
}

struct SuffixAM
{
    int tr[N][26], link[N];
    int len[N];
    bitset<N> in;
    int tag[N];
    int idx, last;

    void init()
    {
        for(int i = 0; i <= idx; i ++ ) 
        {
            memset(tr[i], 0, sizeof tr[i]);
            link[i] = 0;
            in[i] = false;
            tag[i] = 0;
            len[i] = 0;
        }
        link[0] = -1;
        idx = 0;
        last = 0;
    }

    void ins(char ch, int id)
    {
        int c = ch - 'a', p = last, cur = ++ idx;
        len[cur] = len[p] + 1;
        tag[cur] = id;
        in[cur] = true;
        while(p != -1 && !tr[p][c])
        {
            tr[p][c] = cur;
            p = link[p];
        }
        if(p == -1) link[cur] = 0;
        else
        {
            int q = tr[p][c];
            if(len[q] == len[p] + 1) link[cur] = q;
            else
            {
                int copy = ++ idx;
                link[copy] = link[q];
                len[copy] = len[p] + 1;
                tag[copy] = tag[q];
                for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
                while(p != -1 && tr[p][c] == q)
                {
                    tr[p][c] = copy;
                    p = link[p];
                }
                link[q] = link[cur] = copy;
            }
        }
        last = cur;
    }

    int id[N];
    void build()
    {
        for(int i = 0; i <= idx; i ++ ) id[i] = i;
        sort(id, id + idx + 1, [&](int x, int y){
            return len[x] < len[y];
        });

        // for(int i = 0; i <= idx; i ++ ) cout << id[i] << ' ';

        for(int i = idx; i >= 0; i -- ) 
        {
            int p = id[i];
            if(in[p]) insert(root[p], 1, n, len[p]);
            if(p) root[link[p]] = merge(root[link[p]], root[p]);
        }
    }
}SAM, TSAM;

int lim[N];
void solve()
{
    TSAM.init();
    scanf("%s", T + 1);
    m = strlen(T + 1);
    int l = read(), r = read();

    int len = 0, p = 0;
    for(int i = 1; i <= m; i ++ ) 
    {
        TSAM.ins(T[i], i);
        int c = T[i] - 'a';
        while(1)
        {
            if(SAM.tr[p][c] && query(root[SAM.tr[p][c]], 1, n, l + len, r))
            {
                len ++;
                p = SAM.tr[p][c];
                break;
            }
            if(!len) break;
            len --;
            if(len == SAM.len[SAM.link[p]]) p = SAM.link[p];
        }
        lim[i] = len;
        // cout << len << ' ';
    }

    ll ans = 0;
    // cout << TSAM.idx << endl;
    // cout << lim[0] << endl;
    for(int i = 1; i <= TSAM.idx; i ++ )
    {
        ans += max(0, TSAM.len[i] - max(TSAM.len[TSAM.link[i]], lim[TSAM.tag[i]]));
        // cout << TSAM.tag[i] << endl;
        // cout << ans << endl;
    }
    printf("%lld\n", ans);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);
    
    SAM.init();
    for(int i = 1; i <= n; i ++ ) SAM.ins(s[i], i);
    SAM.build();

    q = read();
    while(q -- ) solve();

    return 0;
}