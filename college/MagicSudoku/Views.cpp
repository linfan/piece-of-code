#include <iostream.h>
#include <stdlib.h>

int n = -1;
int m = 0;
int IsAnswer = 0;

//返回table中的下一个数
char Next(int (&table)[9][9][10]) {
    n++;
    if (n == 9) {
        n = 0;
        m++;
    }

    switch (table[m][n][0]) {
    case 0:
        return ' ';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    }

}

//主界面
const void MainView(int (&table)[9][9][10]) {
    cout << "                                                                " << endl;
    cout << "      ▼                                □                      " << endl;
    cout << " ╭────    ○    │      ◇│◆          ─╮    ▲  V1.0.0 " << endl;
    cout << " │ ┼ ┼    ↘    ─┼─    ─┼─ ○         │    │         " << endl;
    cout << " │ ☆ ☆      ●  ─┼─    ◆│◇↙─-┼     ↗╭─┼─╮     " << endl;
    cout << " │ ╱┬┐     │   ╱        ╱╮  │ ╱    ↖││  │  │     " << endl;
    cout << " │ ├┼┤      ↗ │  △    ┼-┼─ ╳        ┼╰─┼─╯     " << endl;
    cout << "    └┴┘     ○  └─╯     ╲╯  │ ╲    ◇│  ─┴─◇     " << endl;
    cout << " ╰─┘└◇╯          ★     ◎↘  │  │   ╰╯        │     " << endl;
    cout << "                                                            ▽  " << endl;
    if (IsAnswer == 0) {
        cout << "   ☆ 你相信魔法吗？不信？那就让你看一看魔法数独的厉害 ☆       " << endl;
    } else {
        cout << "   ☆   魔法完成喽 ^ǒ^      哈哈～  我的魔法天下无敌!  ☆       " << endl;
    }
    cout << "                                                                " << endl;
    cout << "          ┏━┯━┯━┳━┯━┯━┳━┯━┯━┓                " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃ ☆             " << endl;
    cout << "   ◇     ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨                " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃         ◎     " << endl;
    cout << "          ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨                " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃                " << endl;
    cout << "      ☆  ┣━┿━┿━╋━┿━┿━╋━┿━┿━┫                " << endl;
    cout << "    ★    ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃    ◇  ●      " << endl;
    cout << "          ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨                " << endl;
    cout << "  ▽      ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃                " << endl;
    cout << "          ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨                " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃     ★         " << endl;
    cout << "        ○┣━┿━┿━╋━┿━┿━╋━┿━┿━┫  △            " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃                " << endl;
    cout << " ☆       ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨           ◆   " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃                " << endl;
    cout << "     ●   ┠─┼─┼─╂─┼─┼─╂─┼─┼─┨        △      " << endl;
    cout << "          ┃" << Next(table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(
             table) << " │" << Next(table) << " │" << Next(table) << " ┃" << Next(table) << " │" << Next(table) << " │" << Next(
             table) << " ┃                " << endl;
    cout << "          ┗━┷━┷━┻━┷━┷━┻━┷━┷━┛□              " << endl;
    cout << "                                                                " << endl;
    cout << "         ★ 程序算法设计:  LinFan ★             \n" << endl;
}


const void GiveAnswer(int (&table)[9][9][10]) {
    n = -1;
    m = 0;
    IsAnswer = 1;
    MainView(table);
}


const void NoAnswer() {
    cout << "                                                                " << endl;
    cout << "      ▼                                □                      " << endl;
    cout << " ╭────    ○    │      ◇│◆          ─╮    ▲  V1.0.0 " << endl;
    cout << " │ ┼ ┼    ↘    ─┼─    ─┼─ ○         │    │         " << endl;
    cout << " │ ☆ ☆      ●  ─┼─    ◆│◇↙─-┼     ↗╭─┼─╮     " << endl;
    cout << " │ ╱┬┐     │   ╱        ╱╮  │ ╱    ↖││  │  │     " << endl;
    cout << " │ ├┼┤      ↗ │  △    ┼-┼─ ╳        ┼╰─┼─╯     " << endl;
    cout << "    └┴┘     ○  └─╯     ╲╯  │ ╲    ◇│  ─┴─◇     " << endl;
    cout << " ╰─┘└◇╯          ★     ◎↘  │  │   ╰╯        │     " << endl;
    cout << "                                                                " << endl;
    cout << "    ☆  唉唉... 魔法失败了   @.@ 好像是..原料出了问题 ？  ☆    " << endl;
    cout << "\n\n                                                                " << endl;
    cout << " 　　　★★★★★★★★★　　　　　　★★★★　★★★★★★　   " << endl;
    cout << " 　　　　　　★　　　　　　　　　　★　　★　　　★　　　★　   " << endl;
    cout << " 　　　　　　★　　　　　　　　　★　　★　　　　★　　　★　   " << endl;
    cout << " 　　　　　　★　　　　　　　　　　★★★★★　★　　★★　　   " << endl;
    cout << " 　　★★★★★★★★★★★★　　　★　★　★　　★　★　　　   " << endl;
    cout << " 　　　　　　★　★　　　　　　　　★★★★★　　★　★　　　   " << endl;
    cout << " 　　　　　　★　★　　　　　　　　★　★　★　★★★★★★　   " << endl;
    cout << " 　　　　　　★　★　　　　　　　　★★★★★★★　　★　　　   " << endl;
    cout << " 　　　　　★　　★　　　　　　　　★　★　★　　　　★　　　   " << endl;
    cout << " 　　　　★★　　★　　　　★　　　★　★　★★★★★★★★★   " << endl;
    cout << " 　　　★★　　　★　　　★★　　★★　★　★　　　　★　　　   " << endl;
    cout << " 　★★　　　　　　★★★★　　　★　　　　★　　　　★　　　   " << endl;
    cout << " 　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n" << endl;
}
