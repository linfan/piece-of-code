#include "WordNode.h"
#include <iostream>
using namespace std;
#define MAX 21
#define FALSE 0
#define TRUE 1

class LinkList;
class WordNode;
void Change(WordNode *, WordNode *, int, int);
int Compare(const char left[], const char right[]);
void Fill(char(&me)[MAX]);

/*----------------类函数实现部分--------------------*/


//构造WordNode实例
WordNode::WordNode(char(&e)[MAX], char(&c)[MAX], char(&n)[MAX]) {
    strcpy(this->eword, e);
    strcpy(this->cword, c);
    strcpy(this->note, n);
}
//第二种
WordNode::WordNode() {
    strcpy(this->eword, " ");
    strcpy(this->cword, " ");
    strcpy(this->note, " ");
}

//构造LinkList实例
LinkList::LinkList() {
    head = new WordNode(); //首结点初始为空!!
    curr = tail = head;
    curr->next = curr->pre = 0;
}

//析构LinkList实例
LinkList::~LinkList() {
    curr = head;
    for (; curr != tail; curr = curr->next)
        delete curr->pre;
    delete tail;
}

//计算结点数
int LinkList::CountNode() {
    int NUM = 1;
    curr = head;
    for (; curr != tail; curr = curr->next)
        NUM++;
    return NUM;
}

//插入新结点
void LinkList::Intert(char(&e)[MAX], char(&c)[MAX], char(&n)[MAX]) {
    curr = tail;
    Fill(e);
    Fill(c);
    Fill(n);
    tail = new WordNode(e, c, n);
    tail->next = 0;
    tail->pre = curr;
    curr->next = tail;
    curr = tail; //curr指向新创建的结点
}

//删除当前结点
void LinkList::Drop() {
    if (curr == tail) {
        (curr->pre)->next = 0;
        tail = tail->pre;
        delete curr;
        curr = tail;
    } else if (curr == head) {
        (curr->next)->pre = 0;
        head = head->next;
        delete curr;
        curr = head;
    } else {
        (curr->pre)->next = curr->next;
        (curr->next)->pre = curr->pre;
        delete curr;
        curr = head;
    }
}

//显示当前结点内容
void LinkList::ShowNode() {
    cout.width(0);
    cout << "E: ";

    cout.width(20);
    cout.setf(ios::left);
    cout << curr->eword;

    cout.width(0);
    cout << "C: ";

    cout.width(20);
    cout.setf(ios::left);
    cout << curr->cword;

    cout.width(0);
    cout << "N: ";

    cout.width(20);
    cout.setf(ios::left);
    cout << curr->note << endl;
}


//查找结点
WordNode *LinkList::Search(char sear[]) { //形参可以省略[]中的数字。
    int i = 0;
    bool IsSame = FALSE;
    this->curr = this->head;
    while (this->curr != this->tail) {
        //搜索非末尾结点
        i = 0;
        while ((this->curr)->eword[i] <= 'z'
                && (this->curr)->eword[i] >= 'a'
                && sear[i] <= 'z'
                && sear[i] >= 'a') {
            if (sear[i] == (this->curr)->eword[i]) {
                IsSame = TRUE;
            } else {
                IsSame = FALSE;
                break;
            }
            i++;
        }
        if (((this->curr)->eword[i] > 'z' || (this->curr)->eword[i] < 'a')
                && (sear[i] > 'z' || sear[i] < 'a')
                && IsSame == TRUE) {
            return this->curr;
        }
        this->curr = (this->curr)->next;
    }
    //搜索末尾结点
    i = 0;
    while ((this->tail)->eword[i] <= 'z'
            && (this->tail)->eword[i] >= 'a'
            && sear[i] <= 'z'
            && sear[i] >= 'a') {
        if (sear[i] == (this->tail)->eword[i]) {
            IsSame = TRUE;
        } else {
            IsSame = FALSE;
            return NULL;;
        }
        i++;
    }
    if (((this->tail)->eword[i] > 'z' || (this->tail)->eword[i] < 'a')
            && (sear[i] > 'z' || sear[i] < 'a')
            && IsSame == TRUE) {
        return this->tail;
    }
    return NULL;
}


