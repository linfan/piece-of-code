#include <iostream.h>
#include <fstream.h>
#include <windows.h>
#include <stdlib.h>

const void MainView(int (&table)[9][9][10]);
const void GiveAnswer(int (&table)[9][9][10]);
const void NoAnswer();

//结点的定义
class ListNode {
public:
    int L, R;
    ListNode *next, *prov;
};

//链表的定义
class LinkList {
public:

    ListNode *head, *tail, *cur, *end;
//迫于无奈的修改,tail成为"伪尾结点",tail->next=end
    int counts;

    LinkList() {
        head = new ListNode;
        end = new ListNode;
        //不是*head,因为只有才能=new获取的空间
        head->next = end;
        head->prov = 0;
        end->next = 0;
        end->prov = 0;//因为用不着
        tail = cur = head;
    }

    ~LinkList() {
        while (head != tail) {
            LinkList::Pop();
        }
        delete head;
        delete end;
    }

    Push(int LL, int RR) {
        cur = tail;
        tail = new ListNode;
        tail->L = LL;
        tail->R = RR;
        tail->next = end;
        tail->prov = cur;
        cur->next = tail;
        counts++;
    }

    Pop() {
        cur = tail->prov;
        delete tail;
        cur->next = end;
        tail = cur;
        counts--;
    }

};



//主函数
void main() {
    int T_L, T_R, table[9][9][10], tablecopy[9][3][3];
    LinkList recode;//recode仅记录table中哪些位置可写
    recode.counts = 0;

    fstream file1("Table.txt", ios::in);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char Cr = file1.get();
            table[i][j][0] = atoi(&Cr);
            //不加&报错cannot convert from 'char' to 'const char *'
        }
        file1.seekg(2, ios::cur);
    }
    file1.close();

//---- DEBUG 检测读入Table是否正确 ----//
//for(int m=0;m<9;m++){for(int n=0;n<9;n++){cout<<table[m][n][0];}cout<<endl;}

    MainView(table);//主界面
    cout << "\n☆按下任意键,让魔法来得更猛烈些吧☆" << endl;
    system("pause");

//可用位置记入recode
    for (int k = 0; k < 9; k++) {
        for (int l = 0; l < 9; l++) {
            if (table[k][l][0] == 0) {
                recode.Push(k, l);
            }
        }
    }

    recode.cur = recode.head->next;
//head头结点是空的

    int tempB = 0;//为1表明是之前一步无值可取,退下来的
    int tempZ;//为0表示当前位置已无值可用
    int tempR = 1;//为0表示无解
    int tempN;
    int tempT;

//recode.L&R->table[][][]
    do {

        tempZ = 0;

        T_L = recode.cur->L;
        T_R = recode.cur->R;

        if (tempB == 0) {

            //table->tablecopy
            int x = -1;
            for (int y = 0; y < 9; y++) {
                if (y % 3 != 0) {
                    x -= 3;
                }
                for (int z = 0; z < 9; z++) {
                    if (z % 3 == 0) {
                        x++;
                    }
                    tablecopy[x][y % 3][z % 3] = table[y][z][0];
                }
            }


            for (int l = 0; l < 10; l++) {
                table[T_L][T_R][l] = 0;   //全部初始化0
            }

            for (int j = 0; j < 9; j++) { //T_L&T_R所在行
                tempT = table[T_L][j][0];
                if (j != T_R) {
                    table[T_L][T_R][tempT] = tempT;
                }
            }

            for (int p = 0; p < 9; p++) { //T_L&T_R所在列
                tempT = table[p][T_R][0];
                if (p != T_L) {
                    table[T_L][T_R][tempT] = tempT;
                }
            }

            //T_L&T_R所在3×3小格
            for (int q = 0; q < 3; q++) {
                for (int n = 0; n < 3; n++) {
                    tempN = (int(T_L / 3)) * 3 + T_R / 3;
                    tempT = tablecopy[tempN][q][n];
                    table[T_L][T_R][tempT] = tempT;
                }
            }


            for (int r = 1; r < 10; r++) { // 反取
                if (table[T_L][T_R][r] == 0) {
                    table[T_L][T_R][r] = r;
                    tempZ = 1;
                } else {
                    table[T_L][T_R][r] = 0;
                }
            }
        } else {
            table[T_L][T_R][0] = 0;
            tempB = 0;
            for (int r = 1; r < 10; r++) { // 测是否有可用值
                if (table[T_L][T_R][r] != 0) {
                    tempZ = 1;
                    break;
                }
            }
        }
// -------- Ctrl + F10 至此 ---------

        if (tempZ == 0) { //当无值可取时
            recode.cur = recode.cur->prov;
            tempB = 1;

            if (recode.cur == recode.head) {
                recode.cur = recode.end;
                tempR = 0;
                break;
            }
        } else {
            for (int t = 1; t < 10; t++) {
                if (table[T_L][T_R][t] != 0) {
                    table[T_L][T_R][t] = 0;
                    table[T_L][T_R][0] = t;
                    break;
                }
            }
            recode.cur = recode.cur->next;
        }

//---- DEBUG 检测Table结果是否正确 ----//
//cout<<'\n'<<endl;for(int u=0;u<9;u++){for(int v=0;v<9;v++){cout<<table[u][v][0];}cout<<endl;}

// -------- Ctrl + F10 至此 ---------

    } while (recode.cur != recode.end);



    fstream file2("Result.txt", ios::out);
    if (tempR != 0) {
        system("cls");
        GiveAnswer(table);//显示解答

        for (int w = 0; w < 9; w++) {
            for (int v = 0; v < 9; v++) {
                file2 << table[w][v][0];
            }
            file2 << endl;
        }
    } else {
        system("cls");
        NoAnswer();

        file2 << endl;
        file2 << "  ┏━━━━━━━━━━━━┓" << endl;
        file2 << "  ┃                        ┃" << endl;
        file2 << "  ┃        无  解  !       ┃" << endl;
        file2 << "  ┃                        ┃" << endl;
        file2 << "  ┗━━━━━━━━━━━━┛" << endl;
    }
    file2.close();
    system("pause");
}
