#include <bits/stdc++.h>

#include <vector>
#define at 0.99999
#define endT 0.2
#define eps 0.00000001
//#define win
#ifdef Win
#include <windows.h>
#endif
#include <time.h>
#define inf 0x3f3f3f3f
using namespace std;
struct oneans {
  double d1, d2, d3, d4;
  friend bool operator<(oneans x, oneans y) {
    if (x.d3 != y.d3)
      return x.d3 < y.d3;
    else if (x.d4 != y.d4)
      return x.d4 < y.d4;
    return x.d1 < y.d1;
  }
};
map<oneans, bool> mp;
// lea_tmpsum[leader_id[1-20]];num_male[leader_id[1-20]];sex[学号];num_join_a_blo[1]=15,
// leaderid_blo_bloseq[3][20]:leaders who join in this blo's selection
// memberid0_blo_bloseq[3][20]:members who will be selected in this
// blo（初始解）
#define frndly
vector<int> ve[101][202];
int group_num, n, nblo,
    L = 100000000, L0 = 100000000, bl[202], id_blo_blornk[101][202],
    leader_id[202], leaderid_blo_bloseq[101][202], num_join_a_blo[101],
    lea_tmpsum[202], anstot[101][202], fonddegsum_ansid[102], dislknum[101],
    memberid0_blo_bloseq[101][202], memid_blo_bloseq[101][202], id_rnk[101],
    rnk_id[102], fonddeg_leaid_id[202][202], num_male[202], stu1bloseq_blo[4],
    stu2bloseq_blo[4], numsolution, hist[1000004];
int real_group_num, real_lea_num;
bool sex[202], islea_id[202];
double worthnow = 0, ans = 0, fangcha[101], worthnew_bak = 0, score[101],
       jicha[101],T_log[2000004];
double r1 = 0, r2 = 0, r3 = 0, r4 = 3.0;
double T0;
int randnum = 0;
string nam[202];
void sc(string s) {
  int ls = s.length();
#ifdef Win
  for (int i = 0; i < ls; i++) cout << s[i], Sleep(30);
#endif
#ifndef Win
  cout << s;
#endif
}

double calworth() {
  double maxx = 0, minx = inf;
  double sum = 0, ave = 0, s2 = 0, sex_por = 0;
  int dislk = 0;
  for (int i = 1; i <= group_num; i++) lea_tmpsum[leader_id[i]] = 0;
  for (int i = 1; i <= group_num; i++) num_male[leader_id[i]] = 0;

  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++) {
      sum +=
          1.0 *
          fonddeg_leaid_id[leaderid_blo_bloseq[i][j]][memid_blo_bloseq[i][j]],
          lea_tmpsum[leaderid_blo_bloseq[i][j]] +=
          fonddeg_leaid_id[leaderid_blo_bloseq[i][j]][memid_blo_bloseq[i][j]];
    }
  ave = sum / real_lea_num;
  for (int i = 1; i <= group_num / 2; i++) {
    s2 += (1.0 * lea_tmpsum[leader_id[i]] +
           lea_tmpsum[leader_id[i + group_num / 2]] - ave) *
          (1.0 * lea_tmpsum[leader_id[i]] +
           lea_tmpsum[leader_id[i + group_num / 2]] - ave);
  }
  s2 /= real_lea_num;
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++) {
      num_male[leaderid_blo_bloseq[i][j]] += (int)sex[memid_blo_bloseq[i][j]];
      if (fonddeg_leaid_id[leaderid_blo_bloseq[i][j]][memid_blo_bloseq[i][j]] <
          14)
        dislk++;
    }
  for (int i = 1; i <= group_num; i++) {
    if (num_male[leader_id[i]] + num_male[leader_id[i + group_num / 2]] +
                sex[leader_id[i]] >
            4 ||
        num_male[leader_id[i]] + num_male[leader_id[i + group_num / 2]] +
                sex[leader_id[i]] <
            3)
      sex_por += 1;
    //男生人数
  }
  for (int i = 1; i <= group_num / 2; i++)
    maxx = max((int)maxx, lea_tmpsum[leader_id[i]] +
                              lea_tmpsum[leader_id[i + group_num / 2]]),
    minx = min((int)minx, lea_tmpsum[leader_id[i]] +
                              lea_tmpsum[leader_id[i + group_num / 2]]);


  return sum - r2 * sex_por - r3 * (maxx - minx) - r1 * s2-r4*dislk;
}
inline void save() {
  int sum = 0;
  double ave = 0, maxx = 0, minx = inf, min2x = inf;
  if (numsolution > 99) return;
  numsolution++;
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++) {
      ve[numsolution][leaderid_blo_bloseq[i][j]].push_back(
          memid_blo_bloseq[i][j]);
    }
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++)
      anstot[numsolution][leaderid_blo_bloseq[i][j]] = 0;
  dislknum[numsolution] = 0;
  int eachdeg;
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++) {
      eachdeg =
          fonddeg_leaid_id[leaderid_blo_bloseq[i][j]][memid_blo_bloseq[i][j]];
      anstot[numsolution][leaderid_blo_bloseq[i][j]] += eachdeg, sum += eachdeg;
      if (fonddeg_leaid_id[leaderid_blo_bloseq[i][j]][memid_blo_bloseq[i][j]] <
          14)
        dislknum[numsolution]++;
    }
  fonddegsum_ansid[numsolution] = sum;
  ave = 1.0 * sum / real_group_num;
  for (int i = 1; i <= real_group_num; i++) {
    fangcha[numsolution] +=
        (1.0 * anstot[numsolution][leader_id[i]] +
         anstot[numsolution][leader_id[i + group_num / 2]] - ave) *
        (1.0 * anstot[numsolution][leader_id[i]] +
         anstot[numsolution][leader_id[i + group_num / 2]] - ave);
    maxx = max((int)maxx, lea_tmpsum[leader_id[i]] +
                              lea_tmpsum[leader_id[i + group_num / 2]]),
    minx = min((int)minx, lea_tmpsum[leader_id[i]] +
                              lea_tmpsum[leader_id[i + group_num / 2]]);
  }
  fangcha[numsolution] /= real_group_num;
  jicha[numsolution] = maxx - minx;
  score[numsolution] = worthnew_bak;
  if (mp[(oneans){fangcha[numsolution], jicha[numsolution], score[numsolution],
                  fonddegsum_ansid[numsolution]}])
    numsolution--;
  else
    mp[(oneans){fangcha[numsolution], jicha[numsolution], score[numsolution],
                fonddegsum_ansid[numsolution]}] = 1;
}

