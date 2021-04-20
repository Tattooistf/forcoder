/*
 * @lc app=leetcode.cn id=605 lang=c
 *
 * [605] 种花问题
 *
 * https://leetcode-cn.com/problems/can-place-flowers/description/
 *
 * algorithms
 * Easy (34.04%)
 * Likes:    339
 * Dislikes: 0
 * Total Accepted:    88.4K
 * Total Submissions: 263K
 * Testcase Example:  '[1,0,0,0,1]\n1'
 *
 * 假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
 * 
 * 给你一个整数数组  flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。另有一个数 n
 * ，能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：flowerbed = [1,0,0,0,1], n = 1
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：flowerbed = [1,0,0,0,1], n = 2
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * flowerbed[i] 为 0 或 1
 * flowerbed 中不存在相邻的两朵花
 * 0 
 * 
 * 
 */

// @lc code=start


//贪心法解题
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    int count = 0;
    if (n>flowerbedSize)
    {
        return false;
    }
    
    for (int i = 0; i < flowerbedSize; i++)
    {
        if (flowerbed[i] == 1)
        {
            continue;
        }
        
        if (i>0 && flowerbed[i-1] == 1)
        {
            continue;
        }
        if (i<flowerbedSize-1 && flowerbed[i+1] == 1)
        {
            continue;
        }
        flowerbed[i] = 1;
        count++;        
    }

    if (count>=n)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

// @lc code=end


bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    int k = 0;
    int i = 0;
    if (flowerbedSize == 1 && flowerbed[0]==0)
    {
        return true;
    }
    
    for (i = 0; i < flowerbedSize; i++)
    {
        //将两头的情况优先处理掉
        if (i == 0)
        {
            if (flowerbed[i]==0 && flowerbed[i+1]==0)
            {
                k++;
                flowerbed[i]=1;
            }
        }
        else if (i == flowerbedSize-1)
        {  
            if (flowerbed[flowerbedSize-1]==0 && flowerbed[flowerbedSize-2]==0)
            {
                k++;
                flowerbed[flowerbedSize-1]=1;
            }   
        }
        //其他的情况
        else if (flowerbed[i] == 0 && flowerbed[i+1] == 0 && flowerbed[i-1] == 0)
        {
            k++;
            flowerbed[i] = 1;
        }
    }
 
    if (k>=n)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//解答部分错误
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n){
    int k = 0;
    int i = 0;
    if (flowerbed[0] == 0 && flowerbed[1] == 0)
    {
        k++;
        flowerbed[0] = 1;
    }   

    for (i = 1; i < flowerbedSize-2; i++)
    {
        if (flowerbed[i] == 0 && flowerbed[i+1] == 0 && flowerbed[i-1] == 0)
        {
            k++;
            flowerbed[i] = 1;
        }
        else
        {
            continue;
        }
    }
 
    if (flowerbed[i] == 0 && flowerbed[i-1] == 0)
    {
        k++;
        flowerbed[i] = 1;
    }
    
    if (k>=n)
    {
        return true;
    }
    else
    {
        return false;
    }
}