//结点排序
void LinkList::Sort(LinkList &words)
////////////////////////////////
/*超级大的BUG! 排序结果不正确!*/
////////////////////////////////

{
    int N = CountNode();
    for (int i = 0; i < N - 1; i++) {
        curr = tail;
        for (int j = 0; j < N - 1; j++) {
            char left[MAX], right[MAX];
            strcpy(left, (curr->eword));
            strcpy(right, curr->pre->eword);
            if (Compare(left, right) < 0) {
                //			Change(curr,curr->pre,i,j);curr = curr->pre;
                //			运算符'%'的检验函数;
                *curr % (curr->pre); /*双目运算符作为成员重载，
        其左值只能是一个对象，
        其右值由声明的形参决定。
        所以这里的%左值必须为*curr
        而不能是curr(指针)。
         */
                curr = curr->pre;
            }
        }
    }
    curr = head; //curr回首结点
}

void LinkList::FreeAllNode(LinkList &words) { //程序结束前释放所有结点
    words.curr = words.tail;
    while (words.curr != words.head) {
        words.tail = words.tail->pre;
        delete words.curr;
        words.curr = words.tail;
    }
    ///////////////////////////////////////////
    //delete words.head ;
    /* ^此行报错，原因未知。因此无法delete头结点。 */
    ///////////////////////////////////////////
}


/*----------------运算符重载实现--------------------*/

//交换两结点内容
void WordNode::operator % (WordNode *that) {
    WordNode *temp = new WordNode();
    strcpy(temp->eword, this->eword);
    strcpy(temp->cword, this->cword);
    strcpy(temp->note, this->note);
    strcpy(this->eword, that->eword);
    strcpy(this->cword, that->cword);
    strcpy(this->note, that->note);
    strcpy(that->eword, temp->eword);
    strcpy(that->cword, temp->cword);
    strcpy(that->note, temp->note);
    delete temp;
}

/*

//重载运算符'%'的检验和替代函数[仅在原始设计时被使用]
void Change(WordNode *left, WordNode *right, int i, int j)
{
  cout << i << "-" << j << endl;
  WordNode *temp = new WordNode();
  strcpy(temp->eword, left->eword);
  cout << "1-";
  strcpy(temp->cword, left->cword);
  cout << "2-";
  strcpy(temp->note, left->note);
  cout << "3-";
  strcpy(left->eword, right->eword);
  cout << "4-";
  strcpy(left->cword, right->cword);
  cout << "5-";
  strcpy(left->note, right->note);
  cout << "6-";
  strcpy(right->eword, temp->eword);
  cout << "7-";
  strcpy(right->cword, temp->cword);
  cout << "8-";
  strcpy(right->note, temp->note);
  cout << "9-" << endl;
  delete temp;
}


//查找结点
WordNode *LinkList::Old_Search(char sear[])
{
  if ((this->curr)->eword[0] = sear[0])
  //第一位相同
  {
    if ((this->curr)->eword[1] = sear[1])
    //第二位也相同
    {
      int len = MAX; //搜索字符串的长度
      for (int i = 0; i < MAX; i++)
      {
        if (sear[i] == 0)
        {
          len = i;
          i = MAX;
        }
      }
      this->curr = this->head;
      for (; this->curr != this->tail; this->curr = (this->curr)->next)
      {
        if (strstr((this->curr)->eword, sear) != NULL)
        //[eword长度] >= [sear长度]
        {
          if ((this->curr)->eword[len] == ' ')
          //[eword长度] <= [sear长度]
          {
            return this->curr;
          } //eword 与 sear长度相同,内容重合,即为要找的词条
        }
      }
      if (strstr((this->curr)->eword, sear) != NULL)
      if ((this->curr)->eword[len] == ' ')
      {
        {
          return this->tail;
        }
      }
    }
  }
  return NULL;
}

*/
