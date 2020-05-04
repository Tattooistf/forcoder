/*
 * @lc app=leetcode.cn id=143 lang=c
 *
 * [143] 重排链表
 *
 * https://leetcode-cn.com/problems/reorder-list/description/
 *
 * algorithms
 * Medium (55.75%)
 * Likes:    207
 * Dislikes: 0
 * Total Accepted:    22.8K
 * Total Submissions: 40.9K
 * Testcase Example:  '[1,2,3,4]'
 *
 * 给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
 * 将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
 * 
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * 
 * 示例 1:
 * 
 * 给定链表 1->2->3->4, 重新排列为 1->4->2->3.
 * 
 * 示例 2:
 * 
 * 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

 struct ListNode {
     int val;
     struct ListNode *next;
 };

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *reserve(struct ListNode *Node);
void reorderList(struct ListNode* head){
    struct ListNode* fast=head;
    struct ListNode* slow=head;
    // 思路先对后半程进行反序，然后将前半部分进行融合
    if (head == NULL)
    {
        return;
    }
    // 找到中位节点
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct ListNode* end = slow;
    struct ListNode* start = head;
    // 对后半程进行反序
    slow = reserve(slow);
    // 进行两部分链表的拼接
    while (start != end)
    {
        struct ListNode* starttemp = start->next;
        struct ListNode* slowtemp = slow->next;
        start->next = slow;
        slow->next = starttemp;

        start = starttemp;
        slow = slowtemp;
    }
    start->next = NULL;    
    return;
}

struct ListNode *reserve(struct ListNode *Node)
{
    struct ListNode* temp=NULL;
    struct ListNode* pretemp=NULL;

    temp = Node->next;
    pretemp = Node;
    while (temp != NULL && temp->next != NULL)
    {
        struct ListNode* nextnode = temp->next;
        temp->next = pretemp;
        pretemp=temp;
        temp = nextnode;
    }
    Node->next = NULL;
    if (temp == NULL)
    {
        Node = pretemp;
    }
    else
    {
        temp->next = pretemp;
        Node = temp;
    }
    return Node;
}

// @lc code=end
void print(struct ListNode *pNode);
int main(void)
{
    int count = 7;
    int i = 1;
    struct ListNode head;
    struct ListNode *node = &head;
    while (i <= count)
    {
        struct ListNode *pNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        pNode->val = i;
        pNode->next = NULL;
        node->next = pNode;
        node = node->next;
        i++;
    }
    print(head.next);
    reorderList(head.next);
    print(head.next);
    return 0;
}

void print(struct ListNode *pNode)
{
    while (pNode)
    {
        printf("%p:%d -> ",pNode,pNode->val);
        pNode=pNode->next;
    }
    printf("null\n");
    return;
}