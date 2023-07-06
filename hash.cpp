#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int N=1e6+10,P=131;
int n,m;


ULL gethash(string s){
	ULL hash=0;
	for(int i=0;i<s.size();i++){
		hash=hash*P+s[i];
	}
	return hash;
}

int main(){
	unordered_map<ULL,int> have,cnt;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		have[gethash(s)] = 1;
	}
	
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		string s;
		cin>>s;
		ULL h=gethash(s);
		cnt[h]++;
		if(have[h] == 0) cout<<"WRONG"<<endl;
		else {
			if(cnt[h] == 1) cout<<"OK"<<endl;
			else cout<<"REPEAT"<<endl;
		}
	}
}
