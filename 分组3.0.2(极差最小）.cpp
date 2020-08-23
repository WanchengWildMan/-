#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#include<windows.h>
#include<time.h>
using namespace std;
vector<int>ve[2000],ansve[2000];
int W[105][105][105],n;
int Lx[1005],Ly[1005];
int Left[1005],lea0[1001],lea[1001],leanow[200][1005],e;
bool S[1005],T[1005],zz[1000],out[1004];
string nam[700];
int xh[700][700],blosz[200],nblo,ngrp,bl[1005],tot[1000],anstot[1004],WOrder[10004],likep[1005][1005],ordzzin[1005],mark[2005],nzzblo[1005];
int cantchoose[200][1005],nzznow[1005],Wpos=0,minjicha=inf;
double minfangcha=inf*1.0;
int worknum=0;
double musicalnote[10]= {0,261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25,587.3};
void sc(string s) {
	int ls=s.length();
	for(int i=0; i<ls; i++)cout<<s[i],Sleep(30);
}
bool match(int i,int k) {
	S[i]=1;
	for(int j=1; j<=blosz[k]; j++) {
//	cout<<i<<"I "<<j<<"J "<<Lx[i]+Ly[j]<<" "<<W[i][j]<<endl;
		if(Lx[i]+Ly[j]==W[k][i][j]&&!T[j]) {
			T[j]=1;

			if(!Left[j]||match(Left[j],k)) {

//				cout<<j<<"j "<<Left[j]<<" ";
//				cout<<i<<"i\n";

				Left[j]=i;
				return 1;
			}

		}
	}
	return 0;
}
void update(int k) {
	int a=inf;
	for(int i=1; i<=blosz[k]; i++)
		if(S[i])
			for(int j=1; j<=blosz[k]; j++)
				if(!T[j]) {
					a=min(a,Lx[i]+Ly[j]-W[k][i][j]);
				}
	for(int i=1; i<=blosz[k]; i++) {
		if(S[i])Lx[i]-=a;
		if(T[i])Ly[i]+=a;
	}
}
void KM(int k) {
	for(int i=1; i<=blosz[k]; i++) {
		Left[i]=Lx[i]=Ly[i]=0;
		for(int j=1; j<=blosz[k]; j++)
			Lx[i]=max(Lx[i],W[k][i][j]);
	}

	for(int i=1; i<=blosz[k]; i++) {
		for(;;) {
			for(int j=1; j<=n; j++)S[j]=T[j]=0;
			if(match(i,k))break;
			else update(k);
		}
	}
}
void initgrp() {
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++) {
			bl[xh[i][j]]=i;
			if(!zz[xh[i][j]])blosz[i]++;
			else nzzblo[bl[xh[i][j]]]++;

			//		cout<<xh[i][j]<<" "<<bl[xh[i][j]]<<endl;
		}
//
	for(int i=1; i<=ngrp; i++)cantchoose[bl[i]][i]=1;
}
void initW(int k) {
	int sum=0;
	for(int i=1; i<=nblo; i++) {
		if(bl[lea[k]]!=i) {
			int p=++nzznow[i],l=0;
			leanow[i][p]=lea[k];
//			cout<<i<<"i "<<p<<"p "<<k<<"k "<<lea[k]<<endl;;
			for(int j=1; j<=ngrp; j++) {
				if(!zz[xh[i][j]])W[i][p][++l]=WOrder[Wpos++],sum++;
			}
		}
	}
//	cout<<sum<<"sum\n";
}

