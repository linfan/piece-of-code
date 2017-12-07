#include <iostream.h>
#include <windows.h>
#include <fstream.h>
#include "LinkList.h" //若不包含也将报错" use of undefined type 'LinkList' "
#define SIZE 10
#define INFO 1 //显示读取的迷宫信息
#define PROCESS 1 //显示计算机思考过程
#define SHORTCUT 0 //显示到终点最短路径 
#define DEBUG 1 //运行错误时抛出错误

class LinkList;
class ListNode;

void ShowView() {
    cout << "  ++++++++++++++++++++++++++++++++++++++++++++++++++++++  " << endl;
    cout << "                                                          " << endl;
    cout << " -欢迎使用-             10                   10           " << endl;
    cout << "              10        10  10      10101010101010101010  " << endl;
    cout << "  +-+-+-+   1010    10  10  10      10                10  " << endl;
    cout << "   数 字            10  1010            101010101010      " << endl;
    cout << "  +-+-+-+         10101010101010        10        10      " << endl;
    cout << "            1010      1010              10        10      " << endl;
    cout << "              10    10  101010            10101010        " << endl;
    cout << "              10  1010  10  1010      1010101010101010    " << endl;
    cout << "              10  10    10            10            10    " << endl;
    cout << "              1010      10            10            10    " << endl;
    cout << "            10    10101010101010      1010101010101010    " << endl;
    cout << "                                                          " << endl;
    cout << " The Labyrinth Of Numbers                         o^ê^o   " << endl;
    cout << " [当前版本: V1.0.0]                   DesignedBy: LinFan  " << endl;
    cout << "                                                          " << endl;
    cout << "#  数字迷宫SIZE                      ";
    cout.width(3);
    cout.fill('0');
    cout << SIZE;
    cout << "×";
    cout.fill('0');
    cout.width(3);
    cout << SIZE;
    cout << "            #" << endl;
    cout << "#  显示读取的迷宫信息                "; //
    if (INFO == 1) {
        cout << "开启                #" << endl;
    } else {
        cout << "关闭                #" << endl;
    }
    cout << "#  显示计算机思考过程                "; //
    if (PROCESS == 1) {
        cout << "开启                #" << endl;
    } else {
        cout << "关闭                #" << endl;
    }
    cout << "#  显示到终点最短路径                "; //
    if (SHORTCUT == 1) {
        cout << "开启                #" << endl;
    } else {
        cout << "关闭                #" << endl;
    }
    cout << "#  运行错误时抛出错误                "; //
    if (DEBUG == 1) {
        cout << "开启                #" << endl;
    } else {
        cout << "关闭                #" << endl;
    }
    cout << "                                                          " << endl;
    system("pause");
}

//从文件中读入迷宫内容
int GetTable(int Table[][SIZE]) { //左值可省，右值不可省
    char temp;//如果用char *temp,指针在使用前必须被初始化(赋值):char *temp='\0';
    fstream Palace("Labyrinth.txt", ios::in);
    if (Palace.fail == 0) {
        cout << "迷宫文件载入错误!" << endl;
        return 0;
    }
    for (int i = 0; i < SIZE; i++) { //行
        for (int j = 0; j < SIZE; j++) { //列
            Palace.get(temp);
            switch (temp) {
            case '|':
            case '-':
            case '+':
                Table[i][j] = 1;
                break;
            case '*':
                Table[i][j] = 3;
                break;
            case '#':
                Table[i][j] = 2;
                break;
            default:
                Table[i][j] = 0;
            }
        }
        Palace.seekg(3, ios::cur); //跳过结尾';'和换行符[哪个占了两个字符?]
    }

//////////////////////////////////////////////////////////
    if (INFO == 1) {
        cout << "\n\n以下是读取的迷宫信息:\n" << endl;
        cout << '+';
        for (int e = 0; e < SIZE + 4; e++) {
            cout << '-';
        }
        cout << "+\n\n     ";
        for (int c = 0; c < SIZE; c++) {
            cout << (c + 1) % 10;   //行
        }
        cout << '\n' << "     ";
        for (int d = 0; d < SIZE; d++) {
            cout << '-';
        }
        cout << endl;
        for (int a = 0; a < SIZE; a++) {
            cout << "  " << (a + 1) % 10 << "| ";
            for (int b = 0; b < SIZE; b++) {
                cout << Table[a][b];   //列
            }
            cout << endl;
        }
        cout << "\n+";
        for (int f = 0; f < SIZE + 4; f++) {
            cout << '-';
        }
        cout << "+\n\n  ";
    }
///////////////////////////////////////////////////////////

    cout << "\n成功的载入了一个迷宫!" << endl;
    return 1;
}

//获得起点左坐标L
const int SearchBeginL(int (&Table)[SIZE][SIZE])
//不可以int (&Table),报错"cannot convert from 'int [60][60]' to 'const int [60][60]'"
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Table[i][j] == 3)return i;
        }
    }
    return 0;
}

//获得起点右坐标R
const int SearchBeginR(int (&Table)[SIZE][SIZE]) { //当数组为引用时,左右值均不可省
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Table[i][j] == 3)return j;
        }
    }
    return 0;
}

//计算当前位置有几个方向可使用
const int CountTheWays(int (&Table)[SIZE][SIZE], LinkList &recode, int L, int R) {
    int num = 0;
    if (L != 0 && Table[L - 1][R] != 0)num++;
    if (L != SIZE - 1 && Table[L + 1][R] != 0)num++;
    if (R != 0 && Table[L][R - 1] != 0)num++;
    if (R != SIZE - 1 && Table[L][R + 1] != 0)num++;
    if (recode.tail == recode.head) {
        return num;   //在起点
    }
    return num - 1;
}

