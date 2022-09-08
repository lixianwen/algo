/*
Promlem: Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

O(n) time and O(1) space complexity implemention.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Definition for singly-linked list.
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode, *LinkList, *NodePtr;

/*
如果结点数是偶数，中间结点在上半部分，判断条件是 fast->next && fast->next->next
如果判断条件是 fast && fast->next，则中间结点在下半部分
中间结点在上半部分的好处有：
  - 方便对比上半部分和反转后的下半部分（节点数为奇数时，对比不包括中间结点本身，偶数则对比包括中间结点）
  - 中间结点的下一个结点就是下半部分的头结点
*/
struct ListNode* findMiddleNode(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;
}

struct ListNode* reverse(struct ListNode *head)
{
    struct ListNode *prev = NULL, *next;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}

bool isPalindrome(struct ListNode *head)
{
    if (head == NULL) {
        return false;
    }

    struct ListNode *middle_node = findMiddleNode(head);
    struct ListNode *reversed_head = reverse(middle_node->next);
    if (reversed_head == NULL) {   // only one node in linked list and we consider it as true
        return true;
    }

    bool is_palindrome = true;
    struct ListNode *p = head, *q = reversed_head;
    while (p && q) {
        if (p->val != q->val) {
            is_palindrome = false;
            break;
        } else {
            p = p->next;
            q = q->next;
        }
    }

    // 再次反转链表的下半部分
    reversed_head = reverse(reversed_head);
    middle_node->next = reversed_head;

    return is_palindrome;
}

NodePtr createNode(int value)
{
    NodePtr p = (NodePtr)malloc(sizeof(ListNode));
    p->val = value;
    p->next = NULL;

    return p;
}

NodePtr insertHead(LinkList l, int value)
{
    NodePtr p = createNode(value);
    p->next = l;
    l = p;

    return l;
}

void destroy(LinkList l)
{
    NodePtr p, q;
    for (p=l; p; p=q) {
        q = p->next;
        free(p);
    }
}

int main(void)
{
    LinkList l = createNode(1);
    l = insertHead(l, 1);
    printf("is palindrome: %d\n", isPalindrome(l));
    destroy(l);

    return 0;
}