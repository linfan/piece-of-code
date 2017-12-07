#ifndef __WordNode_H__
#define __WordNode_H__
#define MAX 21

class WordNode;

//词链类声明
class LinkList {
private:
    WordNode *head;
    WordNode *tail;
    WordNode *curr;
public:
    LinkList();
    ~LinkList();
    int CountNode();
    void ShowNode();
    void Sort(class LinkList &words); //传入参数为自定义类的函数声明应加class
    WordNode *Search(char[]);
    void Intert(char(&e)[MAX], char(&c)[MAX], char(&n)[MAX]);
    void Drop();
    void FreeAllNode(LinkList &words);
    WordNode *GetHead() {
        return head;
    } WordNode *GetTail() {
        return tail;
    }
    WordNode *GetCurr() {
        return curr;
    }
    void ModifyCurr(WordNode *to) {
        curr = to;
    }
};

//词结点类声明
class WordNode {
private:
    WordNode *next;
    WordNode *pre;
public:
    void operator % (WordNode *that);
    char eword[MAX];
    char cword[MAX];
    char note[MAX];
    friend class LinkList;
    WordNode(char(&e)[MAX], char(&c)[MAX], char(&n)[MAX]);
    WordNode();
    WordNode *GetNext() {
        return next;
    }
};

#endif
