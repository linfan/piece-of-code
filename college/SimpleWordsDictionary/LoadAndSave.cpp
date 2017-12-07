#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <windows.h> //为了使用清屏功能
#include "WordNode.h"
#define MAX 21

class LinkList;
void Fill(char(&me)[MAX]);
void ShowAllNode(LinkList &);
void ShowMain();
void AboutMe();
int Operator(LinkList &);
void Save(LinkList &);

/*----------------全局函数--------------------*/


//词库载入
void Load(LinkList &words) {
    char ew[MAX], cw[MAX], nt[MAX];
    cout << "正在载入词库.." << endl;
    fstream FileData1;
    FileData1.open("data.dat", ios::in);
    for (int x = 1; x == 1; x++) {
        if (!FileData1) {
            FileData1.open("data.dat", ios::out);
            FileData1.close();
            cout << "未发现此库文件，已新建词库。" << endl;
        } else {
            char getl[6], YorN;
            FileData1.getline(getl, 7);
            cout << getl;
            if (strcmp(getl, "CHECK!") != 0) {
                cout << "词库文件可能已经损坏，继续读入(Y/N)? ";
                cin >> YorN;
                if (YorN == 'N' || YorN == 'n') {
                    break;
                }
            } else {
                FileData1.seekg(2, ios::cur);
                while (!FileData1.eof()) {
                    FileData1.setf(ios::skipws);
                    FileData1.getline((words.GetCurr())->eword, MAX);
                    FileData1.getline((words.GetCurr())->cword, MAX);
                    FileData1.getline((words.GetCurr())->note, MAX);
                    sprintf(ew, "                     ");
                    sprintf(cw, "                     ");
                    sprintf(nt, "                     ");
                    words.Intert(ew, cw, nt); //将会多出一条空记录
                    FileData1.seekg(4, ios::cur); //两个#，两个\r
                } //从文件读入一个20位的字符串，实际需要读21位!! 原因目前未知。
                words.Drop(); //删除多出的空记录

            }
        }
        FileData1.close();
        cout << "词库载入完成。" << '\n' << "当前词库共有" << words.CountNode()
             - 1 << "条记录" << endl; //说不清为什么要-1，但不减结果就是不对。
    }
    //////////////////////////////////
    words.ModifyCurr(words.GetTail());
    words.Drop(); /*词库载完后多出一条空记录,原因尚未查明,
    此处将其Dorp掉,程序才能正常运行。*/
    //////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowNew() { //由于未对DOS行距与屏宽加以考虑，辛苦设计的新版界面实际不有具可用性。
    cout << "                                              MMMMMM                                  " << endl;
    cout << "                                          MMMM      MMMMMM                            " << endl;
    cout << "  欢迎使用 简易语言翻译程序         MMMMMM              MMMM                          " << endl;
    cout << "                                  MMMM                    MMMM                        " << endl;
    cout << "  Designed By: LinFan           MMMM                        MMMM        MMM M         " << endl;
    cout << "  version: 1.0.1            MMMM             SORT 或 sort      MM    MM       MM      " << endl;
    cout << "                            MM             给所有记录排序      MM  M            MM    " << endl;
    cout << "          MMMM          MMMM                                    MM                MM  " << endl;
    cout << "      MMM      MMM  MMMMMM                                      MM   SHOW 或 show  MM " << endl;
    cout << "    MMMM          MMMM                 ALLWORDS 或 allwords     MM     显示主界面   M " << endl;
    cout << "  MM                                           显示所有词条     MM                  M " << endl;
    cout << "              -- 可用指令 --                                    MM      MMMM  MM   M  " << endl;
    cout << "MM                                                              MM  MMMM        MM    " << endl;
    cout << "MM      COUNT 或 count   当前已有记录数                         MMMM              MM  " << endl;
    cout << "MM                                                     MMMM   MMMM     OLD 或 old  MM " << endl;
    cout << "MM        ADD 或 add      添加一条记录              MM      MMMM     使用旧版界面   MM" << endl;
    cout << "MM                                                MM          MM                    MM" << endl;
    cout << "MM     MODIFY 或 modify   修改记录内容            MM      MMMM                      MM" << endl;
    cout << "                                                  MM    MMMM    SAVE 或 save        MM" << endl;
    cout << "  MM      DROP 或 drop     删除一条记录           MM  MMMM      保存修改          MM  " << endl;
    cout << "  MMMM                                            MMMMMM                        MM    " << endl;
    cout << "    MMMM    SEARCH 或 search   查找已有记录     MMMMMM                        MMMM    " << endl;
    cout << "      MMMM                                    MMMMMMMM    EXIT 或 exit    MMMMMM      " << endl;
    cout << "        MMMM      RELOAD 或 reload        MMMMMM    MMMM  退出程序      MMMM          " << endl;
    cout << "          MM      重载词库            MMMM            MM              MMMM            " << endl;
    cout << "            MMMM                  MMMMMM                            MM                " << endl;
    cout << "              MM              MMMMMM                    MMMM      M                   " << endl;
    cout << "               MM           MM                            MMM  MMM                    " << endl;
    cout << "                 MMMMMMMMMMM                                 MM                       " << endl;
    cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//显示主界面
void ShowMain() {
    cout << "                                                                    " << endl;
    cout << "                                            ++ +++  ++++            " << endl;
    cout << "   -------------------------           ++++              +++        " << endl;
    cout << "   欢迎使用 简易语言翻译程序        +++                     +++     " << endl;
    cout << "   -------------------------     +++    -- 程序版本V1.0.2 --   ++   " << endl;
    cout << "                              +++     ________________________   ++ " << endl;
    cout << "            ++++           +++                                   ++ " << endl;
    cout << "        +++    +++     ++++                                      ++ " << endl;
    cout << "     +++          ++++                                           ++ " << endl;
    cout << "   ++                                                            ++ " << endl;
    cout << " ++     <操作说明>:  搜索单词   -   直接输入单词回车即可         +  " << endl;
    cout << " ++                                                             +   " << endl;
    cout << " ++     清屏并显示主界面   -   输入#S#或#s#回车               ++    " << endl;
    cout << " ++                                                        +++      " << endl;
    cout << "  ++     进入后台管理   -   输入#M#或#m#回车            +++      _  " << endl;
    cout << "   +++                                               +++       _|   " << endl;
    cout << "     +++     关于本程序   -   输入#A#或#a#回车     ++         _|    " << endl;
    cout << "       +++                                          +++      _|     " << endl;
    cout << "         +++    退出程序   -    输入#Q#或#q#回车   +++       |_   _ " << endl;
    cout << "           ++                                         ++     _|__|  " << endl;
    cout << "             +++                                  ++++      _| |    " << endl;
    cout << "               ++              +++ +++++ ++++ +++           |       " << endl;
    cout << "                 ++        ++++                          o^^o       " << endl;
    cout << "                    + +++                 [ Designed By: LinFan ]   " << endl;
    cout << endl;
}
//后台管理界面
void Manage(LinkList &words) {
    cout << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  ///////////////////欢迎进入 简易语言翻译后台管理程序///////////////////" << endl;
    cout << " -                                                       version: 1.0.2  -" << endl;
    cout << " -                                                  Designed By: LinFan  -" << endl;
    cout << "  ///////////////////////////////////////////////////////////////////////" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /                 ---- 请选择您需要的操作  o^^o ----                  /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /            可用指令                        说明                     /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /         COUNT 或 count                  当前已有记录数              /" << endl;
    cout << "  /           ADD 或 add                     添加一条记录               /" << endl;
    cout << "  /          DROP 或 drop                    删除一条记录               /" << endl;
    cout << "  /        MODIFY 或 modify                  修改记录内容               /" << endl;
    cout << "  /        SEARCH 或 search                  查找已有记录               /" << endl;
    cout << "  /      ALLWORDS 或 allwords                显示所有词条               /" << endl;
    cout << "  /          SORT 或 sort                   给所有记录排序              /" << endl;
    cout << "  /        RELOAD 或 reload                  重新载入词库               /" << endl;
    cout << "  /          SAVE 或 save                      保存修改                 /" << endl;
    cout << "  /          EXIT 或 exit                    退出后台管理               /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  /                                                                     /" << endl;
    cout << "  ///////////////////////////////////////////////////////////////////////" << endl;
    cout << "  /                                                                     /" << endl;
    cout << endl;

    Operator(words);
}


//前台控制操作，临时
void FrontUse(LinkList &words) {
    char ew[MAX];
    for (int x = 1; x == 1;) {
        cout << "输入查找的词条: ";
        cin >> ew;
        if (strcmp(ew, "#M#") == 0 || strcmp(ew, "#m#") == 0) {
            system("cls");
            Manage(words);
        } else if (strcmp(ew, "#S#") == 0 || strcmp(ew, "#s#") == 0) {
            system("cls");
            ShowMain();
            FrontUse(words);
        } else if (strcmp(ew, "#A#") == 0 || strcmp(ew, "#a#") == 0) {
            AboutMe(); /*system("cls");Abouts();*/
        } else if (strcmp(ew, "#Q#") == 0 || strcmp(ew, "#q#") == 0) {
            cout << "程序已正常退出,谢谢您的使用!" << endl;
            break;
        } else {
            Fill(ew);
            words.ModifyCurr(words.Search(ew));
            if (words.GetCurr() != NULL) {
                words.ShowNode();
                cout << endl;
            } else {
                cout << "未查找到'" << ew << "'词条" << endl;
            }
            words.ModifyCurr(words.GetHead());
        }
        cout << endl;
    }
}

//后台管理操作
int Operator(LinkList &words) {
    char command[MAX], ew[MAX], cw[MAX], nt[MAX];
    char YorN;
    for (int x = 1; x == 1;) {
        cout << "输入指令: ";
        cin >> command;

        ////////////////// -- 新的操作指令判断 用于V1.0.1以后的版本 --

        if (strcmp(command, "COUNT") == 0 || strcmp(command, "count") == 0)
            //当前已有记录数
        {
            cout << "当前词库词条数: " << words.CountNode() << endl;
        } else if (strcmp(command, "ADD") == 0 || strcmp(command, "add") == 0)
            //添加一条记录
        {
            cout << "输入新的词条: ";
            cin >> ew;
            cout << "输入词条的中文解释: ";
            cin >> cw;
            cout << "输入词条的备注内容: ";
            cin >> nt;
            words.Intert(ew, cw, nt);
            cout << "成功添加了新的词条'" << ew << "'" << endl;
        } else if (strcmp(command, "DROP") == 0 || strcmp(command, "drop") == 0)
            //删除一条记录
        {
            cout << "输入需要删除的词条: ";
            cin >> ew;
            Fill(ew);
            words.ModifyCurr(words.Search(ew));
            if (words.GetCurr() != NULL) {
                words.Drop();
                cout << "词条'" << ew << "'删除成功!" << endl;
            } else {
                cout << "无此词条!" << endl;
            }
        } else if (strcmp(command, "MODIFY") == 0 || strcmp(command, "modify") == 0)
            //修改记录内容
        {
            cout << "输入需要修改的词条: ";
            cin >> ew;
            Fill(ew);
            words.ModifyCurr(words.Search(ew));
            if (words.GetCurr() != NULL) {
                cout << "修改单词拼写(Y/N)?";
                cin >> YorN;
                if (YorN == 'Y' || YorN == 'y') {
                    cout << "输入新的单词拼写: ";
                    cin >> ew;
                }
                cout << "修改中文解释(Y/N)?";
                cin >> YorN;

                if (YorN == 'Y' || YorN == 'y') {
                    cout << "输入新的中文解释: ";
                    cin >> cw;
                } else {
                    strcpy(cw, words.GetCurr()->cword);
                }

                cout << "修改备注内容(Y/N)?";
                cin >> YorN;
                if (YorN == 'Y' || YorN == 'y') {
                    cout << "输入新的备注内容: ";
                    cin >> nt;
                } else {
                    strcpy(nt, words.GetCurr()->note);
                }

                words.Drop();
                words.Intert(ew, cw, nt);
                cout << "成功修改了词条'" << ew << "'" << endl;
            } else {
                cout << "无此词条!" << endl;
            }
        } else if (strcmp(command, "SEARCH") == 0 || strcmp(command, "search") == 0)
            //查找已有记录
        {
            cout << "输入查找的词条: ";
            cin >> ew;
            Fill(ew);
            words.ModifyCurr(words.Search(ew));
            if (words.GetCurr() != NULL) {
                words.ShowNode();
                cout << endl;
            } else {
                cout << "未查找到'" << ew << "'词条，是否现在添加(Y/N)? ";
                cin >> YorN;
                if (YorN == 'Y' || YorN == 'y') {
                    cout << "输入词条的中文解释: ";
                    cin >> cw;
                    cout << "输入词条的备注内容: ";
                    cin >> nt;
                    words.Intert(ew, cw, nt);
                    cout << "成功添加了新的词条'" << ew << "'" << endl;
                }
            }

            words.ModifyCurr(words.GetHead());
            //不能让Curr指针挂空，否则下一次使用将报错
        } else if (strcmp(command, "SHOW") == 0 || strcmp(command, "show") == 0)
            //显示主界面
        {
            cout << endl;
        } //在V1.0.2版本以后已取消此操作
        else if (strcmp(command, "ALLWORDS") == 0 || strcmp(command, "allwords") ==
                 0)
            //显示所有词条
        {
            ShowAllNode(words);
            cout << endl;
        } else if (strcmp(command, "SORT") == 0 || strcmp(command, "sort") == 0)
            //给所有记录排序
        {
            cout << "词库排序中.." << endl;
            words.Sort(words);
            cout << "排序完成。" << endl;
        } else if (strcmp(command, "SAVE") == 0 || strcmp(command, "save") == 0)
            //保存修改
        {
            cout << "词库更新中，请稍候.." << endl;
            Save(words);
            cout << "词库更新完成。" << endl;
        } else if (strcmp(command, "EXIT") == 0 || strcmp(command, "exit") == 0)
            //退出程序
        {
            cout << "退出前保存修改吗(Y/N)? ";
            cin >> YorN;
            if (YorN == 'Y' || YorN == 'y') {
                cout << "词库保存中.." << endl;
                Save(words);
                cout << "词库保存完成。" << endl;
            }
            //words.FreeAllNode(words);<-这里注释掉!
            cout << endl;
            system("cls"); //清屏，包含于windows.h
            ShowMain();
            return 0;
        } else if (strcmp(command, "RELOAD") == 0 || strcmp(command, "reload") == 0)
            //重新载入词库
        {
            cout << "重载词库后，当前所有为保存的修改将全部丢失，" << '\n' <<
                 "确定执行(Y/N)? ";
            cin >> YorN;
            if (YorN == 'Y' || YorN == 'y') {
                words.FreeAllNode(words);
                Load(words);
            }
        } else if (strcmp(command, "NEWMAIN") == 0 || strcmp(command, "newmain") == 0)
            //隐藏指令-使用新界面
        {
            system("cls");
            ShowNew();
        } else
            //错误的指令
        {
            cout << "错误的指令!" << endl;
        }
        cout << endl;
    }
    return 1;
}

//输出关于本软件
void AboutMe() {
    system("cls");
    cout << "                                                        " << endl;
    cout << "#                                                      #" << endl;
    cout << "#  -- 简易语言翻译程序 V1.0.2 --                       #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  本程序使用C++语言编写,编译环境:VC++6.0              #" << endl;
    cout << "#  程序设计: LinFan                   #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  版本历史:                                           #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  V1.0.0版 程序最初的版本,提供了词条的载入、输出,     #" << endl;
    cout << "#           和动态增减、搜索等基本操作功能。           #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  V1.0.1版 [1]修正了modify操作的一段代码错误,真正     #" << endl;
    cout << "#           实现了词条的修改。                         #" << endl;
    cout << "#           [2]重写了操作控制的函数,减少输入错误的     #" << endl;
    cout << "#           发生。                                     #" << endl;
    cout << "#           [3]对主界面设计进行修改,并增加了一个       #" << endl;
    cout << "#           reload操作。                               #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  V1.0.2版 [1]再次修正modify操作,可以单独修改词条     #" << endl;
    cout << "#           的局部内容。                               #" << endl;
    cout << "#           [2]修正了search操作得到错误结果的BUG。     #" << endl;
    cout << "#           [3]重新修改程序界面,从而实现了前台操作     #" << endl;
    cout << "#           与后台管理的界面分离。                     #" << endl;
    cout << "#                                                      #" << endl;
    cout << "#  V1.0.3版 [1]修正了从管理界面退回用户界面时会发生    #" << endl;
    cout << "#           词典丢失的BUG。                            #" << endl;
    cout << "#           [2]重写了搜索函数，使搜词更加高效。        #" << endl;
    cout << "#           [3]重新对源文件进行了规范排版。            #" << endl;
    cout << "#                                                      #" << endl;
    system("pause");
    ShowMain();
}

//保存词库
void Save(LinkList &words) {
    fstream FileData2;
    FileData2.open("data.dat", ios::out | ios::trunc);
    char checkme[7];
    sprintf(checkme, "CHECK!");
    FileData2.write(checkme, 6);
    int n = words.CountNode();
    words.ModifyCurr(words.GetHead());
    for (int i = 0; i < n; i++) {
        FileData2.put('\r');
        FileData2.put('\r');
        FileData2.write((words.GetCurr())->eword, MAX - 1);
        FileData2.write((words.GetCurr())->cword, MAX - 1);
        FileData2.write((words.GetCurr())->note, MAX - 1);
        FileData2.put('#');
        FileData2.put('#');
        if (i != n - 1)
            words.ModifyCurr((words.GetCurr())->GetNext());
    }
    FileData2.close();
}


//输出所有词条
void ShowAllNode(LinkList &words) /*这里如果用LinkList *words就会报错:
words must have class/struct/union type ;
和cannot convert parameter 1 from 'class LinkList' to 'class LinkList *'。
因为*words是指针，不能用words.xxx方法，
所以必须把函数里的words.xxx都改为words->xxx。
在实际操作时就应当注意这种区别!!
 */
{
    int F = words.CountNode();
    words.ModifyCurr(words.GetHead());
    for (int r = 1; r < F + 1; r++) {
        cout << "第" << r << "条:" << endl;
        words.ShowNode();
        if (r != F) {
            words.ModifyCurr((words.GetCurr())->GetNext());
        }
    }
    cout << endl;
}

//填满空位
void Fill(char(&me)[MAX]) {
    int i = 0;
    while (me[i] >= 'a' && me[i] <= 'z') {
        i++;
    }
    while (i < MAX) {
        me[i] = ' ';
        i++;
    }
    me[MAX - 1] = '\0';
} /*字符为空即==0;
字符串为空即[0]=='\0';
或strlen(串)==0 ; */

//比较两个字符串大小
int Compare(const char left[], const char right[]) {
    for (int i = 0; i < MAX - 1; i++) {
        if (left[i] - right[i] != 0)
            return (left[i] - right[i]);
    }
    return 0;
}
