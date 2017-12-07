#include <iostream.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //产生随机数的rand()函数在此
#include <ctime> //返回当前时间time_t time( time_t *time )函数在此


#define THDS 250 //同花大顺
#define THS  50  //同花顺
#define SiT  25  //四同
#define HL   9   //葫芦
#define TH   6   //同花 
#define SZ   4   //顺子
#define SaT  3   //三同
#define LD   2   //两对
#define YD   1   //一对J以上


void GetPrize(const int (&Card_int)[5], int &bet) {

    /* ------------------------ 判断手牌 ------------------------ */

    int count1 = 0, count2 = 0, count3 = 0, prize = 0, minnum = 53, maxnum = 0;
    int temp1 = 0, temp2 = 0, temp3 = 0, mintemp = 53, maxtemp = 0, temp[5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (Card_int[i] - Card_int[j] == 13) {
                count1++;
            }
            if (Card_int[i] - Card_int[j] == 26) {
                count2++;
            }
            if (Card_int[i] - Card_int[j] == 39) {
                count3++;
            }
        }
    }//得到有几张同号的牌

    for (int k = 0; k < 5; k++) {
        if (Card_int[k] > maxnum)maxnum = Card_int[k];   //最大手牌
    }
    for (int n = 0; n < 5; n++) {
        if (Card_int[n] < minnum)minnum = Card_int[n];   //最小手牌
    }

    if (maxnum < 14)temp1 = 1;
    else if (maxnum < 27 && minnum > 13)temp1 = 1;
    else if (maxnum < 40 && minnum > 26)temp1 = 1;
    else if (minnum > 39)temp1 = 1;
    else temp1 = 0;//判断是否同花

    for (int q = 0; q < 5; q++) {
        if (Card_int[q] < 14) {
            temp[q] = Card_int[q];
        } else if (Card_int[q] > 13 && Card_int[q] < 27) {
            temp[q] = Card_int[q] - 13;
        } else if (Card_int[q] > 26 && Card_int[q] < 40) {
            temp[q] = Card_int[q] - 26;
        } else {
            temp[q] = Card_int[q] - 39;
        }
    }
    for (int r = 0; r < 5; r++) {
        if (temp[r] > maxtemp)maxtemp = temp[r];
    }
    for (int t = 0; t < 5; t++) {
        if (temp[t] < mintemp)mintemp = temp[t];
    }
    if (maxtemp - mintemp == 4) {
        temp2 = 1;   //判断是否顺子
    }

