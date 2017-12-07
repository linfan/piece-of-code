#include <iostream.h>
#include <windows.h>
#include "LinkList.h"
#define SIZE 10
#define INFO 1 //显示读取的迷宫信息
#define PROCESS 1 //显示计算机思考过程
#define SHORTCUT 0 //显示到终点最短路径 
#define DEBUG 1 //运行错误时抛出错误

class LinkList;
class ListNode;
int GetTable(int Table[][SIZE]);
const int SearchBeginL(int (&Table)[SIZE][SIZE]);
const int SearchBeginR(int (&Table)[SIZE][SIZE]);
const int CountTheWays(int (&Table)[SIZE][SIZE], LinkList &recode, int L, int R);
void ShooseAWay(int (&Table)[SIZE][SIZE], LinkList &recode, int L, int R);
void Solution(LinkList &recode, LinkList &rightways);
void PutTheSolution(LinkList &rightways);
void GetAnswer(LinkList &rightways, char Answer[]);
void ShowView();
int add = 0;

void main() {

    ShowView();

    int Table[SIZE][SIZE];
    int NoFile = GetTable(Table);

    if (NoFile != 0) {
        LinkList recode;
        recode.CreatFristNode(0, 0, 0);
        recode.head->T_L = SearchBeginL(Table);
        recode.head->T_R = SearchBeginR(Table);

        int hereL = recode.head->T_L;
        int hereR = recode.head->T_R;//用于记录当前位置,取值为[0,SIZE]
        int directionS = CountTheWays(Table, recode, hereL, hereR); //用于记录当前可走的方向数,{原来起始点还要加1}
        recode.head->ways = directionS;
        Table[hereL][hereR] = 1;//取消起点标记
////////////////////////////////////////////////////
        if (PROCESS == 1) {
            cout << "\n\n以下是计算机思考过程:\nBeg  " << hereL + 1 << ',' << hereR + 1;
            add++;
            if (add % 4 == 0) {
                cout << endl;
            } else {
                cout << '\t';
            }
        }
////////////////////////////////////////////////////

        do {

            directionS = CountTheWays(Table, recode, hereL, hereR);

            if (directionS <= 0) { //无路可走
                for (int i = 0; i == 0;) { //不会自动结束的循环
                    if (recode.head == recode.tail) { //回到起点,无解退出
                        cout << "\n无解!" << endl;
                        Table[hereL][hereR] = 2;
                        break;
                    } else {
                        Table[hereL][hereR] = 0;//将此点标记为不可走
                        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        /////////////////////////////////////////////////////////////
                        if (PROCESS == 1) {
                            cout << "Pop  " << hereL + 1 << ',' << hereR + 1;
                            add++;
                            if (add % 4 == 0) {
                                cout << endl;
                            } else {
                                cout << '\t';
                            }
                        }
                        /////////////////////////////////////////////////////////////
                        recode.Drop();//退一栈
                        hereL = recode.tail->T_L;
                        hereR = recode.tail->T_R;//	获得前一步位置
                        if (recode.tail->ways > 0) {
                            (recode.tail->ways)--;    //退出循环一次
                            break;
                        }
                    }//否则ways必然为0,继续退栈
                }
            } else {
                recode.Creat(0, 0, directionS);
                ShooseAWay(Table, recode, hereL, hereR);
                hereL = recode.tail->T_L;
                hereR = recode.tail->T_R;
                //先进一栈,在尝试一个方向来走,最后刷新hereL、hereR、directionS
            }
            //////////////////////////////////////////////////////////////
            if (PROCESS == 1) {
                cout << "Push " << hereL + 1 << ',' << hereR + 1;
                add++;
                if (add % 4 == 0) {
                    cout << endl;
                } else {
                    cout << '\t';
                }
            }
            //////////////////////////////////////////////////////////////
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        } while (Table[hereL][hereR] != 2); //当到达终点时跳出循环
///////////////////////////////////
        if (SHORTCUT == 1) {
            cout << "\n\n以下是通往终点的路径:" << endl;
            recode.cur = recode.head;
            for (int i = 0; i < recode.counts; i++) {
                cout << recode.cur->T_L + 1 << ',' << recode.cur->T_R + 1 << endl;
                recode.cur = recode.cur->next;
            }
        }
        cout << endl;
///////////////////////////////////
        if (recode.head != recode.tail) { //当不是无解时
            char YorN;
            LinkList rightways;//记录计算机的到的走法
            Solution(recode, rightways);

            cout << "计算机已经找到了迷宫出口,你愿意自己尝试一次吗(Y/N)? ";
            cin >> YorN;
            if (YorN == 'y' || YorN == 'Y') {
                char InPut[200], Answer[200];
                GetAnswer(rightways, Answer);
                cout << "请直接输入路线,或输入help得到帮助信息,输入abort放弃尝试:" << endl;
                do {
                    cin >> InPut;
                    static int times = 1;
                    if (strcmp(InPut, "help") == 0 || strcmp(InPut, "HELP") == 0) { //帮助信息
                        cout << "\n地图说明:\n\t3 表示起点\t2 表示终点\n\t1 表示可通过\t0 表示不可通过" << endl;
                        cout << "输入说明:\n\t起点 *\t终点 #\n\t向上 w\t向下 s\n\t向左 a\t向右 d" << endl;
                        cout << "\t各项间用 - 相连\n\t如: 起点出发,向上,向左,向下,到达终点" << endl;
                        cout << "\t输入 *-w-a-s-# 回车即可\n现在请开始输入吧:" << endl;
                        continue;
                    }
                    if (strcmp(InPut, "abort") == 0 || strcmp(InPut, "ABORT") == 0) {
                        break;   //放弃尝试
                    }
                    if (strcmp(InPut, Answer) == 0 ) {
                        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
                        cout << "| 成功啦!                                   |" << endl;
                        switch (times) {
                        case 1:
                            cout << "| 干得漂亮!你的观察力相当优秀!              |" << endl;
                            break;
                        case 2:
                        case 3:
                            cout << "| 很不错哦,第" << times << "次就找到出口了!     |" << endl;
                            break;
                        case 4:
                        case 5:
                            cout << "| 呵~ 胜利总是属于能坚持的人哦!             |" << endl;
                            break;
                        default:
                            cout << "| 契而不舍是最可贵的精神哦!                 |" << endl;
                            break;
                        }
                        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
                        break;//跳出do循环
                    } else {
                        cout << "不完全正确,再试一试吧:" << endl;
                        times++;
                    }
                } while (1 == 1); //是当条件为真的时候继续循环!
            }
            //否则
            if (YorN == 'y' || YorN == 'Y') {
                cout << "正确答案:" << endl;
            } else {
                cout << "\n那么,现在公布正确答案了哦 --" << endl;
                system("pause");
            }

            cout << endl;
            PutTheSolution(rightways);
            cout << "\n\n+-----------------------------------------+\n";
            cout << "|  已将结果记录到Solution.txt中了 ^ê^     |\n";
            cout << "+-----------------------------------------+" << endl;
        }
    } else {
        cout << ".............................." << endl;
    }
    system("pause");
}
