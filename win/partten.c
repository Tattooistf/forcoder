/*

�����ַ���s���ַ�����words����s���ҵ�words���ֵ�λ�ã�����ǰ��ӱ�Ƿ������
��ʼ���<b> 
�������</b>
������ص�����Ҫɾ���ص����
��������
2
cd df
acdfg
���滻��Ϊ
a<b>c<b>d</b>f</b>g
ɾ���ظ���Ǻ���ȷ�������
a<b>cdf</b>g

����
1
ab
ababab
�滻��Ϊ
<b>ab</b><b>ab</b><b>ab</b>
<b>ababab</b>
*/

#include "stdio.h"
#include "string.h"

#define MAX 512
#define CNT 64
int count=0;//word����
char string[MAX],outstr[MAX*2];//���������ַ���
char words[CNT][MAX];
const char bstr[2][6]={"<b>","</b>"};
int bstrpot[2][MAX]={0};//�洢��ʽ�����

void FormatStr(void);
void OutPut(void);
bool IsMatch(char *string);
void GetPara(void);
void ClrDupStr(void);

int main()
{
	//��ȡ���벢���г�ʼ��
	GetPara();
	
	/* �����ַ�����Ѱ��ƥ��words��Ƭ��
	   ����ƥ���Ƭ��ִ�и�ʽ�����
	*/
	FormatStr();
	OutPut();
	printf("%s\n",outstr);
	
	//��ʽ���ַ���ת�������ظ�
	ClrDupStr();
	OutPut();
	printf("%s\n",outstr);

	return 0;
}

void FormatStr(void)
{
	int i=0;

	for(i=0;i<(int)strlen(string);i++){
		if(IsMatch(string+i)){
			//��¼��ʼ��λ����Ϣ
			bstrpot[0][i]=1;
			//��¼������λ����Ϣ����ʼλ��ȷ�������word�����ܵ�֪������λ��
			bstrpot[1][i+strlen(words[0])-1]=1;
		}
	}		
	return;
}

void OutPut(void)
{
	int i;
	char *outptr=outstr;	
	
	for(i=0;i<(int)strlen(string);i++){
		if(bstrpot[0][i]==1)
		{
			//�����ʼ�ַ���
			sprintf(outptr,"%s",bstr[0]);
			outptr+=strlen(bstr[0]);			
		}
		*outptr++ = string[i];
		if(bstrpot[1][i]==1)
		{
			//��������ַ���
			sprintf(outptr,"%s",bstr[1]);
			outptr+=strlen(bstr[1]);			
		}
	}
	*outptr='\0';
	
	return;
}

bool IsMatch(char *string)
{
	int k,match;
	
	for(k=0;k<count;k++){
		match = strncmp(words[k],string,strlen(words[0]));
		if(match == 0) return true;
	}
	return false;
}

void GetPara(void)
{
	int i;
	
	scanf("%d\n",&count);
	count%=CNT;//promis param valid
	for(i=0;i<count;i++){
		scanf("%s",words[i]);
	}
	
	scanf("%s",string);

	return;
}

void ClrDupStr(void)
{
	int i,idx,match;
	
	for(idx=0;idx<(int)strlen(string);idx++){//�ص�����ļ���˼·���Թ�һ
		//���ǰһ����ʼ�����������������ʼ����˵��ǰ���໥�ص�����������
		if(bstrpot[0][idx] != 0){
			for(i=1;i<(int)strlen(words[0]);i++){
				if(bstrpot[0][idx+i]!=0){
					//��������ص�
					bstrpot[0][idx+i]=2;//��Ҫ���㣬�����Ǳ������滹��Ҫ�ã�������Ϊ�����ǣ�����ͳһ����
					bstrpot[1][idx+strlen(words[0])-1]=2;
				}
			}
			//���ǰһ��������������һ����ʼ����������������ȣ���������
			if((idx+strlen(words[0])) > strlen(string)) return;
			if(bstrpot[0][idx+strlen(words[0])]==1){
				match = strncmp(string+idx,string+idx+strlen(words[0]),strlen(words[0]));
				if(match == 0){
					bstrpot[1][idx+strlen(words[0])-1]=2;
					bstrpot[0][idx+strlen(words[0])]=2;
				}
			}
			
		}
	}
	
	//ǰ��������Ϊ�����ǣ��˴�ͳһ����
	for(idx=0;idx<(int)strlen(string);idx++){
		if(bstrpot[0][idx]==2) bstrpot[0][idx]=0;
		if(bstrpot[1][idx]==2) bstrpot[1][idx]=0;
	}
	return;
}

