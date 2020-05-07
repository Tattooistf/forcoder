/*
 * @lc app=leetcode.cn id=147 lang=c
 *
 * [147] 对链表进行插入排序
 *
 * https://leetcode-cn.com/problems/insertion-sort-list/description/
 *
 * algorithms
 * Medium (63.97%)
 * Likes:    153
 * Dislikes: 0
 * Total Accepted:    28K
 * Total Submissions: 43.7K
 * Testcase Example:  '[4,2,1,3]'
 *
 * 对链表进行插入排序。
 * 
 * 
 * 插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
 * 每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。
 * 
 * 
 * 
 * 插入排序算法：
 * 
 * 
 * 插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
 * 每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
 * 重复直到所有输入数据插入完为止。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入: 4->2->1->3
 * 输出: 1->2->3->4
 * 
 * 
 * 示例 2：
 * 
 * 输入: -1->5->3->4->0
 * 输出: -1->0->3->4->5
 * 
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


struct ListNode* insertionSortList(struct ListNode* head){
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    struct ListNode node;
    struct ListNode *pnode = &node;
    struct ListNode *tnd = head;
    struct ListNode *start = pnode;
    pnode->next = NULL;

    while (tnd)
    {
        struct ListNode *nnd = tnd->next;
        // 之前是每次都从头部找起，后面优化为只有比上次值小的时候才开始从头找，性能提升10倍
        if (start->val > tnd->val) start = pnode;

        // 插入当前节点
        while (start->next && tnd->val > start->next->val)
        {
            start = start->next;
        }
        struct ListNode *tmp = start->next;
        start->next = tnd;
        tnd->next = tmp;
        
        tnd = nnd;
    }

    return pnode->next;    
}


// @lc code=end