////////////////////////////////////////// DEBUG
//cout<<"minnum: "<<minnum<<"    maxnum: "<<maxnum<<endl;
//cout<<"count1: "<<count1<<"    count2: "<<count2<<"    count3: "<<count3<<endl;
////////////////////////////////////////// DEBUG

    /* ------------------------ 返回结果 ------------------------ */

    if (temp1 == 1 && temp2 == 1) {
        if (minnum == 9 || minnum == 22 || minnum == 35 || minnum == 48) {
            bet *= THDS;    //同花大顺
            cout << "同花大顺" << endl;
            return;
        } else {
            bet *= THS;    //同花顺
            cout << "同花顺" << endl;
            return;
        }
    }
    if (count1 == 3 && count2 == 2 && count3 == 1) {
        bet *= SiT;    //四同
        cout << "四同" << endl;
        return;
    }
    if (count1 == 3 && count2 == 1 && count3 == 0) {
        bet *= HL;    //葫芦
        cout << "葫芦" << endl;
        return;
    } else if (count1 == 2 && count2 == 1 && count3 == 1) {
        bet *= HL;
        cout << "葫芦" << endl;
        return;
    } else if (count1 == 2 && count2 == 2 && count3 == 0) {
        bet *= HL;
        cout << "葫芦" << endl;
        return;
    } else if (count1 == 1 && count2 == 2 && count3 == 1) {
        bet *= HL;
        cout << "葫芦" << endl;
        return;
    } else if (count1 == 1 && count2 == 1 && count3 == 2) {
        bet *= HL;
        cout << "葫芦" << endl;
        return;
    }
    if (temp1 == 1) {
        bet *= TH;    //同花
        cout << "同花" << endl;
        return;
    }
    if (temp2 == 1) {
        bet *= SZ;    //顺子
        cout << "顺子" << endl;
        return;
    }
    if (count1 == 2 && count2 == 1 && count3 == 0) {
        bet *= SaT;    //三同
        cout << "三同 " << endl;
        return;
    } else if (count1 == 1 && count2 == 1 && count3 == 1) {
        bet *= SaT;
        cout << "三同" << endl;
        return;
    }
    if (count1 == 2 && count2 == 0 && count3 == 0) {
        bet *= LD;    //两对
        cout << "两对" << endl;
        return;
    } else if (count1 == 1 && count2 == 1 && count3 == 0) {
        bet *= LD;
        cout << "两对" << endl;
        return;
    } else if (count1 == 1 && count2 == 0 && count3 == 1) {
        bet *= LD;
        cout << "两对" << endl;
        return;
    } else if (count1 == 0 && count2 == 2 && count3 == 0) {
        bet *= LD;
        cout << "两对" << endl;
        return;
    } else if (count1 == 0 && count2 == 1 && count3 == 1) {
        bet *= LD;
        cout << "两对" << endl;
        return;
    } else if (count1 == 0 && count2 == 0 && count3 == 2) {
        bet *= LD;
        cout << "两对" << endl;
        return;
    }
    if (count1 == 1 && count2 == 0 && count3 == 0) {
        temp3 = 1;   //一对
    } else if (count1 == 0 && count2 == 1 && count3 == 0) {
        temp3 = 1;
    } else if (count1 == 0 && count2 == 0 && count3 == 1) {
        temp3 = 1;
    }
    if (temp3 == 1) {
        for (int m = 0; m < 5; m++) {
            for (int p = 0; p < 5; p++) {
                if (p != m) {
                    if (Card_int[m] - Card_int[p] == 13
                            || Card_int[m] - Card_int[p] == 26
                            || Card_int[m] - Card_int[p] == 39) {
                        if (Card_int[p] > 9 && Card_int[p] < 14 ) {
                            bet *= YD;
                            cout << "一对J以上" << endl;
                            return;
                        } else if (Card_int[p] > 22 && Card_int[p] < 27) {
                            bet *= YD;
                            cout << "一对J以上" << endl;
                            return;
                        } else if (Card_int[p] > 35 && Card_int[p] < 40) {
                            bet *= YD;
                            cout << "一对J以上" << endl;
                            return;
                        } else if (Card_int[p] > 48) {
                            bet *= YD;    //J以上
                            cout << "一对J以上" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "没有中奖" << endl;
    bet = 0;//没有中奖
    return;
}


void SwitchCard(const int Card_i, char (&Card_c)[3]) { //不是Card_int[5]&Card_char[5]
    switch (Card_i) {
    case 1:
        sprintf(Card_c, "▲2");
        break; //  ▲-黑桃  ◆-方片  ●-红桃  ★-梅花
    case 2:
        sprintf(Card_c, "▲3");
        break;
    case 3:
        sprintf(Card_c, "▲4");
        break;
    case 4:
        sprintf(Card_c, "▲5");
        break;
    case 5:
        sprintf(Card_c, "▲6");
        break;
    case 6:
        sprintf(Card_c, "▲7");
        break;
    case 7:
        sprintf(Card_c, "▲8");
        break;
    case 8:
        sprintf(Card_c, "▲9");
        break;
    case 9:
        sprintf(Card_c, "▲0");
        break;
    case 10:
        sprintf(Card_c, "▲J");
        break;
    case 11:
        sprintf(Card_c, "▲Q");
        break;
    case 12:
        sprintf(Card_c, "▲K");
        break;
    case 13:
        sprintf(Card_c, "▲A");
        break;
    case 14:
        sprintf(Card_c, "◆2");
        break;
    case 15:
        sprintf(Card_c, "◆3");
        break;
    case 16:
        sprintf(Card_c, "◆4");
        break;
    case 17:
        sprintf(Card_c, "◆5");
        break;
    case 18:
        sprintf(Card_c, "◆6");
        break;
    case 19:
        sprintf(Card_c, "◆7");
        break;
    case 20:
        sprintf(Card_c, "◆8");
        break;
    case 21:
        sprintf(Card_c, "◆9");
        break;
    case 22:
        sprintf(Card_c, "◆0");
        break;
    case 23:
        sprintf(Card_c, "◆J");
        break;
    case 24:
        sprintf(Card_c, "◆Q");
        break;
    case 25:
        sprintf(Card_c, "◆K");
        break;
    case 26:
        sprintf(Card_c, "◆A");
        break;
    case 27:
        sprintf(Card_c, "●2");
        break;
    case 28:
        sprintf(Card_c, "●3");
        break;
    case 29:
        sprintf(Card_c, "●4");
        break;
    case 30:
        sprintf(Card_c, "●5");
        break;
    case 31:
        sprintf(Card_c, "●6");
        break;
    case 32:
        sprintf(Card_c, "●7");
        break;
    case 33:
        sprintf(Card_c, "●8");
        break;
    case 34:
        sprintf(Card_c, "●9");
        break;
    case 35:
        sprintf(Card_c, "●0");
        break;
    case 36:
        sprintf(Card_c, "●J");
        break;
    case 37:
        sprintf(Card_c, "●Q");
        break;
    case 38:
        sprintf(Card_c, "●K");
        break;
    case 39:
        sprintf(Card_c, "●A");
        break;
    case 40:
        sprintf(Card_c, "★2");
        break;
    case 41:
        sprintf(Card_c, "★3");
        break;
    case 42:
        sprintf(Card_c, "★4");
        break;
    case 43:
        sprintf(Card_c, "★5");
        break;
    case 44:
        sprintf(Card_c, "★6");
        break;
    case 45:
        sprintf(Card_c, "★7");
        break;
    case 46:
        sprintf(Card_c, "★8");
        break;
    case 47:
        sprintf(Card_c, "★9");
        break;
    case 48:
        sprintf(Card_c, "★0");
        break;
    case 49:
        sprintf(Card_c, "★J");
        break;
    case 50:
        sprintf(Card_c, "★Q");
        break;
    case 51:
        sprintf(Card_c, "★K");
        break;
    case 52:
        sprintf(Card_c, "★A");
        break; //事先将0转换为52,否则GetPrize出错
    default:
        sprintf(Card_c, "err");
    }
}


void LoadCard(int (&Card_int)[5], char (&Card_char)[5][3]) {
    int temp;
    for (int j = 0; j < 5; j++) {
        Card_int[j] = 53;
    }
    for (int i = 0; i < 5; i++) {
        srand(time(0) + rand() / 5);
        temp = rand() % 52;
        if (temp == 0)temp = 52;
        for (int k = 0; k < 5; k++) {
            if (temp == Card_int[k]) {
                k = -1;
                srand(time(0) + rand() / 7);
                temp = rand() % 52;
                if (temp == 0)temp = 52;
            }
        }
        Card_int[i] = temp;
        cout << ". "; //在'系统洗牌中,请稍候'后加'.'号
        SwitchCard(Card_int[i], Card_char[i]);
    }
}

void InPuts_to_InPut(char (&InPuts)[5], int (&InPut)[6]) {
    int len = strlen(InPuts);
    for (int n = 0; n < len; n++) {
        switch (InPuts[n]) {
        case '0':
            InPut[n] = 0;
            break;
        case '1':
            InPut[n] = 1;
            break;
        case '2':
            InPut[n] = 2;
            break;
        case '3':
            InPut[n] = 3;
            break;
        case '4':
            InPut[n] = 4;
            break;
        case '5':
            InPut[n] = 5;
            break;
        }
//	InPut[n] = atoi((&InPuts)[n]); //原方案,结果InPut[n]变成乱码,不知为什么
    }
    InPut[len] = '\0';
}

void ChangeHandCard(int (&Card_int)[5], char (&Card_char)[5][3], char (&InPuts)[5], int (&InPut)[6], int (&temp)[5]) {
    int len = strlen(InPuts);
    InPuts_to_InPut(InPuts, InPut);
    for (int i = 0; i < len; i++) {
        int num = InPut[i] - 1; //在循环中的变量定义在第二次执行时自动成为赋值!
        srand(time(0) + rand() / 13);
        temp[num] = rand() % 52;
        if (temp[num] == 0)temp[num] = 52;
        for (int j = 0; j < 5; j++) {
            if (temp[num] == Card_int[j]) {
                i--;    //如果temp值重复,i退一位,重取temp
                break;
            }
        }
        //ShowChangCard(Card_int[num],temp[num]);//逐张显示换牌
        Card_int[num] = temp[num];
    }
    for (int k = 0; k < 5; k++) {
        SwitchCard(Card_int[k], Card_char[k]);
    }
}
