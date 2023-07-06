#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef pair<int,int> PII;
int h[N],e[N],ne[N],idx;
int d[N],q[N];
bool st[N];
int t;
int n,m;

void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;

    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;

    while (hh <= tt)
    {
        int t = q[hh ++ ];

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }

    return tt == n - 1;
}



int main(){
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		
		scanf("%d%d",&n,&m);
		memset(h,-1,sizeof h);
		for(int i=1;i<n;i++) add(i,i+1);
		for(int i=0;i<m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			add(a,b);
			d[b]++;
		}
		if(topsort()){
			for(int i=0;i<n;i++) cout<<q[i]<<" ";
			puts("");
		}
		else cout<<"Impossible!"<<endl;
		memset(d,0,sizeof d);
	}
}
