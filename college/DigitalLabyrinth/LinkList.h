class LinkList;

class ListNode {
public: //一切为了速度,不要private了!
    ListNode(int L, int R, int W): T_L(L), T_R(R), ways(W) {}
    ~ListNode() {};
    ListNode *next, *prov;
    int T_L, T_R, ways;
};

class LinkList {
public:
    ListNode *head, *tail, *cur;
    LinkList() {}
    ~LinkList();
    void Creat(int, int, int);
    void CreatFristNode(int, int, int);
    void Drop();
    int counts;//记录已有结点数
};
