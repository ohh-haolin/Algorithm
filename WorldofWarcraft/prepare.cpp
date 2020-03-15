#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


//全局变量初始化
int TIME = 0;

//士兵的基类
class Soldier {
  private:
    /* data */
  public:
    //名称
    char sname = 'B';
    //编号
    int id = -1;
    //当前生命值
    int HP = -1;
    //创造需要用的生命值
    static int cHP;
    //创造物品需要的最小生命值
    static int cHP_min;

    Soldier() { HP = this->cHP; }
    Soldier(int id_) {
        HP = this->cHP;
        id = id_;
    }

    //名称转换
    static string transName(char a);
    static char transName(string &a);
};


/*缩写转全称
 *
 *@param：char a表示缩写
 *@return： string，表示全称
 */
string Soldier::transName(char a) {
    string ans;
    if (a == 'i') { ans = "iceman"; }
    if (a == 'd') { ans = "dragon"; }
    if (a == 'n') { ans = "ninja"; }
    if (a == 'l') { ans = "lion"; }
    if (a == 'w') { ans = "wolf"; }
    return ans;
}

/*全程转缩写
 *
 *@param：string a，表示全称
 *@return： char，表示缩写
 */
char Soldier::transName(string &a) {
    if (a == "iceman") { return 'i'; }
    if (a == "dragon") { return 'd'; }
    if (a == "ninja") { return 'n'; }
    if (a == "lion") { return 'l'; }
    if (a == "wolf") { return 'w'; }

    return 'B';
}


//分别的士兵
class Dragon : public Soldier {
  private:
    /* data */
  public:
    char sname = 'd';
    static int cHP;
    Dragon(){};
    Dragon(int id_) : Soldier(id_) { HP = cHP; };
};


class Ninja : public Soldier {
  private:
    /* data */
  public:
    char sname = 'n';
    static int cHP;
    Ninja(){};
    Ninja(int id_) : Soldier(id_) { HP = cHP; };
};


class Iceman : public Soldier {
  private:
    /* data */
  public:
    char sname = 'i';
    static int cHP;
    Iceman(){};
    Iceman(int id_) : Soldier(id_) { HP = cHP; };
};


class Lion : public Soldier {
  private:
    /* data */
  public:
    char sname = 'l';
    static int cHP;
    Lion(){};
    Lion(int id_) : Soldier(id_) { HP = cHP; };
};


class Wolf : public Soldier {
  private:
    /* data */
  public:
    char sname = 'w';
    static int cHP;
    Wolf(){};
    Wolf(int id_) : Soldier(id_) { HP = cHP; };
};



//初始化成极大值
int Soldier::cHP = 0x3f3f3f3f;
int Dragon::cHP = 0x3f3f3f3f;
int Ninja::cHP = 0x3f3f3f3f;
int Iceman::cHP = 0x3f3f3f3f;
int Lion::cHP = 0x3f3f3f3f;
int Wolf::cHP = 0x3f3f3f3f;
int Soldier::cHP_min = 0x3f3f3f3f;

//队伍的基类
class Team {
  protected:
    vector<Iceman *> icemen;
    vector<Lion *> lions;
    vector<Wolf *> wolves;
    vector<Ninja *> ninjas;
    vector<Dragon *> dragons;

  public:
    //析构函数
    Team(){};
    Team(int x) { totleHP = x; };
    virtual ~Team();

    //队伍名称
    string teamName = "TEAM";

    int totleHP = -1;                          //临时初始化
    char sType[5] = {'B', 'B', 'B', 'B', 'B'}; //临时初始化
    int StimeDif = 0;

    //用于创建士兵的函数
    //基于时间判断士兵的生成类型
    char getTypeByTime(int t);
    //创建一个士兵
    char creatSoldier(int t);
    //打包好的生成士兵函数
    void genSoldier();

};


/*Team的析构函数，用于在结束时自动释放创建好的士兵
 *
 */
Team::~Team() {
    for (int i = 0; i < (int)icemen.size(); i++) { delete icemen[i]; }
    for (int i = 0; i < (int)lions.size(); i++) { delete lions[i]; }
    for (int i = 0; i < (int)wolves.size(); i++) { delete wolves[i]; }
    for (int i = 0; i < (int)ninjas.size(); i++) { delete ninjas[i]; }
    for (int i = 0; i < (int)dragons.size(); i++) { delete dragons[i]; }
}



/*根据时间获得类型
 *
 *@param: 一个int，表示时间
 *@return：返回一个char，表示当前时间应该创建的士兵类型
 */
char Team::getTypeByTime(int t) {
    int round = t % 5;
    return this->sType[round];
}

/*根据时间创建一个士兵并输出其相关信息
 *
 * @param: 一个int，表示时间
 * @return: 返回一个c，表示创建的好的战士类型
 *
 * @TODO:使用MAP优化代码
 */
