#include <cstdlib>
#include <iostream>

typedef int DataType;
struct Node {
    DataType data;
    struct Node *next;
};

void Display(Node *p)
{
    while (p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

void DelSameNode(Node *head)
{
    Node *p, *q, *s;    // s是位置标记的作用
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

    std::cout << "first" << std::endl;
    Display(list1);

    DelSameNode(list1);

    std::cout << "second" << std::endl;
    Display(list1);

    system("pause");
    return 0;
}