void pb(int k) {
//	int tot=0;
	int l=0;
//	cout<<"test\n";
	int numpb=0;
	for(int i=1; i<=ngrp; i++) {
		if(zz[xh[k][i]])continue;
		ve[leanow[k][Left[++l]]].push_back(xh[k][i]);
		numpb++;
		tot[leanow[k][Left[l]]]+=W[k][Left[l]][l];
		//tot+=W[k][Left[l]][l];
//		cout<<leanow[k][Left[l]]<<endl;
//		cout<<nam[leanow[k][Left[l]]]<<" "<<nam[xh[k][i]]<<endl;
	}
//	cout<<numpb<<endl;
//	cout<<tot<<endl;
}
void clr() {
	for(int i=1; i<=n; i++)S[i]=T[i]=0,Left[i]=0;
}
bool cmp(int x,int y) {
	return bl[x]<bl[y];
}
int caljicha() {
	int maxx=0,minx=inf;
	for(int i=1; i<=ngrp/2; i++)maxx=max(maxx,tot[lea[i]]+tot[lea[i+ngrp/2]]),minx=min(minx,tot[lea[i]]+tot[lea[i+ngrp/2]]);
	return maxx-minx;
}
double calfangcha(){
	double ave=0,totnow=0,s2=0;
	for(int i=1;i<=ngrp/2;i++)totnow+=tot[lea[i]]+tot[lea[i+ngrp/2]];
	ave=totnow/ngrp;
	for(int i=1;i<=ngrp/2;i++)s2+=(tot[lea[i]]-ave)*(tot[lea[i]]-ave)+(tot[lea[i+ngrp/2]]-ave)*(tot[lea[i+ngrp/2]]-ave);
	return s2*1.0/ngrp;
}
void gengxinvetot() {
	for(int i=1; i<=ngrp; i++)
		ansve[lea[i]].clear();
	for(int i=1; i<=ngrp; i++)
		for(int j=0; j<ve[lea[i]].size(); j++)
			ansve[lea[i]].push_back(ve[lea[i]][j]);
	for(int i=1; i<=ngrp; i++)anstot[lea0[i]]=tot[lea0[i]];
}
void work() {
	int inpos=1;
	for(int i=1; i<=ngrp/2; i++)lea[i]=lea0[ordzzin[i]],lea[i+ngrp/2]=lea0[ordzzin[i]]+n   ;                                                                            ;
	Wpos=1;
	for(int i=1; i<=ngrp/2; i++)
		for(int j=1; j<=n-ngrp-ngrp/2+nzzblo[bl[lea[i]]]; j++)WOrder[inpos++]=likep[ordzzin[i]][j];
	for(int i=1; i<=ngrp/2; i++)
		for(int j=1; j<=n-ngrp/2; j++)WOrder[inpos++]=likep[ordzzin[i]+ngrp/2][j];
//	for(int i=1;i<=inpos;i++)cout<<WOrder[i]<<"W"<<endl;
	for(int i=1; i<=ngrp; i++) {
//	cout<<i<<"III\n";
		initW(i);
	}
	for(int i=1; i<=nblo; i++)
		KM(i),pb(i),clr();
	int temp=caljicha();
	if(minjicha>temp) {
		minjicha=temp;
		gengxinvetot();
	}
/*	double tmp=calfangcha();
	if(minfangcha>tmp){
		minfangcha=tmp;
		gengxinvetot();
	}
*/
//	freopen("分组.out","w",stdout);
	/*	for(int i=1;i<=nblo;i++){
		cout<<i<<"i ";
		for(int j=1;j<=ngrp;j++)cout<<leanow[i][j]<<" ";
		cout<<endl;
		}*/

	/*	cout<<"BLO:\n";
		for(int i=1; i<=nblo; i++)
			for(int j=1; j<=ngrp; j++)cout<<xh[i][j]<<" "<<bl[xh[i][j]]<<endl;*/


}
void clr2() {
	for(int i=1; i<=ngrp; i++)ve[lea0[i]].clear();
	for(int i=1; i<=Wpos-1; i++)WOrder[i]=0;
	for(int i=1; i<=nblo; i++)nzznow[i]=0;
	if(!(ordzzin[1]==ngrp/2&&ordzzin[ngrp/2]==1))for(int i=1; i<=ngrp; i++)tot[lea0[i]]=0;
}
void pai(int cur) {
//	if(ordzzin[1]!=1&&ordzzin[1])return ;
//	cout<<1111111111<<endl;
	if(cur>ngrp/2) {
		worknum++;
		if(worknum%36288==0)cout<<worknum/36288<<"%\n";
//		for(int j=1; j<=ngrp/2; j++)cout<<ordzzin[j]<<" ";
//		cout<<endl;
		work();
		//if(!out[ordzzin[1]])cout<<ordzzin[1]-1<<"0%\n",out[ordzzin[1]]=1,Beep(musicalnote[ordzzin[1]],1000);
		if(!out[ordzzin[1]])out[ordzzin[1]]=1,Beep(musicalnote[ordzzin[1]],1000);
		clr2();
		return ;
	}
	for(int i=1; i<=ngrp/2; i++) {
		if(mark[i])continue;
		mark[i]=1;
		ordzzin[cur]=i;
		pai(cur+1);
		mark[i]=0;
	}
}
void swaptogether(int stu1,int stu2) {
	int posti,postj,posxi,swpposi,swpposj;
	if(!zz[stu1]&&!zz[stu2]) {
		for(int i=1; i<=ngrp; i++)
			for(int j=0; j<ansve[lea0[i]].size(); j++) {
				if(ansve[lea0[i]][j]==stu1)posti=i,postj=j;
				if(ansve[lea0[i]][j]==stu2)posxi=i;
				if(i==posxi&&bl[ansve[lea0[i]][j]]!=bl[stu1])swpposi=i,swpposj=j;
			}
		int tep=ansve[lea[swpposi]][swpposj];
		ansve[lea[swpposi]][swpposj]=ansve[lea[posti]][postj];
		ansve[lea[posti]][postj]=tep;
	}

}
int main() {
//	freopen("分组样例5.in","r",stdin);

	sc("请输入班级人数（包括假人）\n");
	cin>>n;
	sc("请输入小组个数\n");
	cin>>ngrp;
	sc("请输入每位同学的姓名（按学号升序排列）\n");
	for(int i=1; i<=n; i++)cin>>nam[i];
	sc("请输入组长们的学号（初始顺序）\n");
	for(int i=1; i<=ngrp; i++)cin>>lea0[i],zz[lea0[i]]=1,lea0[i+ngrp]=lea0[i]+n,zz[lea0[i]+n]=1;
	sc("请输入按排名排序的同学们的学号\n");
	ngrp*=2,nblo=n/ngrp;
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++) {
			cin>>xh[i][j];
		}
	/*		for(int i=1; i<=nblo; i++)
			for(int j=1; j<=ngrp; j++)cout<<xh[i][j]<<endl;
	*/
	int numin=0;
	initgrp();