char Team::creatSoldier(int t) {
    char type = getTypeByTime(t);
    char ans = 'B';

    string ST_FULL = "SS";
    int SHP = -1;
    int SID = -1;
    int Stotal = -1;


    if (type == 'd')
        if (this->totleHP >= Dragon::cHP) {
            this->totleHP -= Dragon::cHP;
            auto pS = new Dragon(TIME + 1);
            dragons.push_back(pS);
            ans = 'd';

            Stotal = this->dragons.size();
            ST_FULL = Soldier::transName(pS->sname);
            SHP = pS->HP;
            SID = pS->id;
        }

    if (type == 'n')
        if (this->totleHP >= Ninja::cHP) {
            this->totleHP -= Ninja::cHP;
            auto pS = new Ninja(TIME + 1);
            ninjas.push_back(pS);
            ans = 'n';

            Stotal = this->ninjas.size();
            ST_FULL = Soldier::transName(pS->sname);
            SHP = pS->HP;
            SID = pS->id;
        }

    if (type == 'i')
        if (this->totleHP >= Iceman::cHP) {
            this->totleHP -= Iceman::cHP;
            auto pS = new Iceman(TIME + 1);
            icemen.push_back(pS);
            ans = 'i';

            Stotal = this->icemen.size();
            ST_FULL = Soldier::transName(pS->sname);
            SHP = pS->HP;
            SID = pS->id;
        }

    if (type == 'l')
        if (this->totleHP >= Lion::cHP) {
            this->totleHP -= Lion::cHP;
            auto pS = new Lion(TIME + 1);
            lions.push_back(pS);
            ans = 'l';

            Stotal = this->lions.size();
            ST_FULL = Soldier::transName(pS->sname);
            SHP = pS->HP;
            SID = pS->id;
        }


    if (type == 'w')
        if (this->totleHP >= Wolf::cHP) {
            this->totleHP -= Wolf::cHP;
            auto pS = new Wolf(TIME + 1);
            wolves.push_back(pS);
            ans = 'w';

            Stotal = this->wolves.size();
            ST_FULL = Soldier::transName(pS->sname);
            SHP = pS->HP;
            SID = pS->id;
        }

    if (ans != 'B') {
        printf("%03d ", TIME);
        cout << teamName << ' ' << ST_FULL << ' ';
        printf("%d born with strength %d,%d ", SID, SHP, Stotal);
        cout << ST_FULL << " in " << teamName << " headquarter\n";
    }

    return ans;
}


/*根据时间创建所有的士兵
 *
 *@param：int t表示时间
 *
 */

void Team::genSoldier() {
    int time_ = TIME + this->StimeDif;

    for (int i = 0; i < 5; i++) {
        char ST = this->creatSoldier(time_ + i);
        if (ST == 'B') {
            this->StimeDif++;
            continue;
        }
        break;
    }
    this->StimeDif %= 5;
}

//两支队伍

class redTeam : public Team {
  private:
  public:
    redTeam() {}
    redTeam(int x) : Team(x) {
        teamName = "red";
        sType[0] = 'i', sType[1] = 'l', sType[2] = 'w', sType[3] = 'n',
        sType[4] = 'd';
    };
};



class blueTeam : public Team {
  private:
  public:
    blueTeam(){};
    blueTeam(int x) : Team(x) {
        teamName = "blue";
        sType[0] = 'l', sType[1] = 'd', sType[2] = 'n', sType[3] = 'i',
        sType[4] = 'w';
    };
};




/*初始化所有值
 *
 */
void restart() {
    Soldier::cHP = Dragon::cHP = Ninja::cHP = Iceman::cHP = Lion::cHP =
        Wolf::cHP = Soldier::cHP_min = 0x3f3f3f3f;
    TIME = 0;
}

/*计算生成士兵的最小消耗
 *
 * @return int 表示创建士兵的最小值
 */
int calScMin() {
    int ans = 0x3f3f3f3f;
    ans = min(ans, Dragon::cHP);
    ans = min(ans, Ninja::cHP);
    ans = min(ans, Iceman::cHP);
    ans = min(ans, Lion::cHP);
    ans = min(ans, Wolf::cHP);
    return ans;
}

int main() {
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);

    int Nround;
    cin >> Nround;
    for (int roundID = 1; roundID <= Nround; roundID++) {
        //恢复所有的变量
        restart();
        //开始新的一轮
        cout << "Case:" << roundID << endl;
        //读取总生命值并实例化队伍
        int tmp_totalHP;
        cin >> tmp_totalHP;
        redTeam *rt = new redTeam(tmp_totalHP);
        blueTeam *bt = new blueTeam(tmp_totalHP);
        //读入所有的士兵消耗的生命值并完成计算最小值
        cin >> Dragon::cHP >> Ninja::cHP >> Iceman::cHP >> Lion::cHP >>
            Wolf::cHP;
        Soldier::cHP_min = calScMin();

        bool redAbleGen = true, bludAbleGen = true;
        //生成士兵
        while (redAbleGen || bludAbleGen) {
            //红队生成
            if (rt->totleHP >= Soldier::cHP_min)
                rt->genSoldier();
            else {
                if (redAbleGen) {
                    printf("%03d ", TIME);
                    cout << rt->teamName;
                    printf(" headquarter stops making warriors\n");
                }
                redAbleGen = false;
            }
            //蓝队生成

            if (bt->totleHP >= Soldier::cHP_min)
                bt->genSoldier();
            else {
                if (bludAbleGen) {
                    printf("%03d ", TIME);
                    cout << bt->teamName;
                    printf(" headquarter stops making warriors\n");
                }
                bludAbleGen = false;
            }

            TIME++;
        }

        delete rt;
        delete bt;
    }
    return 0;
}