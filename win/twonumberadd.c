#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct ListNode{
	int val;
	struct ListNode *next;
}ListNode;
ListNode *NewNode(int a);
void OutPut(ListNode *p);
ListNode *addTwoNumbers(ListNode *pOne,ListNode *pTwo);

int main()
{
	char input[256];
	int ret,i;
	int count=0;
	ListNode *head[2]={NULL,NULL};
	ListNode *current=NULL;
	ListNode *tail=NULL;
	do{
		ret = scanf("%s",input);
		if(input[0]!='[') return 0;
		if(input[strlen(input)-1]!=']') return 0;
		for(i=0;i<(int)strlen(input);i++){
			if((input[i]<'0')||(input[i]>'9')) continue;
			current=NewNode(input[i]-'0');
			if(head[count]==NULL)
			{
				head[count]=tail=current;
			} 
			else
			{
				tail->next=current;
				tail = current;
			}
		}
		count++;
	}while((ret!=EOF)&&(count<2));

	//OutPut(head[0]);
	//OutPut(head[1]);
	OutPut(addTwoNumbers(head[0],head[1]));

	return 0;
}

void OutPut(ListNode *p)
{
	while(p!=NULL){
		printf("%d",p->val);
		p=p->next;
		if(p!=NULL) printf("->");
	}
	printf("\r\n");

	return;
}

ListNode *NewNode(int a)
{
	ListNode *pNode;
	pNode=(ListNode*)malloc(sizeof(ListNode));
	if(pNode == NULL)
		return NULL;
	pNode->val=a;
	pNode->next=NULL;
	
	return pNode;
}

ListNode *addTwoNumbers(ListNode *pOne,ListNode *pTwo)
{
	ListNode *pNode=NULL;
	ListNode *pHead=NULL;	
	ListNode *pTail=NULL;	
	int value,value1,value2;
	int carry = 0;

	while((pOne != NULL) || (pTwo != NULL))
	{
		value1 = value2 = 0;
		if(pOne != NULL)
		{
			value1 = pOne->val;
			pOne = pOne->next;
		}
		if(pTwo != NULL)
		{
			value2 = pTwo->val;
			pTwo = pTwo->next;
		}
	
		value = value1 + value2 + carry;
		carry = value/10;
		value = value%10;	

		pNode = NewNode(value);
		if(pHead==NULL)
		{
			pHead=pTail=pNode;
		}
		else
		{
			pTail->next=pNode;
			pTail = pNode;
		}
	}
	if(carry>0)
	{
		pNode = NewNode(carry);
		pTail->next=pNode;
		pTail = pNode;	
	}
	return pHead;
}

