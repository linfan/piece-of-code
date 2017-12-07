#include <iostream.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <stdlib.h>

void SwitchCard(const int Card_i, char (&Card_c)[3]);

void Welcome(char Puke[]) {
    cout << "                                                                    " << endl;
    cout << "                 — 休闲益智游戏 幸运扑克 —                        " << endl;
    _sleep(200);
    cout << "                                                                    " << endl;
    _sleep(200);
    cout << "  ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★    " << endl;
    _sleep(200);
    cout << "                                 ☆                                 " << endl;
    _sleep(200);
    cout << "       ☆                                             ☆            " << endl;
    _sleep(200);
    cout << " 　 —┼—     ●  -—  ☆   │   │    ——┼——   LuckPock       " << endl;
    _sleep(200);
    cout << "  —●┴○—   -┐-┬—     -○-  │  ☆┌—┴—┐   V1.0.1         " << endl;
    _sleep(200);
    cout << " ☆ —┬—     ／ ◎         │   ◎-   └┬—┬┘☆                " << endl;
    _sleep(200);
    cout << "  ——┼——   ＼ └—◎     ／   │      │  │○       ☆         " << endl;
    _sleep(200);
    cout << "      │       ○———-   ●│   │☆   ●   └┘                  " << endl;
    _sleep(200);
    cout << "           ☆                                                       " << endl;
    _sleep(200);
    cout << "                                            ☆     ╭————╮     " << endl;
    _sleep(200);
    cout << "  ¤ -幸运扑克玩法-       ☆                       │" << Puke << "     │     " << endl;
    _sleep(200);
    cout << "                                                   │        │     " << endl;
    _sleep(200);
    cout << "    游戏开始后由系统随机发5张牌,玩家有一次选则  ☆ │  祝您  │     " << endl;
    _sleep(200);
    cout << "    换牌的机会,选中的牌随机更换一次,根据结果对     │  中奖  │     " << endl;
    _sleep(200);
    cout << "☆  照奖级表赢得相应奖项。若中奖,还可进入'猜大     │        │     " << endl;
    _sleep(200);
    cout << "    小'游戏,以获得奖分翻倍的机会...    ¤          │     " << Puke << "│☆   " << endl;
    _sleep(200);
    cout << "                                                   ╰————╯     " << endl;
    _sleep(200);
    cout << "                                                                    " << endl;
    _sleep(200);
    cout << "  ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★ ● ◆ ▲ ★    " << endl;
    _sleep(200);
}

const void GameView(char (&Card_char)[5][3], const char (&name)[10], const int Score, const int goal, const int bet) {
    cout << "\n\n_____________________LuckPock V1.0.1__________________________" << endl;
    cout << "\n玩家: ";
    cout.width(10);
    cout.setf(ios::left);
    cout << name;
    cout << "               - 欢迎您参与 幸 运 扑 克 游戏 -" << endl;
    cout << "目标积分: ";
    cout.width(4);
    cout.setf(ios::left);
    cout << goal;
    cout << " 点              - 程序设计: LinFan -" << endl;
    cout << "\n当前积分: ";
    cout.width(4);
    cout.setf(ios::left);
    cout << Score;
    cout << " 点                        本轮下注额: ";
    cout.width(3);
    cout.setf(ios::left);
    cout << bet << " 点" << endl;
    cout << "\n     ☆☆☆☆☆☆☆☆    [你的手牌]    ☆☆☆☆☆☆☆☆" << endl;
    cout << "\n ╭———╮  ╭———╮  ╭———╮  ╭———╮  ╭———╮" << endl;
    cout << " │";
    cout.write(Card_char[0], 3); //系统BUG,Card_char[0]中实际不止3位
    cout << "   │  │";
    cout.write(Card_char[1], 3);
    cout << "   │  │";
    cout.write(Card_char[2], 3);
    cout << "   │  │";
    cout.write(Card_char[3], 3);
    cout << "   │  │";
    cout << Card_char[4] << "   │" << endl;
    cout << " │      │  │      │  │      │  │      │  │      │" << endl;
    cout << " │      │  │      │  │      │  │      │  │      │" << endl;
    cout << " │      │  │      │  │      │  │      │  │      │" << endl;
    cout << " │   ";
    cout.write(Card_char[0], 3);
    cout << "│  │   ";
    cout.write(Card_char[1], 3);
    cout << "│  │   ";
    cout.write(Card_char[2], 3);
    cout << "│  │   ";
    cout.write(Card_char[3], 3);
    cout << "│  │   " << Card_char[4] << "│" << endl;
    cout << " ╰———╯  ╰———╯  ╰———╯  ╰———╯  ╰———╯" << endl;
    cout << "\n\n     ☆◇☆◇☆◇☆◇☆              ☆◇☆◇☆◇☆◇☆" << endl;
    cout << endl;
}


