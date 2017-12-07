#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <windows.h>
#include "WordNode.h"

class LinkList;
void Load(LinkList &);
void ShowMain();
void Save(LinkList &);
void ShowAllNode(LinkList &);
void FrontUse(LinkList &);

void main() {
    //程序初始化
    cout << "程序初始化中.." << endl;
    LinkList words;
    cout << "程序初始化完成。" << endl;
    //词库载入
    Load(words);
    //显示主界面
    ShowMain();
    //进入前台操作界面
    FrontUse(words);
    //结束
    system("pause");
}
