//保留二叉树的层序遍历代码，后面可能需要
//比较简单的一道题，但是未解决输入的问题将二叉树的层序遍历重新做了一遍，花了一个小时；
//最后直接裸考代码10min，提交一次通过
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "ctype.h"

 typedef struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 }TreeNode;

bool isSameTree(struct TreeNode* p, struct TreeNode* q);

TreeNode *strarr[100]={0};
int qrd=0;
int qwr=0;
int qcnt=0;

void initq(void)
{
    qrd=0;
    qwr=0;
    qcnt=0;
    for (int i = 0; i < 100; i++)
    {
        strarr[i]=0;
    }
    
    return;
}

int enqueue(TreeNode *p)
{
    if (qcnt==100)
    {
        return 0;
    }
    strarr[qwr]=p;
    qwr=(qwr+1)%100;
    qcnt++;
    return 1;
}

TreeNode *dequeue(void)
{
    TreeNode *tmp=NULL;
    if (qcnt==0)
    {
        return NULL;
    }
    tmp=strarr[qrd];
    qrd=(qrd+1)%100;
    qcnt--;
    return tmp;
}

TreeNode *getNode(void)
{
    int tmp=0;

    TreeNode *pre=NULL;
    TreeNode *head=NULL;

    while (EOF!=scanf("%d",&tmp))
    {
        TreeNode *p=(TreeNode *)malloc(sizeof(TreeNode));
        if (head==NULL)
        {
            head=p;
        }
        
        p->val=tmp;
        p->right=NULL;
        p->left=NULL;
        enqueue(p);

        if (pre)
        {
            if (pre->left == NULL)
            {
                pre->left=p;
            }
            else
            {
                pre->right=p;
                pre=dequeue();
            }
        }
        else
        {
            pre=dequeue();
        }
        
    }
    initq();

    return head;
}

void printfNode(TreeNode *p)
{
    TreeNode *now=NULL;
    if (p==NULL)
    {
        return;
    }
    enqueue(p);
    while (qcnt!=0)
    {
        now=dequeue();
        if (now==NULL)
        {
            printf("null ");
            continue;
        }
        
        printf("%d ",now->val);
        if (now->right==NULL && now->left==NULL)
        {
            continue;
        }
        
        enqueue(now->left);
        if (now->right)
        {
            enqueue(now->right);
        }      
        
    }
    printf("\n");

    return;
}

int main()
{
    int a=0;
    TreeNode *p,*q;
    p=q=NULL;

    p=getNode();
    printfNode(p);
    q=getNode();
    printfNode(q);

    a=isSameTree(p,q);
    if (a==true)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    
    system("pause");
    return 0;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/* DFS深度优先简单算法 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if (p==q)
    {
        return true;
    }
    if (q==NULL || p==NULL)
    {
        return false;
    }
    
    if (p->val!=q->val)
    {
        return false;
    }
    if(!isSameTree(p->left,q->left)) return false;
    if(!isSameTree(p->right,q->right)) return false;
    
    return true;
}