void SA(bool mark) {
  srand(randnum);
  double T = 180000.0;
  T0 = T;
  L = 100000000;
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= num_join_a_blo[i]; j++)
      memid_blo_bloseq[i][j] = memberid0_blo_bloseq[i][j];  // member为动态解




  while (L--) {
    for (int i = 1; i <= nblo; i++)
      stu1bloseq_blo[i] = 0, stu2bloseq_blo[i] = 0;  // stu为要换的组员
    double si = rand() % 10000;

    si /= 10000;
    for (int i = 1; i <= nblo; i++) {
      do{
      stu1bloseq_blo[i] = rand() % num_join_a_blo[i] + 1;
      stu2bloseq_blo[i] = rand() % num_join_a_blo[i] + 1;


      }while (stu1bloseq_blo[i] == stu2bloseq_blo[i])
      int tmp = memid_blo_bloseq[i][stu1bloseq_blo[i]];
      memid_blo_bloseq[i][stu1bloseq_blo[i]] =
          memid_blo_bloseq[i][stu2bloseq_blo[i]];
      memid_blo_bloseq[i][stu2bloseq_blo[i]] = tmp;
    }
    double worthnew = calworth();

    double dE = worthnew - worthnow;
    if (mark && ans == worthnew)
      worthnew_bak = worthnew, save(), cout << "find solution\n";
    ans = max(ans, worthnew);
    if (dE > 0 || (exp(dE / T) > si)) {  // Accepted
      worthnow = worthnew;

    } else {
      for (int i = 1; i <= nblo; i++) {
        int tmp = memid_blo_bloseq[i][stu1bloseq_blo[i]];
        memid_blo_bloseq[i][stu1bloseq_blo[i]] =
            memid_blo_bloseq[i][stu2bloseq_blo[i]];
        memid_blo_bloseq[i][stu2bloseq_blo[i]] = tmp;  // give back
      }
    }
    T *= at;
    if (T < eps) break;
  }

  cout << "SA" << (int)mark + 1 << "completed\n";
  cout << L0 - L << "steps" << endl;
}
int main() {
  freopen("输入数据2-utf-8.txt", "r", stdin);
#ifdef frndly
  sc("请输入班级人数（包括假人）\n");
#endif
  cin >> n;
#ifdef frndly
  sc("请输入小组个数\n");
#endif
  cin >> group_num;
//=blo_sz
#ifdef frndly
  sc("请输入每位同学的姓名和性别（姓名在前，性别在后，用1表示男，0表示女，理"
     "科"
     "班中假人为男，文科班中假人为女，按学号升序排列）\n");
#endif
  for (int i = 1; i <= n; i++) cin >> nam[i] >> sex[i];
#ifdef frndly
  sc("请输入组长们的学号（排名顺序）\n");
#endif
  for (int i = 1; i <= group_num; i++)
    cin >> leader_id[i], islea_id[leader_id[i]] = 1,
                         leader_id[i + group_num] = leader_id[i] + n,
                         islea_id[leader_id[i] + n] = 1;
  group_num *= 2, nblo = n / group_num;
#ifdef frndly
  sc("请输入同学们的按本次排名数升序排列的学号\n");
#endif
  for (int i = 1; i <= nblo; i++) {
    int num_join_now = 0;
    for (int j = 1; j <= group_num; j++) {
      cin >> id_blo_blornk[i][j];
      id_rnk[i * group_num * j] = id_blo_blornk[i][j];
      rnk_id[id_blo_blornk[i][j]] = i * group_num;
      if (!islea_id[id_blo_blornk[i][j]])
        memberid0_blo_bloseq[i][++num_join_now] = id_blo_blornk[i][j];
      //	cout<<i<<"i\n";
    }  //输入排名，
       //处理每个块中要被选的组员
  }
  for (int i = 1; i <= nblo; i++)
    for (int j = 1; j <= group_num; j++) bl[id_blo_blornk[i][j]] = i;
  //第i块中排名为j的人对应的块

  for (int i = 1; i <= group_num; i++) {
    for (int j = 1; j <= nblo; j++) {
      if (bl[leader_id[i]] == j)
        continue;
      else
        leaderid_blo_bloseq[j][++num_join_a_blo[j]] = leader_id[i];
    }
    //处理每个块中参加选择的组长（和他们的双胞胎弟弟）
  }

  	sc("请输入每位组长对本班全部待选组员的喜爱度");
  int readnum = 0;
  real_group_num = group_num / 2, real_lea_num = group_num / 2;
  for (int i = 1; i <= group_num / 2; i++)
    for (int j = 1; j <= nblo; j++) {
      for (int k = 1; k <= num_join_a_blo[j]; k++) {
        int u = 0;
        cin >> u;
        fonddeg_leaid_id[leader_id[i]][memberid0_blo_bloseq[j][k]] =
            fonddeg_leaid_id[leader_id[i + group_num / 2]]
                            [memberid0_blo_bloseq[j][k]] = u;
        readnum++;

        if (readnum > real_group_num * (n - real_lea_num)) {
          cout << "好感度数据多于正常值，请检查好感度数据个数\n";
          return 0;
        }
      }
    }
  if (readnum < real_group_num * (n - real_lea_num))
    cout << "好感度数据少于正常值，请检查好感度数据个数\n";
  else
    cout << "读入" << readnum << "个数据，读入正常" << endl;
  int moshi = 0;
  cout << "如果希望极差尽可能小，请输入 1 ，如果希望方差尽可能小，请输入 2 ",
      cin >> moshi;
  cout << "请输入好感度平均程度所占权重（0~2.0之间):", cin >> r3;
  if (moshi == 2) swap(r3, r1);
  cout << "请输入性别比例所占权重（0~10之间)", cin >> r2;
  cout << "请输入运算随机数（随心而入，目前较好的有：524171、19260817)",
      cin >> randnum;
  SA(0);
  SA(1);
  freopen("test.out", "w", stdout);
  cout << T0 << "°C " << r3 << "好感度和平均程度权重 " << r2 << "性别比例权重"
       << endl;
  cout << "共" << numsolution << "组解" << endl;
  cout << ans << endl;
  for (int i = 1; i <= numsolution; i++) {
    for (int j = 1; j <= group_num / 2; j++) {
      cout << "第" << j << "组 "
           << "组长: " << nam[leader_id[j]] << " "
           << "组员：";
      for (int k = 0; k < ve[i][leader_id[j]].size(); k++) {
        cout << nam[ve[i][leader_id[j]][k]] << bl[ve[i][leader_id[j]][k]] << " "
             << sex[ve[i][leader_id[j]][k]] << " "
             << fonddeg_leaid_id[leader_id[j]][ve[i][leader_id[j]][k]] << " ";
        if (fonddeg_leaid_id[leader_id[j]][ve[i][leader_id[j]][k]] < 10)
          cout << "??";
      }
      for (int k = 0; k < ve[i][leader_id[j + group_num / 2]].size(); k++) {
        cout << nam[ve[i][leader_id[j + group_num / 2]][k]]
             << bl[ve[i][leader_id[j + group_num / 2]][k]] << " "
             << sex[ve[i][leader_id[j + group_num / 2]][k]] << " "
             << fonddeg_leaid_id[leader_id[j + group_num / 2]]
                                [ve[i][leader_id[j + group_num / 2]][k]]
             << " ";
        if (fonddeg_leaid_id[leader_id[j + group_num / 2]]
                            [ve[i][leader_id[j + group_num / 2]][k]] < 10)
          cout << "??";
      }

      cout << "\n-------"
           << anstot[i][leader_id[j]] + anstot[i][leader_id[j + group_num / 2]]
           << endl;
    }

    cout << "加权和：" << score[i] << " 好感度总和:" << fonddegsum_ansid[i]
         << " 方差：" << fangcha[i] << " 极差： " << jicha[i] << " 平均值："
         << fonddegsum_ansid[i] * 1.0 / group_num * 2 << " 好感度偏低组员个数"
         << dislknum[i] << "\n\n\n";
  }
  cout << hist[0] << "交换次数" << endl;



}

