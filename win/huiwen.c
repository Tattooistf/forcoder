#include "stdio.h"
#include "string.h"

char input[100];

char * longestPalindrome(char * s);

int main(void)
{
    if(EOF == scanf("%s",input)) return 0;
	printf("%s\n",longestPalindrome(input));
    return 0;
}

char * longestPalindrome(char * s){
    int i;
    int max=0;
	int tmp=0;
    int pot=0;
    int j=0;

	if(strlen(s)<=1) return s;
	
    for(i=1;i<(int)strlen(s);i++)
    {
        if(s[i-1] == s[i])
        {
            while(s[i+j]==s[i-1-j])
			{
				tmp=2*j+2;
				j++;
				if((i+j>=(int)strlen(s))||(i-1<j))
				{
					break;
				}   
			}
        }
		if(s[i+1]==s[i-1])
		{
			while(s[i+j] == s[i-j])
			{
				tmp=2*j+1;
				j++;
				if((i+j>=(int)strlen(s))||(i<j))
				{
					break;
				}            
			}
		}
		
        if(tmp>=max)
        {
			max=tmp;
            pot = i;
        }
		tmp=0;
        j=0;
    }
	if(!max) {s[1]='\0';return s;};
	if(max%2 == 0)
	{
		s[pot+max/2]='\0';
		return s+pot-max/2;
	}
	else
	{
		s[pot+max/2+1]='\0';
		return s+pot-max/2;
	}
}
