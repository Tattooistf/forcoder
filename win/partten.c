/*

给定字符串s和字符数组words，在s中找到words出现的位置，并在前后加标记符后输出
起始标记<b> 
结束标记</b>
如果有重叠，需要删除重叠标记
例如输入
2
cd df
acdfg
后替换后为
a<b>c<b>d</b>f</b>g
删除重复标记后正确输出如下
a<b>cdf</b>g

输入
1
ab
ababab
替换后为
<b>ab</b><b>ab</b><b>ab</b>
<b>ababab</b>
*/

#include "stdio.h"
#include "string.h"

#define MAX 512
#define CNT 64
int count=0;//word个数
char string[MAX],outstr[MAX*2];//输入和输出字符串
char words[CNT][MAX];
const char bstr[2][6]={"<b>","</b>"};
int bstrpot[2][MAX]={0};//存储格式化标记

void FormatStr(void);
void OutPut(void);
bool IsMatch(char *string);
void GetPara(void);
void ClrDupStr(void);

int main()
{
	//获取输入并进行初始化
	GetPara();
	
	/* 遍历字符串，寻找匹配words的片段
	   对于匹配的片段执行格式化输出
	*/
	FormatStr();
	OutPut();
	printf("%s\n",outstr);
	
	//格式化字符串转换消除重复
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
			//记录起始符位置信息
			bstrpot[0][i]=1;
			//记录结束符位置信息，起始位置确定后根据word长度能得知结束符位置
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
			//输出起始字符串
			sprintf(outptr,"%s",bstr[0]);
			outptr+=strlen(bstr[0]);			
		}
		*outptr++ = string[i];
		if(bstrpot[1][i]==1)
		{
			//输出结束字符串
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
	
	for(idx=0;idx<(int)strlen(string);idx++){//重叠区域的计算思路可以归一
		//如果前一个起始符结束符区间包含起始符，说明前面相互重叠，可以清零
		if(bstrpot[0][idx] != 0){
			for(i=1;i<(int)strlen(words[0]);i++){
				if(bstrpot[0][idx+i]!=0){
					//区间存在重叠
					bstrpot[0][idx+i]=2;//需要清零，但考虑遍历后面还需要用，先设置为清零标记，后面统一处理
					bstrpot[1][idx+strlen(words[0])-1]=2;
				}
			}
			//如果前一个结束符紧贴下一个起始符，并且两个串相等，可以清零
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
	
	//前面先设置为清零标记，此处统一处理
	for(idx=0;idx<(int)strlen(string);idx++){
		if(bstrpot[0][idx]==2) bstrpot[0][idx]=0;
		if(bstrpot[1][idx]==2) bstrpot[1][idx]=0;
	}
	return;
}

