/*
 * @lc app=leetcode.cn id=1019 lang=c
 *
 * [1019] 链表中的下一个更大节点
 *
 * https://leetcode-cn.com/problems/next-greater-node-in-linked-list/description/
 *
 * algorithms
 * Medium (58.22%)
 * Likes:    158
 * Dislikes: 0
 * Total Accepted:    18.3K
 * Total Submissions: 30.8K
 * Testcase Example:  '[2,1,5]'
 *
 * 给出一个以头节点 head 作为第一个节点的链表。链表中的节点分别编号为：node_1, node_2, node_3, ... 。
 * 
 * 每个节点都可能有下一个更大值（next larger value）：对于 node_i，如果其 next_larger(node_i) 是
 * node_j.val，那么就有 j > i 且  node_j.val > node_i.val，而 j 是可能的选项中最小的那个。如果不存在这样的
 * j，那么下一个更大值为 0 。
 * 
 * 返回整数答案数组 answer，其中 answer[i] = next_larger(node_{i+1}) 。
 * 
 * 注意：在下面的示例中，诸如 [2,1,5] 这样的输入（不是输出）是链表的序列化表示，其头节点的值为 2，第二个节点值为 1，第三个节点值为 5
 * 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[2,1,5]
 * 输出：[5,5,0]
 * 
 * 
 * 示例 2：
 * 
 * 输入：[2,7,4,3,5]
 * 输出：[7,0,5,5,0]
 * 
 * 
 * 示例 3：
 * 
 * 输入：[1,7,5,1,9,2,5,1]
 * 输出：[7,9,9,9,0,5,0,0]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 对于链表中的每个节点，1 <= node.val <= 10^9
 * 给定列表的长度在 [0, 10000] 范围内
 * 
 * 
 */
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
// 两种解题思路
// 1、暴力解题，每个node遍历后面的节点
// 2、单调栈解法，反转链表，从后往前求解，结果再反转

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 单调栈解法一次通过，性能得到很大提升
int *Stack = NULL;
int Count = 0;
int Top = 0;
void StackInit(int size)
{
    Stack = (int *)malloc(sizeof(int)*size);
    memset(Stack,0,sizeof(int)*size);
    Count = size;
    Top = 0;
    return;
}

void StackDestory(void)
{
    Count = 0;
    Top = 0;
    free(Stack);
    return;
}

void StackPush(int val)
{
    if (Top >= Count)
    {
        printf("Stack Full\n");
        return;
    }
    Stack[Top++] = val;
    return;
}

int StackPop(void)
{
    if (Top <= 0)
    {
        printf("Stack Empty\n");
        return 0;
    }
    return Stack[--Top];
}

int StackEmpty(void)
{
    return (Top == 0) ? 1 : 0;
}

int StackTop(void)
{
    return Stack[Top-1];
}

void reversearr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i > len-i-1)
        {
            break;
        }
        
        int tmp = arr[i];
        arr[i] = arr[len-1-i];
        arr[len-1-i] = tmp;
    }
    return;
}

struct ListNode *reverse(struct ListNode *list)
{
    struct ListNode *pre = NULL;
    struct ListNode *cur = list;
    struct ListNode *next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    
    return pre;
}
// 从前往后遍历，单调递减；当出现大于的时候不断赋值
int* nextLargerNodes(struct ListNode* head, int* returnSize){
    int len = 0;
    struct ListNode *node = head;
    while (node)
    {
        node = node->next;
        len++;
    }

    int *arr = (int *)malloc(sizeof(int)*len);
    int idx = 0;
    node = head;
    while (node)
    {
        arr[idx++] = node->val;
        node = node->next;
    }
    StackInit(len);
    int *ret = (int *)malloc(sizeof(int)*len);
    memset(ret, 0, sizeof(int)*len);
    for (int i = 0; i < len; i++)
    {
        while (!StackEmpty() && arr[StackTop()] < arr[i])
        {
            ret[StackTop()] = arr[i];
            StackPop();
        }
        StackPush(i);
    }
    *returnSize = len;
    free(arr);
    StackDestory();
    return ret;
}


// 从后往前遍历，单调递减，当出现大于的时候就不断弹栈，直到小于对方
int* nextLargerNodes2(struct ListNode* head, int* returnSize){
    struct ListNode *newHead = NULL;
    int tmp[10000] = {0};
    int len = 0;
    StackInit(10000);
    newHead = reverse(head);

    while (newHead != NULL)
    {
        while (!StackEmpty() && StackTop() <= newHead->val)
        {
            StackPop();
        }
        tmp[len++] = StackEmpty() ? 0 : StackTop();
        StackPush(newHead->val);
        newHead = newHead->next;
    }
    reversearr(tmp,len); 
    StackDestory();

    int *ret = (int *)malloc(sizeof(int)*len);
    memcpy(ret,tmp,sizeof(int)*len);
    *returnSize = len;
    return ret;
}

// @lc code=end

int* nextLargerNodes(struct ListNode* head, int* returnSize){
    int tmp[10000] = {0};
    struct ListNode *left = head;
    struct ListNode *right = head;
    int len = 0;

    while (left !=NULL)
    {
        right = left;
        while (right != NULL && right->val <= left->val)
        {
            right = right->next;
        }

        if (right == NULL)
        {
            tmp[len] = 0;
            left = left->next;
            len++;
            continue;
        }

        // while (left != right)
        {
            tmp[len] = right->val;
            left = left->next;
            len++;
        }
    }
    int *ret = (int *)malloc(sizeof(int)*len);
    memcpy(ret,tmp,sizeof(int)*len);
    *returnSize = len;
    return ret;
}
