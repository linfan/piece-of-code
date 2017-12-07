#include <iostream.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#define BeginScore 2000

void Welcome(char[]);//欢迎界面
void SwitchCard(const int Card_i, char (&Card_c)[3]); //牌面int->char
const void GameView(char (&Card_char)[5][3], const char (&name)[10], const int Score, const int goal,
                    const int bet); //游戏主界面
void LoadCard(int (&Card_int)[5], char (&Card_char)[5][3]); //随机生成5张牌
void GetPrize(const int (&Card_int)[5], int &bet); //判断中奖级别
void ChangeHandCard(int (&Card_int)[5], char (&Card_char)[5][3], char (&InPuts)[5], int (&InPut)[6],
                    int (&temp)[5]); //更换手牌
void InPuts_to_InPut(char (&InPuts)[5], int (&InPut)[6]); //换牌号char->int
void SmallorBig(int &bet);//猜大小游戏

void main() {
    int Card_int[5];//记录5张手牌的数字表示
    int Score = BeginScore;//积分点数
    int goal;//目标点数
    int bet;//赌注
    char Card_char[5][3];//记录5张手牌的字符表示
    char name [10];//玩家姓名
    char InPuts[5];//记录更换手牌号
    int InPut[6];//同上
    int temp[5];//更换手牌时的临时牌记录
    int len;//临时记录一个字符串长度
    int numb = 1;//记录第几局

    srand(time(0) + rand() / 7);
    Card_int[0] = rand() % 52;
    if (Card_int[0] == 0)Card_int[0] = 52;
    SwitchCard(Card_int[0], Card_char[0]);
//得到欢迎界面上扑克牌的随机花色

    Welcome(Card_char[0]);//显示欢迎界面
    cout << "\n按下任意键开始游戏 " << endl;
//不加endl则这句话会自动被放到pause以后去执行
    system("pause");
    cout << "\n输入玩家姓名: ";
    cin >> name;

    cout << "\n您好! " << name << " ,欢迎参与幸运扑克游戏! 您的初始积分为 " << Score << " 点。" << endl;

    cout << "请输入一个数值作为您的目标积分点数: ";
    cin >> goal;
    do {
        if (goal <= BeginScore ) {
            cout << "\n目标积分应大于您的初始积分,请重新输入: ";
            cin >> goal;
            continue;
        }
        break;
    } while (1 == 1); //BUG:当输入一个非数字时会变成死循环

    cout << "\n                      #  第 1 局  #\n" << endl;
    cout << "\n输入您第1局的赌注额[1~500]: ";

    do { //游戏主循环

        cin >> bet;
        do {
            if (bet > 500 || bet < 1) {
                cout << "\n赌注数额应在1~500之间,请重新输入: ";
                cin >> bet;
                continue;
            }
            if (bet > Score) {
                cout << "\n您的积分点数不足,请重新输入: ";
                cin >> bet;
                continue;
            }
            break;
        } while (1 == 1); //BUG:当输入一个非数字时会变成死循环

        Score -= bet;

        cout << "\n按下任意键开始发牌" << endl;
        system("pause");

        cout << "\n系统洗牌中,请稍候" << endl;

        LoadCard(Card_int, Card_char); //随机获得手牌Card_int和Card_char
//ServeTheCard(Card_char);//显示发牌屏幕
        GameView(Card_char, name, Score, goal, bet); //显示游戏界面
        temp[0] = 0;//借用temp[0]
        cout << "当前牌面: ";
        GetPrize(Card_int, temp[0]);
        temp[0] = 0;
        cout << endl;

        cout << "\n依次输入要更换的手牌序号[输入0表示不更换]: ";
        cin >> InPuts;

        do {
            len = strlen(InPuts);
            if (len > 5) {
                cout << "\n最多只有5张牌!请重新输入: ";
                cin >> InPuts;
                len = strlen(InPuts);
                continue;
            }
            break;
        } while (1 == 1);

        InPuts_to_InPut(InPuts, InPut); //InPuts[n]转InPut[n]

        int	j;
        do {
            len = strlen(InPuts);
            j = 0;
            if (strcmp(InPuts, "0") == 0) {
                break;
            } else {
                for (int i = 0; i < len; i++) {
                    if (InPut[i] < 1 || InPut[i] > 5) {
                        cout << "\n输入格式错误!,请重新输入: ";
                        for (int n = 0; n < 5; n++) {
                            InPuts[n] = '\0';   //还原InPuts
                        }
                        for (int m = 0; m < 5; m++) {
                            InPut[m] = -858993460;   //还原InPut
                        }
                        cin >> InPuts;
                        j = 1;
                        break;
                    }
                }
                if (j == 0) {
                    for (int k = 0; k < len; k++) {
                        for (int m = 0; m < len; m++) {
                            if (m != k && InPut[k] == InPut[m]) {
                                cout << "\n输入的序号有重复!,请重新输入: ";
                                cin >> InPuts;
                                k = 5;
                                j = 1;
                                break;
                            }
                        }
                    }
                }
            }
            InPuts_to_InPut(InPuts, InPut); //InPuts[n]转InPut[n]
        } while (j != 0); //BUG:当输入一个非数字时会变成死循环

        if (strcmp(InPuts, "0") != 0) {
            ChangeHandCard(Card_int, Card_char, InPuts, InPut, temp);
        }

        GameView(Card_char, name, Score, goal, bet);
        GetPrize(Card_int, bet);
        if (bet != 0) { //如果中奖
            SmallorBig(bet); //参与猜大小游戏
            Score += bet; //改变Score值
        }
        if (Score <= 0) {
            cout << "\n  ！！！！！！！！！！！！！！" << endl;
            _sleep(200);
            cout << "   积分用完了哦。不过不要灰心," << endl;
            _sleep(200);
            cout << "   世上无难事,只怕有心人。" << endl;
            _sleep(200);
            cout << "   继续努力,大奖一定属于你!\n" << endl;
            break;
        }
        if (Score >= goal) {
            cout << "\n  ￥￥￥￥￥￥￥￥￥￥￥￥￥￥" << endl;
            _sleep(200);
            cout << "   今天的目标达到啦!" << endl;
            _sleep(200);
            cout << "   放松心情,好好休息一下吧。" << endl;
            _sleep(200);
            cout << "   身体健康才是最大的财富哦!\n" << endl;
            break;
        }

        numb++;
        cout << "\n                      #  第 " << numb << " 局  #\n" << endl;
        cout << "\n您当前拥有积分点数: " << Score << " 点" << endl;
        cout << "您为自己设定的目标点数为: " << goal << " 点" << endl;
        cout << "现在请为下一轮游戏输入下注点数: ";

    } while (1 == 1); //主循环结束

    system("pause");

}
