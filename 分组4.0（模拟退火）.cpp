#include<bits/stdc++.h>
#include<vector>
#define at 0.99999
#define endT 0.2
#include<windows.h>
#include<time.h>
#define inf 0x3f3f3f3f
using namespace std;
//tot[lea0[1-20]];male[lea0[1-20]];xb[ѧ��];blozzjoin[1]=15,
//leader[3][20]:leaders who join in this blo's selection
//member0[3][20]:members who will be selected in this blo����ʼ�⣩
vector<int>ve[101][202];
int ngrp,n,nblo,L=100000000,bl[202],level[101][202],lea0[202],leader[101][202],blozzjoin[101],tot[202],anstot[101][202],tottot[102],dislknum[101],member0[101][202],member[101][202],likep[202][202],male[202],stu1[4],stu2[4],numsolution;
bool xb[202],zz[202];
double worthnow=0,ans=0,fangcha[101],worthnewnew=0,score[101],jicha[101];
double r1=0,r2=0,r3=0,r4=0;
double T0;
int randnum=0;
string nam[202];
void sc(string s) {
	int ls=s.length();
	for(int i=0; i<ls; i++)cout<<s[i],Sleep(30);
}
double calworth() {
	double maxx=0,minx=inf;
	double sum=0,ave=0,s2=0,xbbl=0;
	int dislk=0;
	for(int i=1; i<=ngrp; i++)tot[lea0[i]]=0;
	for(int i=1; i<=ngrp; i++)male[lea0[i]]=0;

	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=blozzjoin[i]; j++)
			sum+=1.0*likep[leader[i][j]][member[i][j]],tot[leader[i][j]]+=likep[leader[i][j]][member[i][j]];

	ave=sum/ngrp*2;
	for(int i=1; i<=ngrp/2; i++) {
		s2+=(1.0*tot[lea0[i]]+tot[lea0[i+ngrp/2]]-ave)*(1.0*tot[lea0[i]]+tot[lea0[i+ngrp/2]]-ave);
	}
	s2/=ngrp/2;
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=blozzjoin[i]; j++) {
			male[leader[i][j]]+=(int)xb[member[i][j]];
			if(likep[leader[i][j]][member[i][j]]<14)dislk++;
		}
	for(int i=1; i<=ngrp; i++) {
		//	xbbl[lea0[i]]=1.0*male[lea0[i]]/nblo/2;
		if(male[lea0[i]]+male[lea0[i+ngrp/2]]+xb[lea0[i]]>4||male[lea0[i]]+male[lea0[i+ngrp/2]]+xb[lea0[i]]<3)xbbl+=1;
	}
	for(int i=1; i<=ngrp/2; i++)maxx=max((int)maxx,tot[lea0[i]]+tot[lea0[i+ngrp/2]]),minx=min((int)minx,tot[lea0[i]]+tot[lea0[i+ngrp/2]]);
	return sum-r2*xbbl-r3*(maxx-minx)-r1*s2;
}
void save() {
	int sum=0;
	double ave=0,maxx=0,minx=inf,min2x=inf;
	if(numsolution>99)return ;
	numsolution++;
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=blozzjoin[i]; j++) {
			ve[numsolution][leader[i][j]].push_back(member[i][j]);
		}
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=blozzjoin[i]; j++) {
			anstot[numsolution][leader[i][j]]+=likep[leader[i][j]][member[i][j]],sum+=likep[leader[i][j]][member[i][j]];
			if(likep[leader[i][j]][member[i][j]]<14)dislknum[numsolution]++;
		}
	tottot[numsolution]=sum;
	ave=1.0*sum/ngrp*2;
	for(int i=1; i<=ngrp/2; i++) {
		fangcha[numsolution]+=(1.0*anstot[numsolution][lea0[i]]+anstot[numsolution][lea0[i+ngrp/2]]-ave)*(1.0*anstot[numsolution][lea0[i]]+anstot[numsolution][lea0[i+ngrp/2]]-ave);
		maxx=max((int)maxx,tot[lea0[i]]+tot[lea0[i+ngrp/2]]),minx=min((int)minx,tot[lea0[i]]+tot[lea0[i+ngrp/2]]);
	}
	fangcha[numsolution]/=ngrp/2;
	jicha[numsolution]=maxx-minx;
	score[numsolution]=worthnewnew;
}
void SA(bool mark) {
	srand(randnum);
	double T=600.0;T0=T;
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=blozzjoin[i]; j++)member[i][j]=member0[i][j]; //memberΪ��̬��

	while(L--) {
		for(int i=1; i<=nblo; i++)stu1[i]=0,stu2[i]=0;//stuΪҪ������Ա
		double si=rand()%10000;
		si/=10000;
		//	cout<<si<<endl;
		for(int i=1; i<=nblo; i++) {
			stu1[i]=rand()%blozzjoin[i]+1;
			stu2[i]=rand()%blozzjoin[i]+1;
//			cout<<stu1[i]<<" "<<stu2[i]<<endl;
			if(stu1==stu2) continue;
			int tmp=member[i][stu1[i]];
			member[i][stu1[i]]=member[i][stu2[i]];
			member[i][stu2[i]]=tmp;
		}
//		cout<<endl;
		double worthnew=calworth();
//		if(L%1000)cout<<worthnew<<endl;
		double dE=worthnew-worthnow;
		if(mark&&ans<=worthnew)worthnewnew=worthnew,save(),cout<<"find solution\n";
		ans=max(ans,worthnew);
		if(dE>0||(exp(dE/T)>si)) {
			worthnow=worthnew;

		} else {
			for(int i=1; i<=nblo; i++) {
				int tmp=member[i][stu1[i]];
				member[i][stu1[i]]=member[i][stu2[i]];
				member[i][stu2[i]]=tmp;//give back
			}
		}
		T*=at;
		//	if(L%10000000)cout<<T<<" "<<worthnew<<endl;
		if(T<0.1)break ;
	}
	/*	for(int i=1; i<=nblo; i++) {
			cout<<i<<"blo "<<endl;
			for(int j=1; j<=blozzjoin[i]; j++)
				cout<<member[i][j]<<" ";
			cout<<endl;
		}*/
	cout<<"SA"<<(int)mark+1<<"completed\n";
	cout<<L<<endl;
}
int main() {
//	sc("������༶�������������ˣ�\n");
	cin>>n;
//	sc("������С�����\n");
	cin>>ngrp;
//	sc("������ÿλͬѧ���������Ա�������ǰ���Ա��ں���1��ʾ�У�0��ʾŮ����ư��м���Ϊ�У��Ŀư��м���ΪŮ����ѧ���������У�\n");
	for(int i=1; i<=n; i++)cin>>nam[i]>>xb[i];
//	sc("�������鳤�ǵ�ѧ�ţ�����˳��\n");
	for(int i=1; i<=ngrp; i++)cin>>lea0[i],zz[lea0[i]]=1,lea0[i+ngrp]=lea0[i]+n,zz[lea0[i]+n]=1;
	ngrp*=2,nblo=n/ngrp;
//	sc("�����밴���������ͬѧ�ǵ�ѧ��\n");
	for(int i=1; i<=nblo; i++) {
		int meminpos=0;
		for(int j=1; j<=ngrp; j++) {
			cin>>level[i][j];
			if(!zz[level[i][j]])member0[i][++meminpos]=level[i][j];
			//	cout<<i<<"i\n";
		}//����������
		//����ÿ������Ҫ��ѡ����Ա
	}
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++)bl[level[i][j]]=i;
	/*	for(int i=1; i<=nblo; i++)
			for(int j=1; j<=ngrp; j++)cout<<bl[level[i][j]]<<endl;
	*/
	for(int i=1; i<=ngrp; i++) {
		for(int j=1; j<=nblo; j++) {
			if(bl[lea0[i]]==j)continue;
			else leader[j][++blozzjoin[j]]=lea0[i];
		}
		//����ÿ�����вμ�ѡ����鳤�������ǵ�˫��̥�ܵܣ�
	}
