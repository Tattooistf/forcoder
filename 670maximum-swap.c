
int maximumSwap(int num){
    int max,pzs,cnt;
    int tmp=num;
    int a[10]={0};
    int res=0;
    max=0;
    cnt=pzs=0;

    do
    {
        a[cnt++]=tmp%10;
        tmp/=10;
        if (a[cnt-1]>a[max]) {
            max=cnt-1;
            continue;
        }

        if (a[cnt-1]<a[max]) {
            pzs=cnt-1;
        }
    } while (tmp>0);

    if (max>pzs) {
        max=0;
        for(int i = pzs; i >= 0; i--)
        {
            max=a[i]>=a[max]?i:max;
        }
        
    }

    tmp=a[pzs];
    a[pzs]=a[max];
    a[max]=tmp;
    
    while(cnt>0){
        res=res*10+a[cnt-1];
        cnt--;
    }    
    
    return res;
}

// 基本上确定是错误的做法，能通过100个用例
int maximumSwap1(int num){
    int res=0;
    int tmp=num;
    int a[10]={0};
    int cnt=0;
    int max=0;
    int pst;
    int i;

    do
    {
        a[cnt++]=tmp%10;
        tmp/=10;
        //找出最大的数
        if (a[cnt-1]>max) {
            max=a[cnt-1];
            pst=cnt-1;
        }
        
    } while (tmp>0);

    if (pst==cnt-1) {
        for( i = cnt-1; i >0; i--)
        {
            if(a[i]<a[i-1])
            {
                pst=i;
                break;
            }
        }

        if (pst == cnt-1)
        {
            return num;
        }

        max=0;
        for( i = pst; i >=0; i--)
        {
            max=max<a[i]?a[i]:max;
        }

    }
    

    for(i = cnt-1; i >=0; i--)
    {
        if (a[i]<max) {
            tmp=a[pst];
            a[pst]=a[i];
            a[i]=tmp;
            break;
        } 
    }


    while(cnt>0){
        res=res*10+a[cnt-1];
        cnt--;
    }

    return res;

}
