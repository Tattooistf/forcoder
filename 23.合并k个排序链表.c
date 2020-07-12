/*
 * @lc app=leetcode.cn id=23 lang=c
 *
 * [23] 合并K个排序链表
 *
 * https://leetcode-cn.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (51.84%)
 * Likes:    782
 * Dislikes: 0
 * Total Accepted:    140.3K
 * Total Submissions: 268.8K
 * Testcase Example:  '[[1,4,5],[1,3,4],[2,6]]'
 *
 * 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 * 
 * 示例:
 * 
 * 输入:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * 输出: 1->1->2->3->4->4->5->6
 * 
 */
#include "stdio.h"
#include "stdlib.h"
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
// 堆实现 ：虽然算法时间复杂度低，但是调试成本太高，相比分裂合并法优势不明显
// 原理：每次从K个链表中选择最小的数，加入堆中；最小堆
static struct ListNode **g_pHeap = NULL;
static int g_size = 0;
void CreateHeap(int size)
{
    g_pHeap = (struct ListNode **)malloc(sizeof(struct ListNode*)*(size+1));
    memset(g_pHeap,0,sizeof(struct ListNode*)*(size+1));
    g_size = 0;
    return;
}
void DestroyHeap(void)
{
    free(g_pHeap);
    g_pHeap = NULL;
    g_size = 0;
}
void PushHeap(struct ListNode* ptr) // 第一次坑 int*参数导致listNode*被截断成32位
{
    g_pHeap[++g_size] = ptr;
    // 开始整理堆
    int i = g_size;
    while ((i>>1)>=1 && ptr->val < g_pHeap[i>>1]->val)
    {
        g_pHeap[i] = g_pHeap[i>>1];
        i = i>>1;
    }
    g_pHeap[i] = ptr;
    return;
}

struct ListNode *PopHeap(void)
{
    struct ListNode* res = g_pHeap[1];
    // 整理堆
    struct ListNode* tmp = g_pHeap[g_size];
    g_size--;
    int i = 1; // 第二次栽跟头：考虑后面的2*i和2*i+1的关系，i必须从1开始 
    while (2*i<= g_size)
    {
        int j = 0;
        if (2*i+1 <= g_size && g_pHeap[2*i]->val > g_pHeap[2*i+1]->val)
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        if (tmp->val > g_pHeap[j]->val)
        {
            g_pHeap[i] = g_pHeap[j];
        }
        else
        {
            break;
        }
        i=j;
    }
    g_pHeap[i] = tmp;
    return res;
}

int HeapEmpty(void)
{
    return (g_size == 0)?1:0;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if (listsSize < 1)
    {
        return NULL;
    }
    struct ListNode Node;
    Node.next = NULL; // 第三个坑：空数组情况下直接返回异常随机值
    struct ListNode* res = &Node;
    struct ListNode* tmp = NULL;
    CreateHeap(listsSize);
        
    for (int i = 0; i < listsSize; i++)
    {
        if (lists[i] != NULL)
        {
            PushHeap(lists[i]);
        }
    }

    while (!HeapEmpty())
    {
        tmp = PopHeap();
        res->next = tmp;
        res = res->next;               
        if (tmp->next != NULL)
        {
            PushHeap(tmp->next);
        }
    }
    DestroyHeap();
    return Node.next;
}

// @lc code=end

// 分裂合并法，递归
struct ListNode* merge2List(struct ListNode* head, struct ListNode* tail)
{
    struct ListNode Node;
    struct ListNode* res = &Node;
    while (head != NULL && tail != NULL)
    {
        if (head->val <= tail->val) // 分裂法第二个栽跟头 比较符号搞反，导致结果错误没有排序
        {
            res->next = head;
            head = head->next;
        }
        else
        {
            res->next = tail;
            tail = tail->next;
        }
        res = res->next;
    }
    res->next = (head!=NULL)?head:tail;
    
    return Node.next;
}

 struct ListNode* mergeRegion(struct ListNode **lists, int left, int right)
 {
     struct ListNode* a = NULL;
     struct ListNode* b = NULL;
    if (left == right)
    {
        return lists[right];
    }
    if (right < left)
    {
        return lists[left];
    }
    int mid = (left+right)/2;
    a = mergeRegion(lists,left,mid);
    b = mergeRegion(lists,mid+1,right);
    return merge2List(a,b);
 }
// 两个链表合并的方式处理
// 还有两种解题方式，一种是通过分裂合并实现，一种是通过推排序实现
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode *res = NULL;
    if (listsSize < 1) // 分裂法第三个跟头，忘记判断为空的情况
    {
        return NULL;
    }
    
    res = mergeRegion(lists,0,listsSize-1);// 分裂合并法栽跟头listsSize忘记-1导致heap异常
    return res;
}


// 循环两两合并法
 struct ListNode* insert(struct ListNode *head,struct ListNode *op)
 {
     struct ListNode node;
     struct ListNode *dst = &node;
     while (op != NULL && head != NULL)
     {
         if (op->val <= head->val)
         {
             dst->next = op;
             op = op->next;
         }
         else
         {
             dst->next = head;
             head = head->next;
         }
         dst = dst->next;
     }
     dst->next = (op == NULL)?head:op;  
     dst = node.next;   
     return dst;
 }
// 两个链表合并的方式处理
// 还有两种解题方式，一种是通过分裂合并实现，一种是通过推排序实现
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode *res = NULL;
    for (int i = 0; i < listsSize; i++)
    {
        struct ListNode *op = lists[i];
        res = insert(res,op);
    }
    return res;
}