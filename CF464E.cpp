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

const int N = 1e5 + 10, M = 2 * N, mod = 1e9 + 7, NN = 1e5 + 100;
int h[N], e[M], ne[M], w[M], idx;
int po[NN];
int n, m, S, T;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

struct segment
{
    int l, r;
    int sum, siz;
    ll hsh;
}t[NN * 77];
int tot, root[NN];

inline void pushup(int p)
{
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
    t[p].hsh = (t[t[p].r].hsh * po[t[t[p].l].siz] + t[t[p].l].hsh) % mod;
}

void build(int &p, int l, int r)
{
    p = ++ tot;
    t[p].siz = r - l + 1;
    if(l == r) return;
    int mid = l + r >> 1;
    build(t[p].l, l, mid);
    build(t[p].r, mid + 1, r);
    pushup(p);
}

void toone(int &p, int last, int l, int r, int pos)
{
    p = ++ tot, t[p] = t[last];
    if(l == r)
    {
        t[p].sum ++;
        t[p].hsh ++;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) toone(t[p].l, t[last].l, l, mid, pos);
    else toone(t[p].r, t[last].r, mid + 1, r, pos);
    pushup(p);
}

void tozero(int &p, int last, int init, int l, int r, int L, int R)
{
    if(l >= L && r <= R)
    {
        p = init;
        return;
    }
    p = ++ tot, t[p] = t[last];
    int mid = l + r >> 1;
    if(L <= mid) tozero(t[p].l, t[last].l, t[init].l, l, mid, L, R);
    if(R > mid) tozero(t[p].r, t[last].r, t[init].r, mid + 1, r, L, R);
    pushup(p);
}

int query(int p, int l, int r, int L, int R)
{
    if(l >= L && r <= R) return t[p].sum;
    int mid = l + r >> 1;
    int sum = 0;
    if(L <= mid) sum += query(t[p].l, l, mid, L, R);
    if(R > mid) sum += query(t[p].r, mid + 1, r, L, R);
    return sum; 
}

int find(int p, int l, int r, int k, int num)
{
    if(l == r) return l;
    int mid = l + r >> 1;
    if(t[t[p].l].sum >= mid - k + 1 + num) return find(t[p].r, mid + 1, r, k, num - t[t[p].l].sum);
    else return find(t[p].l, l, mid, k, num);
}

void change(int &x, int last, int pos)
{
    int c = 0;
    if(pos > 0) c = query(last, 0, N, 0, pos - 1);
    int y = find(last, 0, N, pos, c);
    if(y > pos) tozero(x, last, root[0], 0, N, pos, y - 1);
    else
        x = last;
    toone(x, x, 0, N, y);
}

bool cmp(int a, int b, int l, int r)
{
    if(l == r) return t[a].sum > t[b].sum;
    int mid = l + r >> 1;
    if(t[t[a].r].hsh == t[t[b].r].hsh) return cmp(t[a].l, t[b].l, l, mid);
    else return cmp(t[a].r, t[b].r, mid + 1, r);
}

struct Ver
{
    int id, root;
    bool operator <(const Ver& w) const
    {
        return cmp(root, w.root, 0, N);
    }
};
priority_queue<Ver> heap;

bool st[N];
int pre[N];
void dijkstra(int s, int t)
{
    build(root[0], 0, N);
    root[s] = root[0];
    
    heap.push({s, root[s]});
    while(!heap.empty())
    {
        auto k = heap.top();
        heap.pop();

        int ver = k.id;
        
        if(st[ver]) continue;
        st[ver] = true;
        if(ver == t) break;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            change(root[n + 1], root[ver], w[i]);
            if(!root[j] || cmp(root[j], root[n + 1], 0, N))
            {
                root[j] = root[n + 1];
                pre[j] = ver;
                if(!st[j]) heap.push({j, root[j]});
            }
        }
    }
}

int to[N];
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    po[0] = 1;
    
    for(int i = 1; i <= N; i ++ ) po[i] = po[i - 1] * 2 % mod; 

    scanf("%d%d", &S, &T);   
    dijkstra(S, T);

//    for(int i = 1; i <= n; i ++ ) cout << t[root[i]].hsh << endl;

    if(!st[T]) puts("-1");
    else
    {
        cout << t[root[T]].hsh << endl;
        int p = T;
        to[++ to[0]] = T;
        while(p != S)
        {
            p = pre[p];
            to[++ to[0]] = p;
        }
        cout << to[0] << endl;
        for(int i = to[0]; i > 0; i -- ) cout << to[i] << " ";
    }

    return 0;
}
