#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define SWAP_ELEMENT(arr, i, j){    \
    int tmp = arr[i];       \
    arr[i] = arr[j];        \
    arr[j] = tmp;       \
}

void print_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    printf("\n");
}

// 该函数会把以root_idx索引元素为根结点的逻辑长度是tree_len的一棵完全二叉树arr，构建成一个大顶堆
static void heapify(int arr[], int tree_len, int root_idx) {
    /*
       堆化操作必然是需要循环来完成的
       如果对于某个循环,既不清楚循环的次数,循环结束的条件也不太好找到
       那么可以先写一个死循环, 然后具体到代码中再用break,return等结束循环
    */
    while (1) {
        // 根据根节点的下标,先计算出左右子树的下标
        int lchild_idx = (root_idx << 1) + 1;
        int rchild_idx = (root_idx << 1) + 2;
        int max_idx = root_idx;     // 先假设根节点就是最大值
        if (lchild_idx < tree_len && arr[lchild_idx] > arr[max_idx]) {
            // 如果左子树存在且左子树值比假设的最大值要大,那么左子树下标就是新的最大值下标
            max_idx = lchild_idx;
        }
        if (rchild_idx < tree_len && arr[rchild_idx] > arr[max_idx]) {
            // 如果右子树存在且右子树值比假设的最大值要大,那么右子树下标就是新的最大值下标
            max_idx = rchild_idx;
        }
        if (max_idx != root_idx) {
            // 交换左右子树较大者和根节点的值
            SWAP_ELEMENT(arr, max_idx, root_idx);
            // 此时max_idx结点的值就是以前根节点的值,此时由于数据发生了改变,max_idx结点的树就不一定是大顶堆了
            // 所以接下来要以max_idx为根节点,继续构建大顶堆
            root_idx = max_idx;
        }
        else {
            // 不需要交换了,说明以root_idx为根节点的树已经是大顶堆了
            break;
        }
    }
}
// 第一次将数组构建成大顶堆，自下而上将每一个非叶子结点构建大顶堆
static void first_build_heap(int arr[], int len) {
    int last_idx = (len - 2) >> 1;    //最后一个非叶子结点的下标
    for (int i = last_idx; i >= 0; i--) {
        heapify(arr, len, i);
    }
    printf("第一次堆化后数组为: \n");
    print_arr(arr, len);
}
void heap_sort(int arr[], int len) {
    // 1.将原arr数组构建成大顶堆，第一次构建大顶堆
    first_build_heap(arr, len);
    // 2.反复移除根结点元素，然后再重建大顶堆
    int heap_len = len; // 堆逻辑上的长度，一开始就是数组长度，随着反复移除重建大顶堆，这个长度会一直减少1
    while (heap_len > 1) {  // 只要堆还有两个元素就需要继续构建移除
        SWAP_ELEMENT(arr, 0, heap_len - 1);
        heap_len--;
        // 堆排序的核心操作：重新构建大顶堆
        heapify(arr, heap_len, 0);  // 堆排序核心操作：堆化
        printf("重新构建大顶堆后: \n");
        print_arr(arr, heap_len);
    }
}
int main(void) {
    int arr[] = { 4, 10, 3, 5, 1 };
    int len = ARR_SIZE(arr);
    printf("Before heap sort, the array is: ");
    print_arr(arr, len);
    // 测试堆排序
    heap_sort(arr, len);
    printf("After heap sort, the array is: ");
    print_arr(arr, len);

    return 0;
}
