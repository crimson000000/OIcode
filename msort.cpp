#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;

int q[N];//���� 

int rev[N];//�����洢��ת������ 

void msort(int q[],int l,int r){
	if(l>=r) return;//�ݹ�߽� 
	int mid=l+r>>1;//ѡȡ�ֽ�� 
	msort(q,l,mid);msort(q,mid+1,r);//�ݹ鴦�� 
	int i=l,j=mid+1,k=0;
	while(i<=mid && j<=r){//˫ָ���㷨����2���������Сֵ����rev�� 
		if(q[i]<q[j]) rev[k++] = q[i++];
		else rev[k++] = q[j++];
	}
	while(i<=mid) rev[k++] =q[i++];//��ʣ������Ԫ�ط���rev 
	while(j<=r) rev[k++] =q[j++];
	for(int i=l,j=0;i<=r;i++) q[i]=rev[j++];//��rev��Ԫ�طŻ�q 
} 

int main(){
	int m;
	cin>>m;
	for(int i=0;i<m;i++) scanf("%d",&q[i]);
	msort(q,0,m-1);
	for(int i=0;i<m;i++) printf("%d ",q[i]);
	return 0; 
}
