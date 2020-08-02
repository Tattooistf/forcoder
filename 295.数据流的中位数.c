/*
 * @lc app=leetcode.cn id=295 lang=c
 *
 * [295] 数据流的中位数
 *
 * https://leetcode-cn.com/problems/find-median-from-data-stream/description/
 *
 * algorithms
 * Hard (46.25%)
 * Likes:    220
 * Dislikes: 0
 * Total Accepted:    19K
 * Total Submissions: 40.5K
 * Testcase Example:  '["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]\n' +
  '[[],[1],[2],[],[3],[]]'
 *
 * 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
 * 
 * 例如，
 * 
 * [2,3,4] 的中位数是 3
 * 
 * [2,3] 的中位数是 (2 + 3) / 2 = 2.5
 * 
 * 设计一个支持以下两种操作的数据结构：
 * 
 * 
 * void addNum(int num) - 从数据流中添加一个整数到数据结构中。
 * double findMedian() - 返回目前所有元素的中位数。
 * 
 * 
 * 示例：
 * 
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3) 
 * findMedian() -> 2
 * 
 * 进阶:
 * 
 * 
 * 如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
 * 如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
 * 
 * 
 */

// @lc code=start
//插入排序方法，相比较堆排序而言，解题速度降低了很多，效率不如堆排序；但是代码量要少很多
#define HEAP_SIZE 20000  //第三个坑大小10000不满足要求，需要扩大到2W
typedef struct {
    int *array;
    int size;
} MedianFinder;

/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
    MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
    obj->array = (int *)malloc(sizeof(int)*HEAP_SIZE);
    memset(obj->array,0,sizeof(int)*HEAP_SIZE);
    obj->size = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    int left = 0;
    int right = obj->size-1;
    while (left<=right) // 判断条件边界没有搞好，需要<=，当0-1时导致新的值没有加入
    {
        int mid = (left+right)/2;
        if (obj->array[mid] == num)
        {
            left = mid;
            break;
        }        
        else if (obj->array[mid] < num)
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }
    int i = 0;
    for (i = obj->size; i > left; i--) // 第二个坑，腾挪位置需要往后多一个空间不能是obj->size-1
    {
        obj->array[i] = obj->array[i-1];
    }
    obj->array[left] = num;
    obj->size++;
    
    return;
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->size & 0x1)
    {
        return (double)obj->array[obj->size/2];
    }
    else
    {
        return ((double)(obj->array[obj->size/2] + obj->array[obj->size/2-1]))/2;
    }
}

void medianFinderFree(MedianFinder* obj) {
    if (obj)
    {
        if (obj->array)
        {
            free(obj->array);
        }
        obj->size = 0;
        free(obj);
    }
    return;
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/
// @lc code=end
#if 0
// 堆的解决方法
#define HEAP_SIZE 10000 //基本上一次通过，最刚开始的两次都是堆空间不够导致，100-1000-10000
typedef struct
{
    int *heap;
    int size;
}Heap;

typedef struct {
    Heap lheap;
    Heap rheap;
} MedianFinder;

/** initialize your data structure here. */
void PushMHeap(Heap *Heap,int val)
{
    Heap->heap[++Heap->size] = val;
    int i = Heap->size;
    for ( ; (i>>1)>=1; i=i>>1)
    {
        if (Heap->heap[i>>1] < val)
        {
            Heap->heap[i] = Heap->heap[i>>1];
        }
        else
        {
            break;
        }
    }
    Heap->heap[i] = val;
    return;
}

int PopMHeap(Heap *Heap)
{
    int res = Heap->heap[1];
    int tmp = Heap->heap[Heap->size--];
    int i = 1;
    int j = 1;
    for (; 2*i <= Heap->size; i=j)
    {
        if ((2*i+1) <= Heap->size && Heap->heap[2*i+1] > Heap->heap[2*i])
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        if (Heap->heap[j] > tmp)
        {
            Heap->heap[i] = Heap->heap[j];
        }
        else
        {
            break;
        }
    }
    Heap->heap[i] = tmp;

    return res;
}
void PushNHeap(Heap *Heap,int val)
{
    Heap->heap[++Heap->size] = val;
    int i = Heap->size;
    for ( ; (i>>1)>=1; i=i>>1)
    {
        if (Heap->heap[i>>1] > val)
        {
            Heap->heap[i] = Heap->heap[i>>1];
        }
        else
        {
            break;
        }
    }
    Heap->heap[i] = val;
    return;
}

int PopNHeap(Heap *Heap)
{
    int res = Heap->heap[1];
    int tmp = Heap->heap[Heap->size--];
    int i = 1;
    int j = 1;
    for (; 2*i <= Heap->size; i=j)
    {
        if ((2*i+1) <= Heap->size && Heap->heap[2*i+1] < Heap->heap[2*i])
        {
            j = 2*i+1;
        }
        else
        {
            j = 2*i;
        }
        if (Heap->heap[j] < tmp)
        {
            Heap->heap[i] = Heap->heap[j];
        }
        else
        {
            break;
        }
    }
    Heap->heap[i] = tmp;

    return res;
}

int TopHeap(Heap *heap)
{
    return heap->heap[1];
}
int NumHeap(Heap *heap)
{
    return heap->size;
}
MedianFinder* medianFinderCreate() {
    MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
    obj->lheap.heap = (int *)malloc(sizeof(int)*HEAP_SIZE);
    memset(obj->lheap.heap,0,sizeof(int)*HEAP_SIZE);
    obj->lheap.size = 0;
    obj->rheap.heap = (int *)malloc(sizeof(int)*HEAP_SIZE);
    memset(obj->rheap.heap,0,sizeof(int)*HEAP_SIZE);
    obj->rheap.size = 0;    
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    PushMHeap(&obj->lheap,num);
    int tmp = PopMHeap(&obj->lheap);
    PushNHeap(&obj->rheap,tmp);
    if (NumHeap(&obj->lheap) < NumHeap(&obj->rheap))
    {
        tmp = PopNHeap(&obj->rheap);
        PushMHeap(&obj->lheap,tmp);
    }   
    return;
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (NumHeap(&obj->lheap) > NumHeap(&obj->rheap))
    {
        return TopHeap(&obj->lheap);
    }
    else
    {
        return (double)(TopHeap(&obj->lheap)+TopHeap(&obj->rheap))/2;
    }
}

void medianFinderFree(MedianFinder* obj) {
    if (obj)
    {
        if (obj->lheap.heap)
        {
            free(obj->lheap.heap);
        }
        if (obj->rheap.heap)
        {
            free(obj->rheap.heap);
        }
        obj->lheap.size = 0;
        obj->rheap.size = 0;
        free(obj);
    }
    return;
}
#endif
