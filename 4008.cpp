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

const int N = 1e6 + 10;
struct node
{
    int l, r;
    char ch;
    int key, siz;
}t[4 * N];
int root, cnt, cur;

inline int New(char ch)
{
    t[++ cnt].ch = ch;
    t[cnt].key = rand();
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key > t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void split(int p, int siz, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[t[p].l].siz + 1 <= siz)
        {
            x = p;
            split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, siz, x, t[y].l);
        }
        pushup(p);
    }
}

char ins[3 * N];
int build(int l, int r)
{
    if(l == r) return New(ins[l]);
    int mid = l + r >> 1;
    int x = merge(build(l, mid), build(mid + 1, r));
    return x;
}

void ldr(int p)
{
    if(t[p].l) ldr(t[p].l);
    putchar(t[p].ch);
    if(t[p].r) ldr(t[p].r);
}

int n, x, y, z;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    while(n -- )
    {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'M')
        {
            int k = read();
            cur = k;
        }
        else if(op[0] == 'I')
        {
            int len = read();
            for(int i = 1; i <= len; i ++ )
            {
                ins[i] = getchar();
                if(ins[i] < 32 || ins[i] > 126) 
                {
                    i --; 
                    continue;
                }
            }
            split(root, cur, x, y);
            root = merge(merge(x, build(1, len)), y);
        }
        else if(op[0] == 'D')
        {
            int len = read();
            split(root, cur, x, y);
            split(y, len, y, z);
            root = merge(x, z);
        }
        else if(op[0] == 'G')
        {
            int len = read();
            split(root, cur, x, y);
            split(y, len, y, z);
            ldr(y);
            puts("");
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'P')
        {
            cur --;
        }
        else
        {
            cur ++;
        }
        // cout << "yeah" << endl;
    }
    
    return 0;
}