//	for(int i=1; i<=nblo; i++)cout<<blozzjoin[i]<<" ";
//	sc("������ÿλ�鳤�Ա���ȫ����ѡ��Ա��ϲ����");
	int readnum=0;
	for(int i=1; i<=ngrp/2; i++)
		for(int j=1; j<=nblo; j++) {
			for(int k=1; k<=blozzjoin[j]; k++) {
				int u=0;
				cin>>u;
				likep[lea0[i]][member0[j][k]]=likep[lea0[i+ngrp/2]][member0[j][k]]=u;
				readnum++;
				if(readnum>ngrp/2*(n-ngrp/2)) {
					cout<<"�øж����ݶ�������ֵ������øж����ݸ���\n";
					return 0;
				}
			}
		}
	if(readnum<ngrp/2*(n-ngrp/2))cout<<"�øж�������������ֵ������øж����ݸ���\n";
	else cout<<"����"<<readnum<<"�����ݣ���������"<<endl;
	int moshi=0; 
	cout<<"���ϣ���������С�������� 1 �����ϣ���������С�������� 2 ",cin>>moshi ;
	cout<<"������øж�ƽ������ռȨ�أ�0~2.0֮��):",cin>>r3;
	if(moshi==2)swap(r3,r1);
	cout<<"�������Ա�ƽ������ռȨ�أ�0~10֮��)",cin>>r2;
	cout<<"��������������������Ķ��룬Ŀǰ�Ϻõ��У�524171��19260817)",cin>>randnum;
