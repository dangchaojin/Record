#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <regex>
#include <string>

/*

Todo：插入

*/




typedef int DataType;
struct Node {
    DataType data;
    struct Node *next;
};

void Display(Node *p)
{
    while (p) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

void DelSameNode(Node *head)
{
    Node *p, *q, *s;  // s是位置标记的作用
    p = head;
    while (p != nullptr && p->next != nullptr) {
        s = p;
        q = p->next;
        while (q != nullptr) {
            if (p->data == q->data) {
                s->next = q->next;
                free(q);
                q = s->next;
            } else {
                s = q;
                q = q->next;
            }
        }
        p = p->next;
    }
}

Node *reverse1(Node *n)
{
    if (n == nullptr) {
        return nullptr;
    }

    Node *old = n;
    Node *tmp = nullptr;

    Node *cur = old->next;
    old->next = nullptr;

    while (cur != nullptr) {
        tmp = cur->next;
        cur->next = old;
        old = cur;
        cur = tmp;
    }
    return old;
}

Node *reverse2(Node *oldList, Node *newHead = NULL)
{
    Node *next = oldList->next;  //记录上次翻转后的链表
    oldList->next = newHead;  //将当前结点插入到翻转后链表的开头
    newHead = oldList;  //递归处理剩余的链表
    return (next == NULL) ? newHead : reverse2(next, newHead);
}

int main()
{
    Node *list1 = (Node *)malloc(sizeof(Node));
    Node *list2 = (Node *)malloc(sizeof(Node));
    Node *list3 = (Node *)malloc(sizeof(Node));
    Node *list4 = (Node *)malloc(sizeof(Node));
    Node *list5 = (Node *)malloc(sizeof(Node));

    list1->data = 10;
    list2->data = 20;
    list3->data = 30;
    list4->data = 20;
    list5->data = 50;

    list1->next = list2;
    list2->next = list3;
    list3->next = list4;
    list4->next = list5;
    list5->next = nullptr;

    // std::cout << "delete same number:" << std::endl;
    // std::cout << "first: ";
    // Display(list1);
    // DelSameNode(list1);
    // std::cout << "second: ";
    // Display(list1);

    std::cout << "reverse1 Node:" << std::endl;
    std::cout << "first: ";
    Display(list1);
    Node *reverseList = reverse1(list1);
    std::cout << "second: ";
    Display(reverseList);
	
    std::cout << "reverse2 Node:" << std::endl;
    std::cout << "first: ";
    Display(list1);
    Node *reverseList = reverse2(list1);
    std::cout << "second: ";
    Display(reverseList);

    system("pause");
    return 0;
}