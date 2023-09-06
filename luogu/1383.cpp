#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct segment
{
    int l, r;
    char s;
    int size;
}tr[N * 4 + 17 * N];
int root[N], idx, node;
int n;

void insert(int &q, int p, int l, int r, char ch)
{
    q = ++ idx;
    tr[q] = tr[p];
    if(l > r) return;
    if(l == r)
    {
        tr[q].s = ch;
        tr[q].size = 1;
        return;
    }
    int mid = l + r >> 1;
    if(tr[tr[q].l].size >= mid - l + 1)
        insert(tr[q].r, tr[p].r, mid + 1, r, ch);
    else insert(tr[q].l, tr[p].l, l, mid, ch);
    tr[q].size = tr[tr[q].l].size + tr[tr[q].r].size;
}

char query(int p, int l, int r, int x)
{
    if(l >= r) return tr[p].s;
    int mid = l + r >> 1;
    if(x <= tr[tr[p].l].size) return query(tr[p].l, l, mid, x);
    else return query(tr[p].r, mid + 1, r, x - tr[tr[p].l].size);
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ )
    {
        char op[2], ch;
        int x;
        scanf("%s", op);
        if(*op == 'T')
        {
            cin >> ch;
            node ++;
            insert(root[node], root[node - 1], 1, n, ch);
        }
        else if(*op == 'Q')
        {
            scanf("%d", &x);
            cout << query(root[node], 1, n, x) << endl;
        }
        else
        {
            scanf("%d", &x);
            node ++;
            root[node] = root[node - x - 1];
        }
    }
    return 0;
}