//	sc("333333\n"),Sleep(1000),sc("222222\n"),Sleep(1000),sc("111111\n"),Sleep(1000),sc("Go!\n");
	/*	for(int i=1; i<=nblo; i++) {
			cout<<i<<"blo "<<endl;
			for(int j=1; j<=blozzjoin[i]; j++)
				cout<<member0[i][j]<<" ";
			cout<<endl;
		}
	*/
	SA(0),SA(1);
	freopen("������.out","w",stdout);
	cout<<T0<<"T "<<r3<<" "<<r2<<endl;
	cout<<"��"<<numsolution<<"���"<<endl;
	cout<<ans<<endl;
	for(int i=1; i<=numsolution; i++) {
		for(int j=1; j<=ngrp/2; j++) {
			cout<<"��"<<j<<"�� "<<"�鳤: "<<nam[lea0[j]]<<" "<<"��Ա��";
			for(int k=0; k<ve[i][lea0[j]].size(); k++) {
				cout<<nam[ve[i][lea0[j]][k]]<<bl[ve[i][lea0[j]][k]]<<" "<<xb[ve[i][lea0[j]][k]]<<" "<<likep[lea0[j]][ve[i][lea0[j]][k]]<<" ";
				if(likep[lea0[j]][ve[i][lea0[j]][k]]<10)cout<<" ";
			}
			for(int k=0; k<ve[i][lea0[j+ngrp/2]].size(); k++) {
				cout<<nam[ve[i][lea0[j+ngrp/2]][k]]<<bl[ve[i][lea0[j+ngrp/2]][k]]<<" "<<xb[ve[i][lea0[j+ngrp/2]][k]]<<" "<<likep[lea0[j+ngrp/2]][ve[i][lea0[j+ngrp/2]][k]]<<" ";
				if(likep[lea0[j+ngrp/2]][ve[i][lea0[j+ngrp/2]][k]]<10)cout<<" ";
			}

			cout<<"\n-------"<<anstot[i][lea0[j]]+anstot[i][lea0[j+ngrp/2]]<<endl;
		}

		cout<<"��Ȩ�ͣ�"<<score[i]<<" �øж��ܺ�:"<<tottot[i]<<" ���"<<fangcha[i]<<" ��� "<<jicha[i]<<" ƽ��ֵ��"<<tottot[i]*1.0/ngrp*2<<" �øж�ƫ����Ա����"<<dislknum[i]<<"\n\n\n";
	}
}

//r1=0.1 r2=5 endT=0.2 srand:19260817/524171
//r2=10 r3=2.0 T=600
