int juge(int a,int b);

int numFriendRequests(int* ages, int agesSize){
    int array[121]={0};
    int i=0;
    int linknum=0;

    for ( i = 0; i < agesSize; i++)
    {
        array[ages[i]]++;
    }

    for ( i = 120; i >=1; i--)
    {
        int tmp = i-1;
        if (array[i]==0)
        {
            continue;
        }
        if ((array[i]>1) && !juge(i,i))//另外一个坑，自身也需要满足juge后才能+1
        {
            linknum+=(array[i]-1)*array[i];//一个坑，多个相同年龄的人之间建立的联系是n*n-1
        }
        
        while (tmp>=1)
        {
            if (array[tmp] && !juge(i,tmp))
            {
                linknum+=array[i]*array[tmp];
            }
            tmp--;
        }
    }
    return linknum;
    
}

int juge(int a,int b)
{
    if ((b<=0.5*a+7) || (b>a) || (b>100 && a<100) )
    {
        return 1;
    }
    return 0;
}
//[73,106,39,6,26,15,30,100,71,35,46,112,6,60,110]
