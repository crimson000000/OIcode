#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int ne[N];
char str[N],st[N];
int main(){
	freopen("P3375_11.in","r",stdin);
	freopen("P3375.out","w",stdout);
	scanf("%s%s",str+1,st+1);
	ne[1]=0;
	int m=strlen(st+1),n=strlen(str+1);
//	cout<<m<<" "<<n<<endl;
	for(int i=2,j=0;i<=m;i++){
		while(j>0 && st[j+1]!=st[i]) j=ne[j];
		if(st[j+1] == st[i]) j++;
		ne[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j && st[j+1]!=str[i])j=ne[j];
		if(st[j+1]== str[i])j++;
		if(j==m){
			cout<<i-m+1<<endl;
			j=ne[j];
		}
	}
	for (int i=1;i<=m;i++)
    	printf("%d ",ne[i]);
    return 0;
}
