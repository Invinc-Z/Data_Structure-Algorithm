#include <stdio.h>
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// 打印数组的函数
void print_arr(int arr[], int left, int right) {
    for (int i = left; i <= right; i++) 
        printf("%d ", arr[i]);
    printf("\n");
}

// 快速排序的核心操作: 双向分区, 也就是确定pivot的最终位置
// 挑选一个基准值,通过双向分区操作,决定最终的位置,最终位置就是基准值排好序的位置
static int partition(int arr[], int left, int right) {
    // 1.为了简化实现,直接挑选首元素为基准值，因为基准值要交换到开头，所以直接挑选首元素作为基准值，可以减少一步交换
    // (可以使用随机数挑选数组中的一个数作为基准值）
    int pivot = arr[left];
    // 2.初始化两个索引low和high,分别指向数组两端
    int low = left, high = right;
    // 3.循环遍历这个数组区间
    while (low < high) {    // 两个索引没有相遇就继续循环
                            // 在两个索引没有相遇的情况下,high索引用于寻找比基准值小的元素
        while (low < high && arr[high] >= pivot) {
            high--;
        }   // while循环结束时,要么两个索引相遇了,要么high索引已经找到了一个比基准值小的元素
        arr[low] = arr[high];   // 将这个比基准值小的元素覆盖到low位置
                                //low++;    该行语句不能加，因为若此时两个索引相遇结束while，low++将导致相遇的索引不再相遇
                                // 在两个索引没有相遇的情况下,low索引用于寻找比基准值大和相等的元素
        while (low < high && arr[low] < pivot) {
            low++;
        }   // while循环结束时,要么两个索引相遇了,要么low索引已经找到了一个比基准值大或相等的元素
        arr[high] = arr[low];   // 将这个比基准值大或相等的元素覆盖到high位置
                                //high--;   该行语句不能加，因为若此时两个索引相遇结束while，high--将导致相遇的索引不再相遇
    }   // while循环结束时,说明low和high索引相遇,此时该位置就是pivot应该放置的位置
    arr[low] = pivot;
    printf("此一轮分区操作选择的pivot = %d\n", pivot);
    print_arr(arr, left, right);
    return low;
}
// 对[left, right]区间进行递归分区操作
void partition_recursion(int arr[], int left, int right) {
    // 递归出口
    if (left >= right) 
        return;
    // 递归体
    int idx = partition(arr, left, right);  // 分区操作,找到pivot下标位置
    partition_recursion(arr, left, idx - 1);
    partition_recursion(arr, idx + 1, right);
}
void quick_sort_two_way(int arr[], int len) {
    partition_recursion(arr, 0, len - 1);
}

int main(void) {
    int arr[] = { 8,3,2,6,9,5 };
    int len = ARR_SIZE(arr);
    printf("Before quick sort, the array is: ");
    print_arr(arr, 0, len -1);
    // 测试双向分区-快速排序
    quick_sort_two_way(arr, len);
    printf("After quick sort, the array is: ");
    print_arr(arr, 0, len -1);

    return 0;
}