void SmallorBig(int &bet) {
    int guessme_int, SorB;
    char guessme_char[3], myguess;

    cout << "\n- 参与扑克猜大小,获得积分无限翻倍的机会! -" << endl;
    cout << "\n只要猜中下面这张扑克牌的数值是小[A~6]或大[8~K]就可将收获的点数翻倍" << endl;
    cout << "但是如果猜错您将损矢本轮的全部赌注。" << endl;
    do {
        cout << "\n   ╭———╮" << endl;
        cout << "   │×?   │" << endl;
        cout << "   │      │" << endl;
        cout << "   │      │" << endl;
        cout << "   │      │" << endl;
        cout << "   │   ×?│   您现在能收获的积分为: " << bet << " 点" << endl;
        cout << "   ╰———╯   猜一猜[输入1为小,2为大,0为不参与]: ";
        cin >> myguess;
        srand(time(0));
        guessme_int = rand() % 52;
        if (guessme_int == 0) guessme_int = 52;
        SwitchCard(guessme_int, guessme_char);
        if (myguess == '1' || myguess == '2') {
            cout << "\n按下任意键公布扑克牌面" << endl;
        } else {
            cout << "\n按下任意键开始下一轮发牌" << endl;
        }
        system("pause");

        if (guessme_int == 6 || guessme_int == 19 || guessme_int == 32 || guessme_int == 45) {
            SorB = 0;
        } else if (guessme_int < 6) {
            SorB = 1;
        } else if (guessme_int < 19 && guessme_int > 13) {
            SorB = 1;
        } else if (guessme_int < 32 && guessme_int > 26) {
            SorB = 1;
        } else if (guessme_int < 45 && guessme_int > 39) {
            SorB = 1;
        } else {
            SorB = 2;
        }

        if (myguess == '1' || myguess == '2') {
            cout << "\n   ╭———╮" << endl;
            cout << "   │" << guessme_char << "   │" << endl;
            cout << "   │      │" << endl;
            cout << "   │      │" << endl;
            cout << "   │      │" << endl;
            cout << "   │   " << guessme_char << "│" << endl;
            cout << "   ╰———╯  牌面";
            if (SorB == 1) cout << "为小!" << endl;
            if (SorB == 2) cout << "为大!" << endl;
            if (SorB == 0) cout << "既非大也非小,收获积分不变。" << endl;

            switch (myguess) {
            case '1':
                if (SorB == 1) {
                    cout << "\n恭喜你,猜对啦! ^-^" << endl;
                    bet *= 2;
                }
                if (SorB == 2) {
                    cout << "\n很遗憾,祝君下次好运!" << endl;
                    bet = 0;
                }
                break;
            case '2':
                if (SorB == 2) {
                    cout << "\n恭喜你,猜对啦! ^-^" << endl;
                    bet *= 2;
                }
                if (SorB == 1) {
                    cout << "\n很遗憾,祝君下次好运!" << endl;
                    bet = 0;
                }
                break;
            }
            if (bet != 0)cout << "\n准备进入下一轮猜大小.." << endl;
        } else {
            break;
        }
    } while (bet != 0);

}
