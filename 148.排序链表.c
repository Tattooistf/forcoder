/*
 * @lc app=leetcode.cn id=148 lang=c
 *
 * [148] 排序链表
 *
 * https://leetcode-cn.com/problems/sort-list/description/
 *
 * algorithms
 * Medium (65.08%)
 * Likes:    518
 * Dislikes: 0
 * Total Accepted:    57.8K
 * Total Submissions: 88.7K
 * Testcase Example:  '[4,2,1,3]'
 *
 * 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 * 
 * 示例 1:
 * 
 * 输入: 4->2->1->3
 * 输出: 1->2->3->4
 * 
 * 
 * 示例 2:
 * 
 * 输入: -1->5->3->4->0
 * 输出: -1->0->3->4->5
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


struct ListNode* sortList(struct ListNode* head){
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    // 快慢指针找到中间节点
    // 栽的第一个坑，2个节点的时候会陷入死循环，修正fast=head->next
    fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    // 将链表切割为两个链表
    struct ListNode *left = head;
    struct ListNode *right = slow->next;
    slow->next = NULL;
    left = sortList(left);
    right = sortList(right);
    struct ListNode *newHead = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *res = newHead;
    // 对两个链表进行合并
    while (left != NULL && right != NULL)
    {
        if (left->val < right->val)
        {
            newHead->next = left;
            left = left->next;
        }
        else
        {
            newHead->next = right;
            right = right->next;
        }
        newHead = newHead->next;
    }
    newHead->next = (left == NULL)?right:left;
    // 释放伪节点
    newHead = res->next;
    free(res);
    return newHead;
}


// @lc code=end

void print(struct ListNode *pNode);
int main(void)
{
    int count = 6;
    int i = 1;
    struct ListNode head;
    struct ListNode *node = &head;
    while (i <= count)
    {
        struct ListNode *pNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        pNode->val = rand()%14;
        pNode->next = NULL;
        node->next = pNode;
        node = node->next;
        i++;
    }
    print(head.next);
    struct ListNode *res = sortList(head.next);
    print(res);
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
