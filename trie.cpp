#include<bits/stdc++.h>
using namespace std;
const int N=60,M=1e6+10;
const string O="OK",R="REPEAT",W="WRONG";
int son[N][26],idx,cnt[M],have[M];
int n,m;

void insert(char* s){
	int p=0;
	for(int i=0;s[i];i++){
		int u=s[i]-'a';
		if(!son[i][u]){
			son[i][u]=++idx;
		}
		p=son[p][u];
	}
	have[p]=1;
}

int query(char *s){
	int p=0;
	for(int i=0;s[i];i++){
		int u=s[i]-'a';
		if(!son[i][u]){
			return 0;
		}
		p=son[p][u];
	}
	if(!have[p]) return 0;
	if(!cnt[p]){
		cnt[p]++;
		return 1;
	}
	return 2;
}

int main(){
	freopen("P2580_2.in","r",stdin);
	freopen("P2580_2.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		char s[N];
		scanf("%s",s);
		insert(s);
	}
	
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		char s[N];
		scanf("%s",s);
		int p=query(s);
		if(p == 0 ) cout<<W<<endl;
		else if(p == 1) cout<<O<<endl;
		else if(p==2) cout<<R<<endl;
	}
	return 0;
}
