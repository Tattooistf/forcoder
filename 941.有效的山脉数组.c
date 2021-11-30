/*
 * @lc app=leetcode.cn id=941 lang=c
 *
 * [941] 有效的山脉数组
 *
 * https://leetcode-cn.com/problems/valid-mountain-array/description/
 *
 * algorithms
 * Easy (39.25%)
 * Likes:    153
 * Dislikes: 0
 * Total Accepted:    60.3K
 * Total Submissions: 153.5K
 * Testcase Example:  '[2,1]'
 *
 * 给定一个整数数组 arr，如果它是有效的山脉数组就返回 true，否则返回 false。
 * 
 * 让我们回顾一下，如果 A 满足下述条件，那么它是一个山脉数组：
 * 
 * 
 * arr.length >= 3
 * 在 0 < i < arr.length - 1 条件下，存在 i 使得：
 * 
 * arr[0] < arr[1] < ... arr[i-1] < arr[i] 
 * arr[i] > arr[i+1] > ... > arr[arr.length - 1]
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：arr = [2,1]
 * 输出：false
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：arr = [3,5,5]
 * 输出：false
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：arr = [0,3,2,1]
 * 输出：true
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 0 
 * 
 * 
 */
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "stdbool.h"
bool validMountainArray(int* arr, int arrSize);

int main()
{
    int arr[] = {0,3,2,1};
    bool ret = validMountainArray(arr,sizeof(arr)/sizeof(arr[0]));
    return 0;
}

// @lc code=start
// 尝试使用双指针解题：最开始第一反应是双指针，只是没有想到很好的方法
// 严格意义上来说这个不属于双指针，只是两头分别找到最大值，看看是否为同一个
bool validMountainArray(int* arr, int arrSize){
    int left = 0;
    int right = arrSize-1;

    if (arrSize < 3)
    {
        return false;
    }
    
    while (left < arrSize-1 && arr[left] < arr[left+1])
    {
        left++;
    }

    while (0 < right && arr[right] < arr[right-1])
    {
        right--;
    }
    
    if ((left == right) && (left != arrSize-1) && (right != 0))
    {
        return true;
    }
    
    return false;
}

// @lc code=end

// // 先寻找最高点，然后判断接下来是否递减；效率不是最优，比不上下面的一次判断
// bool validMountainArray(int* arr, int arrSize){
//     int i = 0;
//     while (i<arrSize-1 && arr[i]<arr[i+1])
//     {
//         i++;
//     }
    
//     if (i == arrSize-1 || i == 0)
//     {
//         return false;
//     }

//     while (i < arrSize-1 && arr[i] > arr[i+1])
//     {
//         i++;
//     }
    
//     if (i == arrSize-1)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }


// bool validMountainArray(int* arr, int arrSize){
//     if (arrSize < 3)
//     {
//         return false;
//     }
//     if (arr[0] > arr[1] || arr[arrSize-1] > arr[arrSize-2])
//     {
//         return false;
//     }
    
//     bool dirFlag = true;
//     for (int i = 0; i < arrSize-1; i++)
//     {
//         if (arr[i] == arr[i+1])
//         {
//             return false;
//         }   

//         if (arr[i] > arr[i+1] || dirFlag == false)
//         {
//             if (arr[i] > arr[i+1])
//             {
//                 if (dirFlag == true)
//                 {
//                     dirFlag = false;
//                 }
//             }
//             else
//             {
//                 return false;
//             }
//         }
        
//     }
//     return true;
// }

// bool validMountainArray(int* arr, int arrSize){
//     if (arrSize < 3)
//     {
//         return false;
//     }
//     if (arr[0] > arr[1])
//     {
//         return false;
//     }
    
    
//     bool dirFlag = true;
//     for (int i = 0; i < arrSize-1; i++)
//     {
//         if (arr[i] < arr[i+1] && dirFlag == true)
//         {
//             continue;
//         }
//         else if (arr[i] > arr[i+1])
//         {
//             if (dirFlag == true)
//             {
//                 dirFlag = false;
//             }
//         }
//         else
//         {
//             return false;
//         }
        
//     }
//     return (dirFlag == true) ? false : true;
// }