//判断一个位置是否在来时走的路上
inline int PassBy(ListNode *cur, int L, int R) {
    do {
        if (L == cur->T_L && R == cur->T_R)return 1; //来时经过此点
        cur = cur->prov;
    } while (cur != 0); //do{..}while()后要加';'
    return 0;
}

//选一个方向
void ShooseAWay(int (&Table)[SIZE][SIZE], LinkList &recode, int L, int R) {
    static int times = 0;
    if (times == 0) {
        recode.cur = recode.tail->prov;
    } else {
        recode.cur = (recode.tail->prov)->prov;
    }
    if (recode.tail->prov == recode.head) {
        recode.cur = recode.tail;   //途经起点
    }
    times++;

    // -- 上方向 -- //
    if (L != 0 && Table[L - 1][R] != 0) { //不是在迷宫的边缘
        if ( PassBy(recode.cur, L - 1, R) == 0 ) { //新方向也不是来时走的方向
            recode.tail->T_L = L - 1;
            recode.tail->T_R = R;
            return;
        }
    }

    // -- 右方向 -- //
    if (R != SIZE - 1 && Table[L][R + 1] != 0) {
        if ( PassBy(recode.cur, L, R + 1) == 0 ) {
            recode.tail->T_L = L;
            recode.tail->T_R = R + 1;
            return;
        }
    }

    // -- 下方向 -- //
    if (L != SIZE - 1 && Table[L + 1][R] != 0) {
        if ( PassBy(recode.cur, L + 1, R) == 0 ) {
            recode.tail->T_L = L + 1;
            recode.tail->T_R = R;
            return;
        }
    }

    // -- 左方向 -- //
    if (R != 0 && Table[L][R - 1] != 0) {
        if ( PassBy(recode.cur, L, R - 1) == 0 ) {
            recode.tail->T_L = L;
            recode.tail->T_R = R - 1;
            return;
        }
    }

    /////////////////////////////////////////////////
    if (DEBUG == 1) {
        cout << "运行错误:无方向可选!" << endl;
    }
    return;
    /////////////////////////////////////////////////
}

//返回recode链中通过的方向
inline int TellTheDirection(ListNode &cur) {
    int temp1 = cur.T_L;
    int temp2 = (cur.next)->T_L;
    switch (temp1 - temp2) {
    case 1:
        return 1;
        break;//上
    case -1:
        return 2;
        break;//下
    }
    temp1 = cur.T_R;
    temp2 = (cur.next)->T_R;
    switch (temp1 - temp2) {
    case 1:
        return 3;
        break;//左
    case -1:
        return 4;
        break;//右
    ////////////////////////////////////////////////////
    default:
        if (DEBUG == 1) {
            cout << "\n运行错误:recode的记录不是任何方向!" << endl;
        }
        return 0;//都不是,出错!
        ////////////////////////////////////////////////////
    }
}

//记录正确走法
void Solution(LinkList &recode, LinkList &rightways) {
    rightways.CreatFristNode(0, 0, 0); //创建首结点为空
    recode.cur = recode.head;
    while (recode.cur != recode.tail) {
        if (rightways.tail->ways != TellTheDirection(*(recode.cur)) ) {
            rightways.Creat( 0, 0, TellTheDirection(*(recode.cur)) );
        }
        recode.cur =  recode.cur->next;
    }	//不能用(T_L*100+T_R)简化计算,否则当SIZE>100将不可支持。
}

//记录用于对比输入字符串InPut的Answer字符串
void GetAnswer(LinkList &rightways, char Answer[]) {
    Answer[0] = '*';
    Answer[1] = '-';
    int k = 2;
    rightways.cur = rightways.head->next;
    for (int i = 0; i < rightways.counts - 1; i++) {
        switch (rightways.cur->ways) {
        case 1:
            Answer[k] = 'w';
            k++;
            Answer[k] = '-';
            k++;
            break;
        case 2:
            Answer[k] = 's';
            k++;
            Answer[k] = '-';
            k++;
            break;
        case 3:
            Answer[k] = 'a';
            k++;
            Answer[k] = '-';
            k++;
            break;
        case 4:
            Answer[k] = 'd';
            k++;
            Answer[k] = '-';
            k++;
            break;
        ////////////////////////////////////////////////////
        default:
            if (DEBUG == 1) {
                cout << "\n运行错误:rightways的记录不是任何方向!" << endl;
            }
            return;
            ////////////////////////////////////////////////////
        }
        rightways.cur = rightways.cur->next;
    }
    Answer[k] = '#';
    Answer[k + 1] = '\0';
}

//将rightways链输出屏幕，写入文件
void PutTheSolution(LinkList &rightways) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    fstream Palace;
    Palace.open("Solution.txt", ios::out | ios::trunc);
    cout << "起点-";
    Palace << "起点-";
    rightways.cur = rightways.head->next;
    for (int i = 0; i < rightways.counts - 1; i++) {
        switch (rightways.cur->ways) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        case 1:
            cout << "上-";
            Palace << "上-";
            break;
        case 2:
            cout << "下-";
            Palace << "下-";
            break;
        case 3:
            cout << "左-";
            Palace << "左-";
            break;
        case 4:
            cout << "右-";
            Palace << "右-";
            break;
        ////////////////////////////////////////////////////
        default:
            if (DEBUG == 1) {
                cout << "\n运行错误:rightways的记录不是任何方向!" << endl;
            }
            return;
            ////////////////////////////////////////////////////
        }
        rightways.cur = rightways.cur->next;
    }
    cout << "终点! ";
    Palace << "终点!";
    Palace.close();
}