//	for(int i=1; i<=3; i++)cout<<nzzblo[i]<<"nzzblo"<<endl;
	sc("请输入每位组长对不是其本人所处块中的待选组员的喜爱度，再输入每位组长对本班全部待选组员的喜爱度");
	for(int i=1; i<=ngrp/2; i++)
		for(int j=1; j<=n-ngrp-ngrp/2+nzzblo[bl[lea0[i]]]; j++)cin>>likep[i][j],numin++;//nzzblo：每个块中组长的人数 

	for(int i=1; i<=ngrp/2; i++)
		for(int j=1; j<=n-ngrp/2; j++)cin>>likep[i+ngrp/2][j],numin++;//

	cout<<numin<<endl;
	sc("3\n"),Sleep(1000),sc("2\n"),Sleep(1000),sc("1\n"),Sleep(1000),sc("Go!\n");
//	PlaySound("C:\\BGM.wav",NULL,SND_FILENAME|SND_ASYNC);
//system("D:\\BGM.mp3");
	pai(1);
//	swaptogether(11,21);
	freopen("fenzu.out","w",stdout);
	for(int i=1; i<=ngrp/2; i++) {
		cout<<"第"<<i<<"组：   ";
		cout<<"组长:"<<nam[lea0[i]]<<" 组员： ";
		//		cout<<ve[lea[i]].size()<<"sz\n";
		//	cout<<nam[ve[lea[i]][4]];
		sort(ansve[lea0[i]].begin(),ansve[lea0[i]].end(),cmp);
		sort(ansve[lea0[i+ngrp/2]].begin(),ansve[lea0[i+ngrp/2]].end(),cmp);
		for(int j=0; j<ansve[lea0[i]].size(); j++)cout<<nam[ansve[lea0[i]][j]]<<bl[ansve[lea0[i]][j]]<<" ";
		for(int j=0; j<ansve[lea0[i+ngrp/2]].size(); j++)cout<<nam[ansve[lea0[i+ngrp/2]][j]]<<bl[ansve[lea0[i+ngrp/2]][j]]<<" ";
		cout<<endl;
	}
	for(int i=1; i<=8; i++)Beep(musicalnote[i],80),Beep(musicalnote[i]+(musicalnote[i+1]-musicalnote[i])/3,80),Beep(musicalnote[i]+2*(musicalnote[i+1]-musicalnote[i])/3,80);
	int likenum=0;
	for(int i=1; i<=ngrp/2; i++) {
		cout<<anstot[lea0[i]]+anstot[lea0[i+ngrp/2]]<<endl;
		likenum+=anstot[lea0[i]]+anstot[lea0[i+ngrp/2]];
	}
	cout<<likenum;
	/*	for(int i=1; i<=ngrp/2; i++) {
			cout<<lea0[i]<<" "<<lea0[i+ngrp/2]<<endl;
			likenum+=tot[lea0[i]]+tot[lea0[i+ngrp/2]];
		}
	*/
}
