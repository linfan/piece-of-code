#include "LinkList.h"

class LinkList;
class ListNode; //使用类前必须声明，否则将报错


void LinkList::Creat(int L, int R, int W) {
    cur = tail;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    tail = new ListNode(L, R, W);
    tail->prov = cur;
    tail->next = 0;
    cur->next = tail;
    counts++;
}//新结点添加在链尾

void LinkList::CreatFristNode(int L, int R, int W) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    head = new ListNode(L, R, W);
    tail = head;
    cur = head;
    head->prov = 0;
    head->next = 0;
    counts = 1;
}//创建头结点

void LinkList::Drop() {
    cur = tail->prov;
    delete tail;
    cur->next = 0;
    tail = cur;
    counts--;
}//删除尾结点

LinkList::~LinkList(void) {
    cur = head;
    while (cur != tail) {
        cur = cur->next;
        delete cur->prov;
    }
    delete tail;
}
